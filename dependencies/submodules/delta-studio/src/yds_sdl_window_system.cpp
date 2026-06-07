#include "../include/yds_sdl_window_system.h"
#include "../include/yds_sdl_window.h"
#include "../include/yds_sdl_key_maps.h"
#include "../include/yds_input_system.h"
#include "../include/yds_keyboard.h"
#include "../include/yds_mouse.h"
#include <SDL3/SDL.h>

ysSdlWindowSystem::ysSdlWindowSystem() : ysWindowSystem(Platform::SDL) {
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_GAMEPAD);
}

ysSdlWindowSystem::~ysSdlWindowSystem() {
    SDL_Quit();
}

ysError ysSdlWindowSystem::NewWindow(ysWindow **window) {
    YDS_ERROR_DECLARE("NewWindow");
    ysSdlWindow *newWindow = m_windowArray.NewGeneric<ysSdlWindow>();
    *window = newWindow;
    return YDS_ERROR_RETURN(ysError::None);
}

ysMonitor *ysSdlWindowSystem::NewMonitor() {
    return m_monitorArray.NewGeneric<ysMonitor>();
}

void ysSdlWindowSystem::SurveyMonitors() {
    // Add a single default monitor
    ysMonitor *monitor = NewMonitor();
    monitor->SetLogicalSize(1920, 1080);
    monitor->SetPhysicalSize(1920, 1080);
}

void ysSdlWindowSystem::ProcessMessages() {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_EVENT_QUIT) {
            CloseAllWindows();
        }
        else if (e.type == SDL_EVENT_KEY_DOWN || e.type == SDL_EVENT_KEY_UP) {
            if (m_inputSystem != nullptr) {
                ysInputDevice *keyboardDevice = m_inputSystem->GetInputDevice(0, ysInputDevice::InputDeviceType::KEYBOARD);
                if (keyboardDevice != nullptr) {
                    ysKeyboard *keyboard = keyboardDevice->GetAsKeyboard();
                    ysKey::Code index = ysSdlKeyMaps::GetKeyCode(e.key.scancode);
                    if (index != ysKey::Code::Undefined) {
                        ysKey::State newState;
                        if (e.type == SDL_EVENT_KEY_DOWN) {
                            newState = e.key.repeat ? ysKey::State::Down : ysKey::State::DownTransition;
                        } else {
                            newState = ysKey::State::UpTransition;
                        }
                        ysKey::Variation newConf = ysKey::Variation::Undefined;
                        if (e.key.scancode == SDL_SCANCODE_LSHIFT || e.key.scancode == SDL_SCANCODE_LCTRL || e.key.scancode == SDL_SCANCODE_LALT) {
                            newConf = ysKey::Variation::Left;
                        } else if (e.key.scancode == SDL_SCANCODE_RSHIFT || e.key.scancode == SDL_SCANCODE_RCTRL || e.key.scancode == SDL_SCANCODE_RALT) {
                            newConf = ysKey::Variation::Right;
                        }
                        keyboard->SetKeyState(index, newState, newConf);
                    }
                }
            }
        }
        else if (e.type == SDL_EVENT_MOUSE_MOTION || e.type == SDL_EVENT_MOUSE_BUTTON_DOWN || e.type == SDL_EVENT_MOUSE_BUTTON_UP || e.type == SDL_EVENT_MOUSE_WHEEL) {
            if (m_inputSystem != nullptr) {
                ysInputDevice *mouseDevice = m_inputSystem->GetInputDevice(0, ysInputDevice::InputDeviceType::MOUSE);
                if (mouseDevice != nullptr) {
                    ysMouse *mouse = mouseDevice->GetAsMouse();
                    if (e.type == SDL_EVENT_MOUSE_MOTION) {
                        mouse->SetOsPosition((int)e.motion.x, (int)e.motion.y);
                        mouse->UpdatePosition((int)e.motion.x, (int)e.motion.y, false);
                    }
                    else if (e.type == SDL_EVENT_MOUSE_WHEEL) {
                        mouse->UpdateWheel((int)e.wheel.y);
                    }
                    else if (e.type == SDL_EVENT_MOUSE_BUTTON_DOWN || e.type == SDL_EVENT_MOUSE_BUTTON_UP) {
                        ysMouse::Button button = ysMouse::Button::Left;
                        if (e.button.button == SDL_BUTTON_LEFT) button = ysMouse::Button::Left;
                        else if (e.button.button == SDL_BUTTON_RIGHT) button = ysMouse::Button::Right;
                        else if (e.button.button == SDL_BUTTON_MIDDLE) button = ysMouse::Button::Middle;
                        else if (e.button.button == SDL_BUTTON_X1) button = ysMouse::Button::Aux_1;
                        else if (e.button.button == SDL_BUTTON_X2) button = ysMouse::Button::Aux_2;
                        
                        ysMouse::ButtonState state = (e.type == SDL_EVENT_MOUSE_BUTTON_DOWN) ? ysMouse::ButtonState::DownTransition : ysMouse::ButtonState::UpTransition;
                        mouse->UpdateButton(button, state);
                    }
                }
            }
        }
    }
}
