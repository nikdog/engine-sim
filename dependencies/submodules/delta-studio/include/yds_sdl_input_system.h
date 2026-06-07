#ifndef YDS_SDL_INPUT_SYSTEM_H
#define YDS_SDL_INPUT_SYSTEM_H

#include "yds_input_system.h"

class ysSdlInputSystem : public ysInputSystem {
public:
    ysSdlInputSystem();
    virtual ~ysSdlInputSystem();
    virtual ysError CreateDevices() override;
    virtual ysInputDevice *CreateDevice(ysInputDevice::InputDeviceType type, int id) override;
};

#endif
