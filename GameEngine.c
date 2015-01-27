#include "GameEngine.h"
#include "Game.h"
#include "Player.h"
#include <stdio.h>
#include <stdlib.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDL_Window *engineWindow = NULL;
SDL_Renderer *engineRenderer = NULL;

SDL_Texture *load_rendered_text(char text[], TTF_Font *font, SDL_Color textColor)
{
    SDL_Texture *newTexture = NULL;
    SDL_Surface *textSurface = TTF_RenderText_Blended(font, text, textColor);

    if(textSurface == NULL){
        printf("Failed to render text surface... SDL_ttf Error: %s", TTF_GetError());
    } else {
        newTexture = SDL_CreateTextureFromSurface(engineRenderer, textSurface);
        if(newTexture == NULL){
            printf("Failed to create texture from surface... SDL Error: ", SDL_GetError());
        }
        SDL_FreeSurface(textSurface);
    }
    return newTexture;
}

SDL_Texture *load_image_from_file(char path[])
{
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
    SDL_Rect dRect = {xPosition, yPosition, width, height};
    SDL_RenderCopyEx(engineRenderer, texture, sRect, &dRect, angle, center, flip);
}

bool init_engine()
{
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0){
        printf("Failed to init video... SDL Error: %s", SDL_GetError());
        return false;
    }

    if(!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")){
        printf("Linear texture filtering not enabled....");
    }

    engineWindow = SDL_CreateWindow("Game Engine", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
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
    return true;
}

void close_engine()
{
    SDL_DestroyRenderer(engineRenderer);
    SDL_DestroyWindow(engineWindow);

    engineRenderer = NULL;
    engineWindow = NULL;
}

void run_engine()
{
    SDL_Event event;
    bool isRunning = true;

    if(!init_engine()){
        printf("Failed to init engine...");
    }

    if(!load_engine()){
        printf("Failed to load engine...");
    }

    if(!init_game){
        printf("Failed to init game...");
    }

    if(!load_game()){
        printf("Failed to load game...");
    }

    while(isRunning){
        while(SDL_PollEvent(&event) != 0){
            if(event.type == SDL_QUIT){
                isRunning = false;
            }
            handle_player_events(event);
        }
        SDL_RenderClear(engineRenderer);

        move_player();
        render_game();

        SDL_RenderPresent(engineRenderer);
    }
    close_game();
    close_engine();
}

