#pragma once
#include <Vector2.hpp>

class Transform{ // Creates the Transform class, used in GameObjects to store values about its physical state
    public: // All variables and functions in this section are accessible outside of the script
        Vector2 position;
        Vector2 scale;
        Vector2 velocity;
        void SetTransform(Transform newTransform); // A function that changes the Transform to a totally new, provided Transform
        void SetPosition(Vector2 newPosition);     // A function that changes the position to a totally new, provided position
        void Move(Vector2 direction);              // A function that adjusts the position of a Transform by a provided direction
        Transform(){};                             // Do nothing but create the object if no arguements are passed through
        Transform(Vector2 pos, Vector2 _scale){    // If a position and scale are provided, create the Transform with those values
            position = pos;
            scale = _scale;
        }
};