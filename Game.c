#include "Game.h"
#include "Player.h"
#include<stdio.h>

SDL_Texture *backgroundTexture = NULL;
char pathToImage[] = "2d_game_engine_c/images/background.png";

bool init_game()
{
    if(!init_player()){
        printf("Failed to init player...");
        return false;
    }
    return true;
}

bool load_game()
{
    backgroundTexture = load_image_from_file(pathToImage);
    if(backgroundTexture == NULL){
        printf("Failed to load %s. Image not found!", pathToImage);
        return false;
    }

    if(!load_player()){
        printf("Failed to load player...");
        return false;
    }

    return true;
}

void render_game()
{
    render_image(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, backgroundTexture, NULL, NULL, SDL_FLIP_NONE);
    render_player();
}

void close_game()
{
    SDL_DestroyTexture(backgroundTexture);
    backgroundTexture = NULL;
    free_player_resources();
}
