#include "../include/yds_sdl_input_system.h"

ysSdlInputSystem::ysSdlInputSystem() : ysInputSystem(Platform::SDL) {
}

ysSdlInputSystem::~ysSdlInputSystem() {
}

ysError ysSdlInputSystem::CreateDevices() {
    ysInputDevice *keyboard = m_inputDeviceArray.NewGeneric<ysInputDevice>();
    keyboard->SetType(ysInputDevice::InputDeviceType::KEYBOARD);
    keyboard->SetDeviceID(0);
    keyboard->SetName("KEYBOARD000");
    RegisterDevice(keyboard);

    ysInputDevice *mouse = m_inputDeviceArray.NewGeneric<ysInputDevice>();
    mouse->SetType(ysInputDevice::InputDeviceType::MOUSE);
    mouse->SetDeviceID(0);
    mouse->SetName("MOUSE000");
    RegisterDevice(mouse);

    return ysError::None;
}

ysInputDevice *ysSdlInputSystem::CreateDevice(ysInputDevice::InputDeviceType type, int id) {
    return nullptr;
}
