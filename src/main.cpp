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

Game game;

int main(int argc, char *argv[]){

    if (SDL_Init(SDL_INIT_VIDEO) > 0)
		std::cout << "SDL_INIT HAS FAILED. ERROR: " << SDL_GetError() << std::endl;
    
    RenderWindow renderWindow;
    renderWindow.window = SDL_CreateWindow("Terraria",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        1280, 960,
        SDL_WINDOW_SHOWN);
    renderWindow.renderer = SDL_CreateRenderer(renderWindow.window, -1, SDL_RENDERER_ACCELERATED);


    Player player(Transform(Vector2(0,0), Vector2(70, 180)));
    game.gameObjects.push_back(&player);
    game.CreatePlatform(Vector2(100, 400), Vector2(300, 100));
    game.CreatePlatform(Vector2(0, 300), Vector2(200, 30));

    bool running = true;
    SDL_Event event;
    Uint64 now = SDL_GetPerformanceCounter();
    Uint64 last = 0;
    while(running){
        last = now;
        now = SDL_GetPerformanceCounter();

        game.deltaTime = (double)((now - last) / (double)SDL_GetPerformanceFrequency() );
        player.Update();
        while(SDL_PollEvent(&event)){
            player.PlayerInput(event);
            if(event.type == SDL_QUIT){
                running = false;
            }
        }
        SDL_RenderClear(renderWindow.renderer);

        SDL_SetRenderDrawColor(renderWindow.renderer, 255, 255, 255, 255);
        player.grounded = false;
        for(GameObject* go : game.gameObjects){
            SDL_RenderFillRect(renderWindow.renderer, &go->rect);
            if(auto* platform = dynamic_cast<Platform*>(go)){
                if(game.CheckCollision(player, *go)){
                    player.grounded = true;
                }
            }
        }

        SDL_SetRenderDrawColor(renderWindow.renderer, 30, 30, 30, 255);
        SDL_RenderPresent(renderWindow.renderer);
    }

    SDL_DestroyWindow(renderWindow.window);

    return 0;
}