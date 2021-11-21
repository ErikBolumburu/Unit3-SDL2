#pragma once
#include <Vector2.hpp>

class Transform{
    public:
        Vector2 position;
        Vector2 scale;

        void SetTransform(Transform newTransform){
           position = newTransform.position;
           scale = newTransform.scale;
        };
        Transform(){};
        Transform(Vector2 Position, Vector2 Scale){
            position = Position;
            scale = Scale;
        };
};
