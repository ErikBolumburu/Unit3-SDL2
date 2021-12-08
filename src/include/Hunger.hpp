#pragma once

class Hunger {
    public:
        const float maxHunger = 100;
        const float minHunger = 0;
        float value = 100;

        void DecreaseHunger(float amount){
            value -= amount;
        };

};
