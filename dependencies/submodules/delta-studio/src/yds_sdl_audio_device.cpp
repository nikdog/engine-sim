#include "../include/yds_sdl_audio_device.h"
#include "../include/yds_sdl_audio_buffer.h"
#include "../include/yds_sdl_audio_source.h"

ysSdlAudioDevice::ysSdlAudioDevice() : ysAudioDevice(API::SDL) {
}

ysSdlAudioDevice::~ysSdlAudioDevice() {
}

ysAudioBuffer *ysSdlAudioDevice::CreateBuffer(const ysAudioParameters *parameters, SampleOffset size) {
    ysSdlAudioBuffer *newBuffer = m_audioBuffers.NewGeneric<ysSdlAudioBuffer>();
    newBuffer->Initialize(size, *parameters);

    return newBuffer;
}

ysAudioSource *ysSdlAudioDevice::CreateSource(const ysAudioParameters *parameters, SampleOffset size) {
    ysSdlAudioSource *newSource = m_audioSources.NewGeneric<ysSdlAudioSource>();
    
    newSource->m_bufferSize = size;
    if (parameters) {
        newSource->m_audioParameters = *parameters;
    }
    
    newSource->Construct(this);

    return newSource;
}

ysAudioSource *ysSdlAudioDevice::CreateSource(ysAudioBuffer *sourceBuffer) {
    ysSdlAudioSource *newSource = m_audioSources.NewGeneric<ysSdlAudioSource>();
    
    if (sourceBuffer) {
        newSource->m_bufferSize = sourceBuffer->GetSampleCount();
        newSource->SetDataBuffer(sourceBuffer);
        newSource->m_audioParameters = *sourceBuffer->GetAudioParameters();
    }
    
    newSource->Construct(this);

    return newSource;
}

void ysSdlAudioDevice::UpdateAudioSources() {
    // SDL audio playback handles polling natively through callbacks.
    // Nothing required here unless we need to manage state changes.
}
