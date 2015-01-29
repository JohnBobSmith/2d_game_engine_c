#include "Player.h"
#include "Game.h"
#include <math.h>
#include <stdio.h>

SDL_Texture *playerTexture = NULL;
const int PLAYER_VELOCITY = 2;
char pathToPlayerImage[] = "2d_game_engine_c/images/player.png";

bool init_player()
{
    playerPositionX = 50;
    playerPositionY = 50;

    playerVelocityX = 0;
    playerVelocityY = 0;

    playerWidth = 50;
    playerHeight = 50;

    playerAngle = 0;

    return true;
}

bool load_player()
{
    playerTexture = load_image_from_file(pathToPlayerImage);
    if(playerTexture == NULL){
        printf("Failed to load %s. Image not found!", pathToPlayerImage);
        return false;
    }
    return true;
}

void handle_player_events(SDL_Event *event)
{
    int xCenter, yCenter;
    int mouseX, mouseY;
    int result;

    if(event->type == SDL_KEYDOWN && event->key.repeat == 0){
        switch(event->key.keysym.sym){
            case SDLK_UP:
                playerVelocityY -= PLAYER_VELOCITY;
                break;

            case SDLK_DOWN:
                playerVelocityY += PLAYER_VELOCITY;
                break;

            case SDLK_LEFT:
                playerVelocityX -= PLAYER_VELOCITY;
                break;

            case SDLK_RIGHT:
                playerVelocityX += PLAYER_VELOCITY;
                break;
        }
    }

    if(event->type == SDL_KEYUP && event->key.repeat == 0){
        switch(event->key.keysym.sym){
            case SDLK_UP:
                playerVelocityY += PLAYER_VELOCITY;
                break;

            case SDLK_DOWN:
                playerVelocityY -= PLAYER_VELOCITY;
                break;

            case SDLK_LEFT:
                playerVelocityX += PLAYER_VELOCITY;
                break;

            case SDLK_RIGHT:
                playerVelocityX -= PLAYER_VELOCITY;
                break;
        }
    }

    if(event->type == SDL_MOUSEMOTION){
        SDL_GetMouseState(&mouseX, &mouseY);

        xCenter = playerPositionX - camera.x + playerWidth / 2;
        yCenter = playerPositionY - camera.y + playerHeight / 2;
        result = atan2(mouseY - yCenter, mouseX - xCenter) * 180 / 3.14;

        playerAngle = result;

    }
}

void move_player()
{
    playerPositionX += playerVelocityX;
    playerPositionY += playerVelocityY;

    if(playerPositionX < 0 || (playerPositionX + playerWidth) > LEVEL_WIDTH){
        playerPositionX -= playerVelocityX;
    }

    if(playerPositionY < 0 || (playerPositionY + playerHeight) > LEVEL_HEIGHT){
        playerPositionY -= playerVelocityY;
    }
}


void render_player(int camX, int camY)
{
    render_image(playerPositionX - camX, playerPositionY - camY, playerWidth, playerHeight, playerAngle, playerTexture, NULL, NULL, SDL_FLIP_NONE);
}

void free_player_resources()
{
    SDL_DestroyTexture(playerTexture);
    playerTexture = NULL;
}
