#ifndef YDS_SDL_AUDIO_SOURCE_H
#define YDS_SDL_AUDIO_SOURCE_H

#include "yds_audio_source.h"
#include <SDL3/SDL.h>
#include <cstdint>

class ysAudioDevice;

class ysSdlAudioSource : public ysAudioSource {
    friend class ysSdlAudioSystem;

public:
    ysSdlAudioSource();
    virtual ~ysSdlAudioSource();

    ysError Construct(ysAudioDevice *device);
    virtual ysError Destroy() override;

    virtual ysError LockEntireBuffer(void **buffer, SampleOffset *samples) override;
    virtual ysError UnlockBuffer(void *buffer, SampleOffset samples) override;
    virtual ysError LockBufferSegment(SampleOffset offset, SampleOffset samples, void **segment1, SampleOffset *size1, void **segment2, SampleOffset *size2) override;
    virtual ysError UnlockBufferSegments(void *segment1, SampleOffset segment1Size, void *segment2, SampleOffset segment2Size) override;

    virtual ysError SetMode(Mode mode) override;
    virtual SampleOffset GetCurrentPosition() override;
    virtual SampleOffset GetCurrentWritePosition() override;
    virtual void Seek(SampleOffset offset) override;

    static void SDLCALL StreamCallback(void *userdata, SDL_AudioStream *stream, int additional_amount, int total_amount);

protected:
    SDL_AudioStream *m_stream;
    SampleOffset m_playPosition;
};

#endif
