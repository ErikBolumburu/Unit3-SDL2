#pragma once

struct Vector2{
    float x;
    float y;

    public:
        // If no parameters are provided, default both x & y to 0.0f
        Vector2(){
            x = 0.0f;
            y = 0.0f;
        };
        Vector2(float X, float Y){
            x = X;
            y = Y;
        };
};
