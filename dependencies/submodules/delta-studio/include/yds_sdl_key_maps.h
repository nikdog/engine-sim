#ifndef YDS_SDL_KEY_MAPS_H
#define YDS_SDL_KEY_MAPS_H

#include "yds_keyboard.h"
#include <SDL3/SDL.h>

class ysSdlKeyMaps {
public:
    static ysKey::Code GetKeyCode(SDL_Scancode scancode);
};

#endif
