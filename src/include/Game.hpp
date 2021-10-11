#pragma once
#include <GameObject.hpp>
#include <Vector2.hpp>
#include <vector>
#include <Platform.hpp>

class Game{
    public:
        std::vector<GameObject*> gameObjects;
        void CreatePlatform(Vector2 pos, Vector2 size){
            gameObjects.push_back(new Platform(Transform(pos, size)));
        }
};

extern Game game;