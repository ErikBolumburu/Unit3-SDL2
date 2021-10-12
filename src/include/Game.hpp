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

        bool CheckCollision(GameObject &a, GameObject &b){
            bool collisionX = a.GetTransform().position.x + a.GetTransform().scale.x >= b.GetTransform().position.x && b.GetTransform().position.x + b.GetTransform().scale.x >= a.GetTransform().position.x;

            bool collisionY = a.GetTransform().position.y + a.GetTransform().scale.y >= b.GetTransform().position.y && b.GetTransform().position.y + b.GetTransform().scale.y >= a.GetTransform().position.y;

            return collisionX && collisionY;
        }
};

extern Game game;