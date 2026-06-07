#include "../include/yds_sdl_key_maps.h"

ysKey::Code ysSdlKeyMaps::GetKeyCode(SDL_Scancode scancode) {
    switch (scancode) {
        case SDL_SCANCODE_A: return ysKey::Code::A;
        case SDL_SCANCODE_B: return ysKey::Code::B;
        case SDL_SCANCODE_C: return ysKey::Code::C;
        case SDL_SCANCODE_D: return ysKey::Code::D;
        case SDL_SCANCODE_E: return ysKey::Code::E;
        case SDL_SCANCODE_F: return ysKey::Code::F;
        case SDL_SCANCODE_G: return ysKey::Code::G;
        case SDL_SCANCODE_H: return ysKey::Code::H;
        case SDL_SCANCODE_I: return ysKey::Code::I;
        case SDL_SCANCODE_J: return ysKey::Code::J;
        case SDL_SCANCODE_K: return ysKey::Code::K;
        case SDL_SCANCODE_L: return ysKey::Code::L;
        case SDL_SCANCODE_M: return ysKey::Code::M;
        case SDL_SCANCODE_N: return ysKey::Code::N;
        case SDL_SCANCODE_O: return ysKey::Code::O;
        case SDL_SCANCODE_P: return ysKey::Code::P;
        case SDL_SCANCODE_Q: return ysKey::Code::Q;
        case SDL_SCANCODE_R: return ysKey::Code::R;
        case SDL_SCANCODE_S: return ysKey::Code::S;
        case SDL_SCANCODE_T: return ysKey::Code::T;
        case SDL_SCANCODE_U: return ysKey::Code::U;
        case SDL_SCANCODE_V: return ysKey::Code::V;
        case SDL_SCANCODE_W: return ysKey::Code::W;
        case SDL_SCANCODE_X: return ysKey::Code::X;
        case SDL_SCANCODE_Y: return ysKey::Code::Y;
        case SDL_SCANCODE_Z: return ysKey::Code::Z;
        case SDL_SCANCODE_0: return ysKey::Code::N0;
        case SDL_SCANCODE_1: return ysKey::Code::N1;
        case SDL_SCANCODE_2: return ysKey::Code::N2;
        case SDL_SCANCODE_3: return ysKey::Code::N3;
        case SDL_SCANCODE_4: return ysKey::Code::N4;
        case SDL_SCANCODE_5: return ysKey::Code::N5;
        case SDL_SCANCODE_6: return ysKey::Code::N6;
        case SDL_SCANCODE_7: return ysKey::Code::N7;
        case SDL_SCANCODE_8: return ysKey::Code::N8;
        case SDL_SCANCODE_9: return ysKey::Code::N9;
        case SDL_SCANCODE_RETURN: return ysKey::Code::Return;
        case SDL_SCANCODE_ESCAPE: return ysKey::Code::Escape;
        case SDL_SCANCODE_BACKSPACE: return ysKey::Code::Back;
        case SDL_SCANCODE_TAB: return ysKey::Code::Tab;
        case SDL_SCANCODE_SPACE: return ysKey::Code::Space;
        case SDL_SCANCODE_LSHIFT: return ysKey::Code::Shift;
        case SDL_SCANCODE_RSHIFT: return ysKey::Code::Shift;
        case SDL_SCANCODE_LCTRL: return ysKey::Code::Control;
        case SDL_SCANCODE_RCTRL: return ysKey::Code::Control;
        case SDL_SCANCODE_LALT: return ysKey::Code::LeftMenu;
        case SDL_SCANCODE_RALT: return ysKey::Code::RightMenu;
        case SDL_SCANCODE_UP: return ysKey::Code::Up;
        case SDL_SCANCODE_DOWN: return ysKey::Code::Down;
        case SDL_SCANCODE_LEFT: return ysKey::Code::Left;
        case SDL_SCANCODE_RIGHT: return ysKey::Code::Right;
        case SDL_SCANCODE_COMMA: return ysKey::Code::OEM_Comma;
        case SDL_SCANCODE_PERIOD: return ysKey::Code::OEM_Period;
        case SDL_SCANCODE_MINUS: return ysKey::Code::OEM_Minus;
        case SDL_SCANCODE_EQUALS: return ysKey::Code::OEM_Plus;
        default: return ysKey::Code::Undefined;
    }
}
