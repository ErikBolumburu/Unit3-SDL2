#pragma once
#include <GameObject.hpp>
#include <vector>

class Platform : public GameObject{
    public: 
        Platform(){};
        Platform(Transform trans){
            transform = trans;
            rect.x = transform.position.x;
            rect.y = transform.position.y;
            rect.w = transform.scale.x;
            rect.h = transform.scale.y;
            }
        virtual void Update() override {
            rect.x = transform.position.x;
            rect.y = transform.position.y;
            rect.w = transform.scale.x;
            rect.h = transform.scale.y;
        }
};