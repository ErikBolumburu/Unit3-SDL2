#pragma once

struct Vector2{ // Creates a struct with 2 variables (x, y). Used for a lot of things like position, scale, velocity, etc.
    float x;
    float y;
    Vector2(){ // If no arguements are provided, assume that x and y are both 0
        x = 0.0f;
        y = 0.0f;
    };
    Vector2(float X, float Y){ // If an x and y value are provided, initialize the Vector2 with them
        x = X;
        y = Y;
    }
};