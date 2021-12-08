#include <iostream> 
#include <Bar.hpp>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <RenderWindow.hpp>
#include <GameObject.hpp>
#include <TestSquare.hpp>
#include <Player.hpp>
#include <Game.hpp>

int main(){ // Entry Point of the program

    Game game;

    if (SDL_Init(SDL_INIT_VIDEO) > 0) // Initialising SDL_VIDEO
        std::cout << "SDL_INIT HAS FAILED. ERROR: " << SDL_GetError() << std::endl; 

    if (!(IMG_Init(IMG_INIT_PNG))) std::cout << "IMG_init has failed. Error: " << SDL_GetError() << std::endl;

    if (SDL_GetDesktopDisplayMode(0, &game.dm) != 0)
    {
         SDL_Log("SDL_GetDesktopDisplayMode failed: %s", SDL_GetError());
         return 1;
    }


    RenderWindow renderWindow;
    renderWindow.window = SDL_CreateWindow(
            "Unit 3", // Window Name
            SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
            1920, 1080, // Resolution
            SDL_WINDOW_SHOWN // Show the window
            );

    renderWindow.renderer = SDL_CreateRenderer(
            renderWindow.window,
            -1, // Automatically chooses the correct flags
            SDL_RENDERER_ACCELERATED // Provides Hardware Acceleration
            );

    game.world.GenerateWorld();

    SDL_Texture* sandTexture = renderWindow.LoadTexture("assets/sand.png");
    SDL_Texture* grassTexture = renderWindow.LoadTexture("assets/grass.png");
    SDL_Texture* snowTexture = renderWindow.LoadTexture("assets/snow.png");

    SDL_Texture* playerTex = renderWindow.LoadTexture("assets/player.png");

    // Creates A Test Square at X100 Y100 and is 100px wide and tall
    Player player(Transform(Vector2(100, 100), Vector2(100, 100)), game.dm.w, game.dm.h);
    
    SDL_Color bgBarColor;
    bgBarColor.r = 30;
    bgBarColor.g = 30;
    bgBarColor.b = 30;
    bgBarColor.a = 255;

    SDL_Color fillColor;
    bgBarColor.r = 201;
    bgBarColor.g = 148;
    bgBarColor.b = 40;
    bgBarColor.a = 255;

    Bar hungerBar(Vector2(1500, 100), 40, 400, bgBarColor, fillColor); 

    SDL_Event event;
    bool running = true;
    while(running){
        player.Update();
        while(SDL_PollEvent(&event)){
            player.Movement(event);
            if(event.type == SDL_QUIT){
                running = false;
            }
        }

        SDL_RenderClear(renderWindow.renderer);
        SDL_SetRenderDrawColor(renderWindow.renderer, 255, 255, 255, 255); 
        game.world.RenderWorld(renderWindow, player.transform.position, grassTexture, sandTexture, snowTexture);
        SDL_RenderCopy(renderWindow.renderer, playerTex, NULL, &player.rect);
        hungerBar.RenderBar(renderWindow.renderer, 0.4); 
        SDL_SetRenderDrawColor(renderWindow.renderer, 30, 30, 30, 255); 
        SDL_RenderPresent(renderWindow.renderer);
    }

    SDL_DestroyWindow(renderWindow.window); // Safely destroys the window.

    return 0;
}
