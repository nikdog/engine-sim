#include "../include/yds_sdl_audio_buffer.h"
#include <cstring>

ysSdlAudioBuffer::ysSdlAudioBuffer() : ysAudioBuffer(API::SDL) {
    m_buffer = nullptr;
}

ysSdlAudioBuffer::~ysSdlAudioBuffer() {
    Destroy();
}

ysError ysSdlAudioBuffer::Initialize(SampleOffset samples, const ysAudioParameters &parameters) {
    YDS_ERROR_DECLARE("Initialize");

    Destroy();

    m_samples = samples;
    m_audioParameters = parameters;

    int size = GetBufferSize();
    if (size > 0) {
        m_buffer = new uint8_t[size];
        memset(m_buffer, 0, size);
    }

    return YDS_ERROR_RETURN(ysError::None);
}

ysError ysSdlAudioBuffer::EditBuffer(void *data) {
    YDS_ERROR_DECLARE("EditBuffer");

    if (m_buffer && data) {
        memcpy(m_buffer, data, GetBufferSize());
    }

    return YDS_ERROR_RETURN(ysError::None);
}

ysError ysSdlAudioBuffer::EditBufferSegment(void *data, SampleOffset samples, SampleOffset offset) {
    YDS_ERROR_DECLARE("EditBufferSegment");

    if (m_buffer && data) {
        int bytes = m_audioParameters.GetSizeFromSamples(samples);
        int offsetBytes = m_audioParameters.GetSizeFromSamples(offset);
        memcpy(m_buffer + offsetBytes, data, bytes);
    }

    return YDS_ERROR_RETURN(ysError::None);
}

ysError ysSdlAudioBuffer::Destroy() {
    YDS_ERROR_DECLARE("Destroy");

    if (m_buffer) {
        delete[] m_buffer;
        m_buffer = nullptr;
    }

    return YDS_ERROR_RETURN(ysError::None);
}
