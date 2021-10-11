#pragma once
#include <SDL2/SDL.h>
#include <Transform.hpp>

class GameObject{
    public:
        Transform GetTransform();
        SDL_Rect rect;
        GameObject(){};
        GameObject(Transform trans){
            transform = trans;
            rect.x = transform.position.x;
            rect.y = transform.position.y;
            rect.w = transform.scale.x;
            rect.h = transform.scale.y;
        }
        virtual void Update() = 0;
        Transform transform;
};