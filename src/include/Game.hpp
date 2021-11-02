#pragma once
#include <GameObject.hpp>
#include <Vector2.hpp>
#include <vector>
#include <Wall.hpp>

class Game{ 
    public: // All variables and functions in this section are accessible outside of the script
        std::vector<GameObject*> gameObjects; // A std::vector of gameObjects. I used std::vector so that it is resizeable.

        double deltaTime = 0; // Initialize deltaTime to 0 to ensure it is not allocated a random value.

        void CreateWall(Vector2 pos, Vector2 size){ 
            gameObjects.push_back(new Wall(Transform(pos, size))); // Creates a new Wall object and adds it to the std::vector of gameObjects
        }

        bool CheckCollision(GameObject &a, GameObject &b){
            bool collisionX = a.GetTransform().position.x + a.GetTransform().scale.x >= b.GetTransform().position.x && b.GetTransform().position.x + b.GetTransform().scale.x >= a.GetTransform().position.x;

            bool collisionY = a.GetTransform().position.y + a.GetTransform().scale.y >= b.GetTransform().position.y && b.GetTransform().position.y + b.GetTransform().scale.y >= a.GetTransform().position.y;

            return collisionX && collisionY;
        }
};

extern Game game; // Externalises 'game' so that I can access its data in any file