#pragma once
#include <iostream>

class Vector2f{
    public:
        float x,y;
        bool intersects(Vector2f p_other)
        {
            if(this->x - p_other.x <30 && this->x - p_other.x >-30 && this->y - p_other.y <30 && this->y - p_other.y >-30) 
                return true;
             
            return false;
        }
        bool borders(Vector2f p_other)
        {
            if(this->x - p_other.x <5 && this->x - p_other.x >-5 && this->y - p_other.y <5 && this->y - p_other.y >-5) 
                return true;
             
            return false;
        }
        Vector2f(float p_x, float p_y):x(p_x),y(p_y){};
        Vector2f():x(0.0),y(0.0){};
        void print(){
            std::cout << "x: " << x << ", y: " << y << std::endl;
        }
        operator void*() const { return (void*)this; }
};
