#pragma once
#include <SDL2/SDL.h>
#include <Transform.hpp>

class GameObject{ // Create a class called GameObject
    public: // All variables and functions in this section are accessible outside of the script
        Transform GetTransform(); // Function to return the GameObjects Transform
        SDL_Rect rect; // An SDL_Rect used for rendering
        GameObject(){}; // If no arguements are provided, create the object and do nothing else
        GameObject(Transform trans){ // If a Transform is provided, ensure that the SDL_Rect and Transform allign
            transform = trans;
            rect.x = transform.position.x;
            rect.y = transform.position.y;
            rect.w = transform.scale.x;
            rect.h = transform.scale.y;
        }
        virtual void Update() = 0; // A function that can be overloaded in classes that derive from GameObject
        Transform transform; // A Transform variable named 'transform' to store the GameObjects position, scale and velocity
};