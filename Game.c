#include "Game.h"
#include "GameObject.h"
#include "Player.h"
#include<stdio.h>

//Some global game variables
SDL_Texture *backgroundTexture = NULL;
SDL_Texture *menuTexture = NULL;

GAME_STATE_CURRENT = 2; //The current state of the game.
//For the above variable, 3 is exit, 2 is menu, 1 is playing.
const int LEVEL_WIDTH = 1280;
const int LEVEL_HEIGHT = 960;

bool init_game()
{
    //initialize and load our player and the camera, and all game objects.
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
    //Load all our images into the SDL_Texture datatype.
    char pathToBackgroundImage[] = "images/background.png";
    char pathToMainMenuImage[] = "images/mainmenu_bg.png";

    backgroundTexture = load_image_from_file(pathToBackgroundImage);
    if(backgroundTexture == NULL){
        printf("Failed to load %s. Image not found!", pathToBackgroundImage);
        return false;
    }

    menuTexture = load_image_from_file(pathToMainMenuImage);
    if(menuTexture == NULL){
        printf("Failed to load %s. Image not found!", pathToMainMenuImage);
        return false;
    }

    return true;
}

void init_game_state_menu()
{
    for(int i = 0; i < MAX_BUTTONS; i++){
        objectStorage[i].isDead = false;
    }

    for(int i = MAX_BUTTONS; i < MAX_BULLETS + MAX_ASTEROIDS; i++){
        objectStorage[i].isDead = true;
    }
}

void init_game_state_play()
{
    for(int i = 0; i < MAX_BUTTONS; i++){
        objectStorage[i].isDead = true;
    }

    for(int i = MAX_BUTTONS; i < MAX_BULLETS; i++){
        objectStorage[i].isDead = true;
    }

    for(int i = MAX_BULLETS; i < MAX_BULLETS + MAX_ASTEROIDS; i++){
        objectStorage[i].isDead = false;
    }
}

void move_camera()
{
    //Move the camera based on the players current position.
    camera.x = (playerPositionX + playerWidth / 2) - SCREEN_WIDTH / 2;
    camera.y = (playerPositionY + playerHeight / 2) - SCREEN_HEIGHT / 2;

    //If the camera moves off screen in any way...
    if(camera.x < 0) {
        camera.x = 0; //Stop camera movement, while allowing our player to move.
    }

    //Likewise for these next 3 conditions.
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
    //Render all images. Note the order in which we render these images!
    //The background must always be first!
    render_image(0, 0, LEVEL_WIDTH, LEVEL_HEIGHT, 0, backgroundTexture, &camera, NULL, SDL_FLIP_NONE);
    render_player(camera.x, camera.y);
    render_object();
}

void render_menu()
{
    render_image(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, menuTexture, NULL, NULL, SDL_FLIP_NONE);
    render_object();
}


void close_game()
{
    //Free our resources
    SDL_DestroyTexture(backgroundTexture);
    backgroundTexture = NULL;
    free_player_resources();
}
