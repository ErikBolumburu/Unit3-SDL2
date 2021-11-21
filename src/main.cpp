#include <iostream> 
#include <SDL2/SDL.h>
#include <RenderWindow.hpp>
#include <GameObject.hpp>
#include <TestSquare.hpp>

int main(){ // Entry Point of the program
    if (SDL_Init(SDL_INIT_VIDEO) > 0) // Initialising SDL_VIDEO
        std::cout << "SDL_INIT HAS FAILED. ERROR: " << SDL_GetError() << std::endl; 

    RenderWindow renderWindow;
    renderWindow.window = SDL_CreateWindow(
            "Unit 3", // Window Name
            SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
            1280, 960, // Resolution
            SDL_WINDOW_SHOWN // Show the window
            );

    renderWindow.renderer = SDL_CreateRenderer(
            renderWindow.window,
            -1, // Automatically chooses the correct flags
            SDL_RENDERER_ACCELERATED // Provides Hardware Acceleration
            );

    // Creates A Test Square at X100 Y100 and is 100px wide and tall
    TestSquare testSquare(Transform(Vector2(100, 100), Vector2(100, 100)));

    SDL_Event event;
    bool running = true;
    while(running){

        while(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT){
                running = false;
            }
        }

        SDL_RenderClear(renderWindow.renderer);
        SDL_SetRenderDrawColor(renderWindow.renderer, 255, 255, 255, 255); // White
        SDL_RenderFillRect(renderWindow.renderer, &testSquare.rect);
        SDL_SetRenderDrawColor(renderWindow.renderer, 30, 30, 30, 255); // Set the draw color to dark gray
        SDL_RenderPresent(renderWindow.renderer);
    }

    SDL_DestroyWindow(renderWindow.window); // Safely destroys the window.
        
    return 0;
}
