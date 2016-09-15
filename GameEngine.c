#include "GameEngine.h"
#include "Game.h"
#include "GameObject.h"
#include "Player.h"
#include "Timer.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


//Some global engine variables.
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//Note that the renderer and window should never
//need to be touched outside of this file.
SDL_Window *engineWindow = NULL;
SDL_Renderer *engineRenderer = NULL;

TTF_Font *droidFont = NULL;

SDL_Texture *load_rendered_text(char text[], SDL_Color textColor)
{
    //Load text into a texture so that we can call render_image() on it.
    SDL_Texture *newTexture = NULL;
    SDL_Surface *textSurface = TTF_RenderText_Blended(droidFont, text, textColor);

    if(textSurface == NULL){
        printf("Failed to render text surface... SDL_ttf Error: %s", TTF_GetError());
    } else {
        newTexture = SDL_CreateTextureFromSurface(engineRenderer, textSurface);
        if(newTexture == NULL){
            printf("Failed to create texture from surface... SDL Error: %s", SDL_GetError());
        }
        SDL_FreeSurface(textSurface);
    }
    return newTexture;
}

SDL_Texture *load_image_from_file(char path[])
{
    //Load images into the SDL_Texture datatype so that we can call render_image() on it.
	SDL_Texture* newTexture = NULL;
	SDL_Surface* loadedSurface = IMG_Load(path);

	if(loadedSurface == NULL) {
            printf("Unable to load image %s. SDL_image Error: %s", path, IMG_GetError());
	} else {
        newTexture = SDL_CreateTextureFromSurface(engineRenderer, loadedSurface);
		if(newTexture == NULL) {
            printf("Unable to create texture from %s. SDL Error: %s", path, SDL_GetError());
		}
		SDL_FreeSurface(loadedSurface);
	}
	return newTexture;
}

void render_image(int xPosition, int yPosition, int width, int height, float angle, SDL_Texture *texture,
                                    SDL_Rect *sRect, SDL_Point *center, SDL_RendererFlip flip)
{
    //Render an image, either statically (no movement) or dynamically (with movement).
    //Also supports our camera via the *sRect paramater.

    SDL_Rect dRect = {xPosition, yPosition, width, height};
    SDL_RenderCopyEx(engineRenderer, texture, sRect, &dRect, angle, center, flip);
}

bool init_engine()
{
    //Initialize all SDL libraries, create the window and the renderer.
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0){
        printf("Failed to init video... SDL Error: %s", SDL_GetError());
        return false;
    }

    if(!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")){
        printf("Linear texture filtering not enabled....");
    }

    engineWindow = SDL_CreateWindow("Spacey Rocks", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                    SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if(engineWindow == NULL){
        printf("Failed to create window... SDL Error: %s", SDL_GetError());
        return false;
    }

    engineRenderer = SDL_CreateRenderer(engineWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(engineRenderer == NULL){
        printf("Failed to create renderer... SDL Error: %s", SDL_GetError());
        return false;
    }

    int imageFlags = IMG_INIT_PNG;
    if(!(IMG_Init(imageFlags) &imageFlags)){
        printf("SDL_image failed to initialize... SDL_image Error: %s ", IMG_GetError());
        return false;
    }

    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0){
        printf("SDL_mixer failed to initialize... SDL_mixer Error: %s ", Mix_GetError());
        return false;
    }

    if(TTF_Init() == -1){
        printf("SDL_ttf failed to initialize... SDL_ttf Error: %s", TTF_GetError());
        return false;
    }
    return true;
}

bool load_engine()
{
    char pathToDroidFont[] = "fonts/droid.ttf";

    droidFont = TTF_OpenFont(pathToDroidFont, 48);
    if(droidFont == NULL){
        printf("Failed to open font %s ", pathToDroidFont);
        return false;
    }

    return true;
}

void close_engine()
{
    //Cleanup everything.
    SDL_DestroyRenderer(engineRenderer);
    SDL_DestroyWindow(engineWindow);
    TTF_CloseFont(droidFont);

    engineRenderer = NULL;
    engineWindow = NULL;
    droidFont = NULL;

    IMG_Quit();
    TTF_Quit();
    Mix_Quit();
    SDL_Quit();
}

void run_engine()
{
    srand(time(NULL));

    SDL_Event event;
    bool isRunning = true;

    bool didWeInitMenu = false; //Used to call out init functions only once
    bool didWeInitGame = false; //inside of the loop.

    //Load and init the engine and the game by calling relevant functions.
    if(!init_engine()){
        printf("Failed to init engine...");
    }

    if(!load_engine()){
        printf("Failed to load engine...");
    }

    if(!init_game()){
        printf("Failed to init game....");
    }

    if(!load_game()){
        printf("Failed to load game...");
    }

    while(isRunning){
        while(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT){
                isRunning = false;
            }
            handle_player_events(&event);
        }

        //Call SDL_RenderClear at start to avoid the chance of
        //having weird visuals.
        SDL_RenderClear(engineRenderer);

        switch(GAME_STATE_CURRENT) //Check our game state variable...
        {
            case 1: //If equal to N value...
                move_bullet(); //Moving our objects and the player.
                move_player();
                move_camera();
                //Reset the timer
                start();
                render_game();
                break;

            case 2:
                render_menu();
                break;

            case 3:
                printf("Exiting game. Goodbye!");
                isRunning = false;
                break;

            default:
                printf("Something went horribly wrong with the game state system...\n");
                printf("Now exiting game.");
                isRunning = false;
        }

        SDL_RenderPresent(engineRenderer); //Finally, update the frame and render it to the screen.
    }
    close_game(); //If we exit, clean up everything
    close_engine();
}

