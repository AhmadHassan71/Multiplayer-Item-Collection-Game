#pragma once
#include <SDL2/SDL.h>

namespace utils{

    float hireTime()
    {
        float t = SDL_GetTicks();
        return t*0.001f;
    }
}
