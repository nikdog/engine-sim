#ifndef YDS_SDL_AUDIO_DEVICE_H
#define YDS_SDL_AUDIO_DEVICE_H

#include "yds_audio_device.h"

class ysSdlAudioSystem;

class ysSdlAudioDevice : public ysAudioDevice {
    friend class ysSdlAudioSystem;

public:
    ysSdlAudioDevice();
    virtual ~ysSdlAudioDevice();

    virtual ysAudioBuffer *CreateBuffer(const ysAudioParameters *parameters, SampleOffset size) override;

    virtual ysAudioSource *CreateSource(const ysAudioParameters *parameters, SampleOffset size) override;
    virtual ysAudioSource *CreateSource(ysAudioBuffer *sourceBuffer) override;

    virtual void UpdateAudioSources() override;
};

#endif
