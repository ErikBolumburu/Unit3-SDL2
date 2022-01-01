#pragma once

class Hunger {
    public:
        const float maxHunger = 100;
        const float minHunger = 0;

        const float starveThreshold = 30;

        const float wellFedThreshold = 70;
        const float wellFedMoveSpeedMultiplier = 1.5f;

        float value = 100;

        void DecreaseHunger(float amount){
            if(value >= minHunger){
                value -= amount;
            }
        };
};
