#ifndef YDS_SDL_AUDIO_SYSTEM_H
#define YDS_SDL_AUDIO_SYSTEM_H

#include "yds_audio_system.h"
#include "yds_sdl_audio_device.h"

class ysSdlAudioSystem : public ysAudioSystem {
public:
    ysSdlAudioSystem();
    virtual ~ysSdlAudioSystem();

    virtual void EnumerateDevices() override;
    virtual void ConnectDevice(ysAudioDevice *device, ysWindow *window) override;
    virtual void ConnectDeviceConsole(ysAudioDevice *device) override;
    virtual void DisconnectDevice(ysAudioDevice *device) override;

protected:
    ysSdlAudioDevice *AddSdlDevice();
};

#endif
