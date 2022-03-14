#pragma once
#include <iostream>

class Health {
    public:
        const float maxHealth = 100;
        const float minHealth = 0;
        float value = 100;

        void LowerHealth(float amount){
            value -= amount;
        }

};