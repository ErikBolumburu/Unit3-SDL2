#pragma once
#include <Vector2.hpp>

class Transform{
    public:
        Vector2 position;
        Vector2 scale;
        Vector2 velocity;
        void SetTransform(Transform newTransform);
        void SetPosition(Vector2 newPosition);
        void Move(Vector2 direction);
        Transform(){};
        Transform(Vector2 pos, Vector2 _scale){
            position = pos;
            scale = _scale;
        }
};