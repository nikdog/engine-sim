#include "../include/yds_sdl_audio_source.h"
#include "../include/yds_sdl_audio_buffer.h"

#include <cstdint>
#include <cstring>
#include "../include/yds_audio_device.h"

ysSdlAudioSource::ysSdlAudioSource() : ysAudioSource(API::SDL) {
    m_stream = nullptr;
    m_playPosition = 0;
}

ysSdlAudioSource::~ysSdlAudioSource() {
    Destroy();
}

void SDLCALL ysSdlAudioSource::StreamCallback(void *userdata, SDL_AudioStream *stream, int additional_amount, int total_amount) {
    ysSdlAudioSource *source = static_cast<ysSdlAudioSource *>(userdata);
    
    if (source->m_dataBuffer != nullptr && 
        (source->GetBufferMode() == Mode::Play || 
         source->GetBufferMode() == Mode::Loop || 
         source->GetBufferMode() == Mode::PlayOnce)) {
        ysSdlAudioBuffer *sdlBuffer = static_cast<ysSdlAudioBuffer *>(source->m_dataBuffer);
        
        int bufferSize = sdlBuffer->GetBufferSize();
        if (bufferSize > 0) {
            uint8_t *data = new uint8_t[additional_amount];
            uint8_t *bufferData = sdlBuffer->GetBuffer();

            // Circular buffer read
            int amountRead = 0;
            while (amountRead < additional_amount) {
                int toRead = additional_amount - amountRead;
                int bytesToEnd = bufferSize - source->m_playPosition;

                if (toRead > bytesToEnd) {
                    toRead = bytesToEnd;
                }

                memcpy(data + amountRead, bufferData + source->m_playPosition, toRead);
                source->m_playPosition = (source->m_playPosition + toRead) % bufferSize;
                amountRead += toRead;
            }

            // Apply volume
            float volume = source->m_volume * source->m_panVolume;
            if (volume != 1.0f) {
                int16_t *samples = reinterpret_cast<int16_t *>(data);
                int numSamples = additional_amount / 2;
                for (int i = 0; i < numSamples; ++i) {
                    samples[i] = static_cast<int16_t>(samples[i] * volume);
                }
            }

            SDL_PutAudioStreamData(stream, data, additional_amount);
            delete[] data;
        }
    } else {
        // Output silence if paused or no buffer
        uint8_t *data = new uint8_t[additional_amount];
        memset(data, 0, additional_amount);
        SDL_PutAudioStreamData(stream, data, additional_amount);
        delete[] data;
    }
}

ysError ysSdlAudioSource::Construct(ysAudioDevice *device) {
    YDS_ERROR_DECLARE("Construct");

    SDL_AudioSpec spec;
    spec.freq = 44100;
    spec.format = SDL_AUDIO_S16;
    spec.channels = 1;

    m_stream = SDL_OpenAudioDeviceStream(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, &spec, StreamCallback, this);
    if (!m_stream) {
        return YDS_ERROR_RETURN(ysError::ApiError);
    }
    
    SDL_ResumeAudioStreamDevice(m_stream);

    return YDS_ERROR_RETURN(ysError::None);
}

ysError ysSdlAudioSource::Destroy() {
    YDS_ERROR_DECLARE("Destroy");

    if (m_stream) {
        SDL_DestroyAudioStream(m_stream);
        m_stream = nullptr;
    }

    return YDS_ERROR_RETURN(ysError::None);
}

ysError ysSdlAudioSource::LockEntireBuffer(void **buffer, SampleOffset *samples) {
    YDS_ERROR_DECLARE("LockEntireBuffer");
    
    ysError err = ysAudioSource::LockEntireBuffer(buffer, samples);
    if (err != ysError::None) return YDS_ERROR_RETURN(err);

    ysSdlAudioBuffer *sdlBuffer = static_cast<ysSdlAudioBuffer *>(m_dataBuffer);
    *buffer = sdlBuffer->GetBuffer();
    *samples = sdlBuffer->GetSampleCount();

    return YDS_ERROR_RETURN(ysError::None);
}

ysError ysSdlAudioSource::UnlockBuffer(void *buffer, SampleOffset samples) {
    YDS_ERROR_DECLARE("UnlockBuffer");

    ysError err = ysAudioSource::UnlockBuffer(buffer, samples);
    if (err != ysError::None) return YDS_ERROR_RETURN(err);

    return YDS_ERROR_RETURN(ysError::None);
}

ysError ysSdlAudioSource::LockBufferSegment(SampleOffset offset, SampleOffset samples, void **segment1, SampleOffset *size1, void **segment2, SampleOffset *size2) {
    YDS_ERROR_DECLARE("LockBufferSegment");

    ysError err = ysAudioSource::LockBufferSegment(offset, samples, segment1, size1, segment2, size2);
    if (err != ysError::None) return YDS_ERROR_RETURN(err);

    ysSdlAudioBuffer *sdlBuffer = static_cast<ysSdlAudioBuffer *>(m_dataBuffer);
    uint8_t *bufferData = sdlBuffer->GetBuffer();

    int offsetBytes = m_audioParameters.GetSizeFromSamples(offset);
    *segment1 = bufferData + offsetBytes;

    if (segment2) {
        *segment2 = bufferData;
    }

    return YDS_ERROR_RETURN(ysError::None);
}

ysError ysSdlAudioSource::UnlockBufferSegments(void *segment1, SampleOffset segment1Size, void *segment2, SampleOffset segment2Size) {
    YDS_ERROR_DECLARE("UnlockBufferSegments");

    ysError err = ysAudioSource::UnlockBufferSegments(segment1, segment1Size, segment2, segment2Size);
    if (err != ysError::None) return YDS_ERROR_RETURN(err);

    return YDS_ERROR_RETURN(ysError::None);
}

ysError ysSdlAudioSource::SetMode(Mode mode) {
    YDS_ERROR_DECLARE("SetMode");
    
    ysError err = ysAudioSource::SetMode(mode);
    if (err != ysError::None) return YDS_ERROR_RETURN(err);
    
    if (mode == Mode::Play || mode == Mode::Loop || mode == Mode::PlayOnce) {
        if (m_stream) {
            SDL_ResumeAudioStreamDevice(m_stream);
        }
    } else {
        if (m_stream) {
            SDL_PauseAudioStreamDevice(m_stream);
        }
    }
    
    return YDS_ERROR_RETURN(ysError::None);
}

SampleOffset ysSdlAudioSource::GetCurrentPosition() {
    return m_audioParameters.GetSamplesFromSize(m_playPosition);
}

SampleOffset ysSdlAudioSource::GetCurrentWritePosition() {
    return GetCurrentPosition();
}

void ysSdlAudioSource::Seek(SampleOffset offset) {
    m_playPosition = m_audioParameters.GetSizeFromSamples(offset);
}
