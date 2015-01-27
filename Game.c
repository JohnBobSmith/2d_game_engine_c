#include "Game.h"
#include<stdio.h>

SDL_Texture *backgroundTexture = NULL;
char pathToImage[] = "images/background.png";

bool init_game()
{
    return true;
}

bool load_game()
{
    backgroundTexture = load_image_from_file(pathToImage);
    if(backgroundTexture == NULL){
        printf("Failed to load %s. Image not found!", pathToImage);
        return false;
    }
    return true;
}

void render_game()
{
    render_image(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, backgroundTexture, NULL, NULL, SDL_FLIP_NONE);
}

void close_game()
{
    SDL_DestroyTexture(backgroundTexture);
    backgroundTexture = NULL;
}
