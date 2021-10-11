#include <RenderWindow.hpp>
#include <SDL2/SDL.h>
#include <iostream>
#include <GameObject.hpp>
#include <Vector2.hpp>
#include <Player.hpp>
#include <Platform.hpp>
#include <math.h>
#include <vector>
#include <Game.hpp>
#define FPS 60

int main(int argc, char *argv[]){

    Game game;

    if (SDL_Init(SDL_INIT_VIDEO) > 0)
		std::cout << "SDL_INIT HAS FAILED. ERROR: " << SDL_GetError() << std::endl;
    
    RenderWindow renderWindow;
    renderWindow.window = SDL_CreateWindow("Terraria",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        1280, 960,
        SDL_WINDOW_SHOWN);
    renderWindow.renderer = SDL_CreateRenderer(renderWindow.window, -1, SDL_RENDERER_ACCELERATED);


    Player player(Transform(Vector2(250,200), Vector2(70, 180)));
    game.gameObjects.push_back(&player);
    game.CreatePlatform(Vector2(100, 400), Vector2(300, 100));

    int a;
    int b;
    int delta;
    bool running = true;
    SDL_Event event;
    while(running){
        a = SDL_GetTicks();
        delta = a - b;
        if(delta > 1000 / FPS){
            player.Update();
            //std::cout << "fps: " << 1000 / delta << std::endl;
            while(SDL_PollEvent(&event)){
                player.PlayerInput(event);
                if(event.type == SDL_QUIT){
                    running = false;
                }
            }
            b = a;
            SDL_RenderClear(renderWindow.renderer);

            SDL_SetRenderDrawColor(renderWindow.renderer, 255, 255, 255, 255);
            for(GameObject* go : game.gameObjects){
                SDL_RenderFillRect(renderWindow.renderer, &go->rect);
            }

            SDL_SetRenderDrawColor(renderWindow.renderer, 30, 30, 30, 255);
            SDL_RenderPresent(renderWindow.renderer);
        }
    }

    SDL_DestroyWindow(renderWindow.window);

    return 0;
}