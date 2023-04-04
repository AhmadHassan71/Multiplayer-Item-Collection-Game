#pragma once

#include <iostream>
#include "Physics.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Object
{
private:
    Vector2f pos;
    SDL_Rect currentFrame;
    SDL_Texture *texture;

public:
    Object(Vector2f p_pos, SDL_Texture *p_texture);
    Object(Vector2f p_pos, SDL_Texture *p_texture,float p_w,float p_h);

    Vector2f &getPos();
    void *move(float p_x, float p_y);
    void setPos(float, float);
    SDL_Texture *getTexture();
    SDL_Rect getCurrentFrame();
    operator void *() const { return (void *)this; }
};

Object::Object(Vector2f p_pos, SDL_Texture *p_texture)
{
    pos = p_pos;
    texture = p_texture;
    currentFrame.x = 0;
    currentFrame.y = 0;
    currentFrame.w = 32;
    currentFrame.h = 32;
}
Object::Object(Vector2f p_pos, SDL_Texture *p_texture,float p_w,float p_h)
{
    pos = p_pos;
    texture = p_texture;
    currentFrame.x = 0;
    currentFrame.y = 0;
    currentFrame.w = p_w;
    currentFrame.h = p_h;
}
void *Object ::move(float p_x, float p_y)
{
    pos.x += p_x;
    pos.y += p_y;

    return (void *)this->getPos();
}

void Object ::setPos(float p_x, float p_y)
{
    pos.x = p_x;
    pos.y = p_y;
}

Vector2f &Object ::getPos()
{
    return pos;
}

SDL_Texture *Object ::getTexture()
{
    return texture;
}

SDL_Rect Object ::getCurrentFrame()
{
    return currentFrame;
}



