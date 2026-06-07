#include "../include/yds_sdl_audio_system.h"

ysSdlAudioSystem::ysSdlAudioSystem() : ysAudioSystem(API::SDL) {
}

ysSdlAudioSystem::~ysSdlAudioSystem() {
}

void ysSdlAudioSystem::EnumerateDevices() {
    ysAudioSystem::EnumerateDevices();
    ysSdlAudioDevice *device = AddSdlDevice();
    device->SetDeviceName("SDL Audio Device");
    // device->SetAvailable(true);
    // device->SetConnected(true);
}

ysSdlAudioDevice *ysSdlAudioSystem::AddSdlDevice() {
    return m_devices.NewGeneric<ysSdlAudioDevice>();
}

void ysSdlAudioSystem::ConnectDevice(ysAudioDevice *device, ysWindow *window) {
    ysAudioSystem::ConnectDevice(device, window);
}

void ysSdlAudioSystem::ConnectDeviceConsole(ysAudioDevice *device) {
    ysAudioSystem::ConnectDeviceConsole(device);
}

void ysSdlAudioSystem::DisconnectDevice(ysAudioDevice *device) {
    ysAudioSystem::DisconnectDevice(device);
}
