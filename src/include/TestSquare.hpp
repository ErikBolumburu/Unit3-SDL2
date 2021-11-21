#pragma once
#include <GameObject.hpp>
#include <Transform.hpp>

class TestSquare : public GameObject{
    public:
        TestSquare(){};
        TestSquare(Transform trans){
            transform = trans;
            rect.x = transform.position.x;
            rect.y = transform.position.y;
            rect.w = transform.scale.x;
            rect.h = transform.scale.y;
        }
};
