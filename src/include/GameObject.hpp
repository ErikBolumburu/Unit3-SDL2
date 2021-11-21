#pragma once
#include <SDL2/SDL.h>
#include <Transform.hpp>

class GameObject{
    public:
        SDL_Rect rect;
        Transform transform;
            GameObject(){};
            GameObject(Transform trans){
                transform = trans;
                rect.x = transform.position.x;
                rect.y = transform.position.y;
                rect.w = transform.scale.x;
                rect.h = transform.scale.y;
            }
};
