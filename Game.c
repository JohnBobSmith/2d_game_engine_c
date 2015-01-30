#include "Game.h"
#include "GameObject.h"
#include "Player.h"
#include<stdio.h>

SDL_Texture *backgroundTexture = NULL;

const int LEVEL_WIDTH = 1280;
const int LEVEL_HEIGHT = 960;

char pathToImage[] = "2d_game_engine_c/images/background.png";

bool init_game()
{
    camera.x = 0;
    camera.y = 0;
    camera.w = SCREEN_WIDTH;
    camera.h = SCREEN_HEIGHT;

    if(!init_player()){
        printf("Failed to init player...");
        return false;
    }

    if(!load_player()){
        printf("Failed to load player...");
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
    return true;
}

void move_camera()
{
    camera.x = (playerPositionX + playerWidth / 2) - SCREEN_WIDTH / 2;
    camera.y = (playerPositionY + playerHeight / 2) - SCREEN_HEIGHT / 2;

    if(camera.x < 0) {
        camera.x = 0;
    }

    if(camera.y < 0){
        camera.y = 0;
    }

    if(camera.x > LEVEL_WIDTH - camera.w) {
        camera.x = LEVEL_WIDTH - camera.w;
    }

    if(camera.y > LEVEL_HEIGHT - camera.h) {
        camera.y = LEVEL_HEIGHT - camera.h;
    }
}

void render_game()
{
    render_image(0, 0, LEVEL_WIDTH, LEVEL_HEIGHT, 0, backgroundTexture, &camera, NULL, SDL_FLIP_NONE);
    render_player(camera.x, camera.y);
    render_object();
}

void close_game()
{
    SDL_DestroyTexture(backgroundTexture);
    backgroundTexture = NULL;
    free_player_resources();
}
