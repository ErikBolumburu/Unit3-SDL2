#include <iostream> 

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

/*
#include <imgui.h>
#include <imgui_impl_sdlrenderer.h>
#include <imgui_impl_sdl.h>
*/

#include <Bar.hpp>
#include <RenderWindow.hpp>
#include <GameObject.hpp>
#include <TestSquare.hpp>
#include <Player.hpp>
#include <Game.hpp>

#define SCREENWIDTH 1280
#define SCREENHEIGHT 720
#define FPS 60

float fps = 0;

int main(){ // Entry Point of the program

    Game game;

    if (SDL_Init(SDL_INIT_VIDEO) > 0) // Initialising SDL_VIDEO
        std::cout << "SDL_INIT HAS FAILED. ERROR: " << SDL_GetError() << std::endl; 

    if (!(IMG_Init(IMG_INIT_PNG))) std::cout << "IMG_init has failed. Error: " << SDL_GetError() << std::endl;


    RenderWindow renderWindow;
    renderWindow.window = SDL_CreateWindow(
            "Unit 3", // Window Name
            SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
            SCREENWIDTH, SCREENHEIGHT, // Resolution
            SDL_WINDOW_SHOWN // Show the window
            );

    renderWindow.renderer = SDL_CreateRenderer(
            renderWindow.window,
            -1, // Automatically chooses the correct flags
            SDL_RENDERER_ACCELERATED // Provides Hardware Acceleration
            );

    if (SDL_GetDesktopDisplayMode(0, &game.dm) != 0)
    {
        SDL_Log("SDL_GetDesktopDisplayMode failed: %s", SDL_GetError());
        return 1;
    }

    /* TODO: COMPILE IMGUI PROPERLY
    ImGui::CreateContext();
    ImGui::StyleColorsClassic();
    ImGui_ImplSDL2_InitForSDLRenderer(renderWindow.window);
    ImGui_ImplSDLRenderer_Init(renderWindow.renderer);
    */

    bool showDebug = false;

    game.world.GenerateWorld();

    SDL_Texture* sandTexture = renderWindow.LoadTexture("/home/ef/dev/csp/assets/sand.png");
    SDL_Texture* grassTexture = renderWindow.LoadTexture("/home/ef/dev/csp/assets/grass.png");
    SDL_Texture* snowTexture = renderWindow.LoadTexture("/home/ef/dev/csp/assets/snow.png");

    SDL_Texture* playerTex = renderWindow.LoadTexture("/home/ef/dev/csp/assets/player.png");

    Player player(Transform(Vector2(0, 0), Vector2(100, 100)));
    
    
    SDL_Color bgBarColor = {30, 30, 30};
    SDL_Color hungerFillColor = {255, 179, 0};
    SDL_Color healthFillColor = {255, 0, 0};
    SDL_Color temperatureFillColor = {0, 0, 255};

    Bar healthBar(Vector2(860, 20), 40, 400, bgBarColor, healthFillColor); 
    Bar hungerBar(Vector2(860, 80), 40, 400, bgBarColor, hungerFillColor);
    Bar temperatureBar(Vector2(860, 140), 40, 400, bgBarColor, temperatureFillColor); 


    int a;
    int b;
    int dT;

    SDL_Event event;
    bool running = true;
    while(running){
        a = SDL_GetTicks();

        Uint64 start = SDL_GetPerformanceCounter();
        dT = a - b;
        if(dT > (1000 / FPS)){

            player.Update();
            player.currentTile = player.GetCurrentTile(game.world);
            std::cout << player.currentTile.type << "\n";

            while(SDL_PollEvent(&event)){
                if(event.type == SDL_QUIT){
                    running = false;
                }
                if(event.type == SDL_KEYDOWN){ 
                    if(event.key.keysym.scancode == SDL_SCANCODE_L){
                        showDebug = !showDebug;
                    }
                }
                player.Movement(event, dT);
                //ImGui_ImplSDL2_ProcessEvent(&event);
            }

            b = a;

            SDL_RenderClear(renderWindow.renderer);

            SDL_SetRenderDrawColor(renderWindow.renderer, 255, 255, 255, 255); 

            /*
            ImGui_ImplSDLRenderer_NewFrame();
            ImGui_ImplSDL2_NewFrame();

            ImGui::NewFrame();
            {
                if(showDebug){
                    ImGui::Text("FPS: %f", 1.0f / fps);
                    ImGui::SliderFloat("Hunger: ", &player.hunger.value, player.hunger.minHunger, player.hunger.maxHunger);
                    ImGui::SliderFloat("Health: ", &player.health.value, player.health.minHealth, player.health.maxHealth);
                    ImGui::SliderFloat("Temperature: ", &player.temperature.value, player.temperature.minTemperature, player.temperature.maxTemperature);
                    ImGui::SliderFloat("Move Speed: ", &player.moveSpeed, 0, 1);
                }
            }
            */
            game.world.RenderWorld(renderWindow, player.transform.position, grassTexture, sandTexture, snowTexture);

            SDL_RenderCopy(renderWindow.renderer, playerTex, NULL, &player.rect);

            healthBar.RenderBar(renderWindow.renderer, player.health.value / player.health.maxHealth); 
            hungerBar.RenderBar(renderWindow.renderer, player.hunger.value / player.hunger.maxHunger); 
            temperatureBar.RenderBar(renderWindow.renderer, player.temperature.value / player.temperature.maxTemperature); 

            SDL_SetRenderDrawColor(renderWindow.renderer, 30, 30, 30, 255); 
            //ImGui::Render();
            //ImGui_ImplSDLRenderer_RenderDrawData(ImGui::GetDrawData());
            SDL_RenderPresent(renderWindow.renderer);
            Uint64 end = SDL_GetPerformanceCounter();
            fps = (end - start) / (float)SDL_GetPerformanceFrequency();
        }
    }


    /*
    ImGui_ImplSDLRenderer_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
    */
    SDL_DestroyWindow(renderWindow.window); // Safely destroys the window.

    return 0;
}