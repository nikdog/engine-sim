#ifndef YDS_SDL_AUDIO_BUFFER_H
#define YDS_SDL_AUDIO_BUFFER_H

#include "yds_audio_buffer.h"
#include <cstdint>

class ysSdlAudioBuffer : public ysAudioBuffer {
public:
    ysSdlAudioBuffer();
    virtual ~ysSdlAudioBuffer();

    virtual ysError Initialize(SampleOffset samples, const ysAudioParameters &parameters) override;
    virtual ysError EditBuffer(void *data) override;
    virtual ysError EditBufferSegment(void *data, SampleOffset samples, SampleOffset offset) override;
    virtual ysError Destroy() override;

    uint8_t *GetBuffer() { return m_buffer; }

protected:
    uint8_t *m_buffer;
};

#endif
