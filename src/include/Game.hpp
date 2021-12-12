#pragma once
#include <vector>
#include <GameObject.hpp>
#include <World.hpp>

class Game{
    public:
        std::vector<GameObject*> gameObjects;
        World world;

        SDL_DisplayMode dm;

};

extern Game game; // Make any variable with the type Game and name game accessible from anywhere in the program.
