#pragma once

class Temperature {
    public:
        const float maxTemperature = 100;
        const float minTemperature = 0;

        const float hypothermiaThreshold = 20;
        const float hyperthermiaThreshold = 80;

        bool hypothermia;
        bool hyperthermia;

        float value = 50;

        void DecreaseTemperature(float amount){
            if(value >= minTemperature){
                value -= amount;
            }
        };

        void IncreaseTemperature(float amount){
            if(value <= maxTemperature){
                value += amount;
            }
        };

        void ApplyStatus(){
            if(value < hypothermiaThreshold){
                hypothermia = true;
                hyperthermia = false;
            }
            else if(value > hyperthermiaThreshold){
                hyperthermia = true;
                hypothermia = false;
            }
            else{
                hypothermia = false;
                hyperthermia = false;
            }
        }
};
