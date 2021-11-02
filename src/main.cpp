#include <RenderWindow.hpp>
#include <SDL2/SDL.h>
#include <iostream>
#include <GameObject.hpp>
#include <Vector2.hpp>
#include <Player.hpp>
#include <Wall.hpp>
#include <math.h>
#include <vector>
#include <Game.hpp>

Game game;

int main(int argc, char *argv[]){

    if (SDL_Init(SDL_INIT_VIDEO) > 0) // Initializing SDL_VIDEO module
		std::cout << "SDL_INIT HAS FAILED. ERROR: " << SDL_GetError() << std::endl; // If there is an error, print it out for debugging purposes
    
    RenderWindow renderWindow; // Create a new RenderWindow class
    renderWindow.window = SDL_CreateWindow("Terraria",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        1280, 960,
        SDL_WINDOW_SHOWN); // Define paramaters for the SDL_Window class within renderWindow
    renderWindow.renderer = SDL_CreateRenderer(renderWindow.window, -1, SDL_RENDERER_ACCELERATED); // Create an SDL_Renderer and define its parameters


    Player player(Transform(Vector2(0,0), Vector2(50, 50))); // Create the player object
    game.gameObjects.push_back(&player); // Add it to the game.gameObjects vector
    game.CreateWall(Vector2(100, 100), Vector2(300, 20)); // Create a wall to test player collision
    game.CreateWall(Vector2(400, 100), Vector2(20, 300)); // Create a wall to test player collision

    bool running = true; // Initialize the 'running' bool used in the main game loop as true
    SDL_Event event; // Create an SDL_Event object called event to handle inputs and other events
    Uint64 now = SDL_GetPerformanceCounter(); // Get the current performance counter and store it in now. Used in measuring the delta time below
    Uint64 last = 0; // Initialize the 'last' variable as 0 so it is not assigned the value from whatever was in the memory address before
    while(running){ // Infinite, main game loop where all game logic happens. True until the player quits
        last = now; // Assigning 'last's value to now in order to remember last frames value
        now = SDL_GetPerformanceCounter(); // Assigning 'now's value to the current performance counter

        game.deltaTime = (double)((now - last) / (double)SDL_GetPerformanceFrequency()); // Calculating the current delta time (time between frames) in order to gain frame independance in certain parts of the game
        player.Update(); // Run the players Update() function every frame 
        while(SDL_PollEvent(&event)){ // Whilst SDL is listening for events from the 'event' variable
            player.PlayerInput(event); // Run the PlayerInput() function which captures inputs from the player and generates the expected output.
            if(event.type == SDL_QUIT){ // If the player quits
                running = false; // Stop the current main game loop
            }
        }
        SDL_RenderClear(renderWindow.renderer); // Clear the screen to prepare to render the current frame

        SDL_SetRenderDrawColor(renderWindow.renderer, 255, 255, 255, 255); // Set the current render color to white. This means that anything drawn after this point will be white, unless changed again.
        for(GameObject* go : game.gameObjects){ // Loop through all the GameObjects in game.gameObjects
            SDL_RenderFillRect(renderWindow.renderer, &go->rect); // Render every GameObject based on their current SDL_Rect 'rect'
            if(dynamic_cast<Wall*>(go)){ // If the current GameObject has the type 'Wall'
                if(game.CheckCollision(player, *go)){ // If a collision between the player and the wall is detected
                    // Stop the player from moving through the gameObject
                }
            }
        }

        SDL_SetRenderDrawColor(renderWindow.renderer, 30, 30, 30, 255); // Set the current render color to a dark gray. This means that anything drawn after this point will be dark gray, unless changed again.
        SDL_RenderPresent(renderWindow.renderer); // Render everything in the render buffer and display it to the window
    }

    SDL_DestroyWindow(renderWindow.window); // Cleanly destroy the window

    return 0; // Return 0 (could be any value) in order to close the 'main' function
}