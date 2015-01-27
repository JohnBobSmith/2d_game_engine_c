#include "Player.h"
#include "Game.h"
#include <stdio.h>

bool init_player()
{
    playerTexture = NULL;

    const int PLAYER_VELOCITY = 2;

    playerPositionX = 50;
    playerPositionY = 50;

    playerVelocityX = 0;
    playerVelocityY = 0;

    playerWidth = 50;
    playerHeight = 50;

    return true;
}

bool load_player()
{
    char pathToImage[] = "2d_game_engine_c/images/player.png";

    playerTexture = load_image_from_file(pathToImage);
    if(playerTexture == NULL){
        printf("Failed to load %s. Image not found!", pathToImage);
        return false;
    }
    return true;
}

void handle_player_events(SDL_Event event)
{
    if(event.type == SDL_KEYDOWN && event.key.repeat == 0)
    {
        switch(event.key.keysym.sym)
        {
            case SDLK_w:
            case SDLK_UP:
                playerVelocityY -= PLAYER_VELOCITY;
                break;

            case SDLK_s:
            case SDLK_DOWN:
                playerVelocityY += PLAYER_VELOCITY;
                break;

            case SDLK_a:
            case SDLK_LEFT:
                playerVelocityX -= PLAYER_VELOCITY;
                break;

            case SDLK_d:
            case SDLK_RIGHT:
                playerVelocityX += PLAYER_VELOCITY;
                break;
        }
    }

    else if(event.type == SDL_KEYUP && event.key.repeat == 0)
    {
        switch(event.key.keysym.sym)
        {
            case SDLK_w:
            case SDLK_UP:
                playerVelocityY += PLAYER_VELOCITY;
                break;

            case SDLK_s:
            case SDLK_DOWN:
                playerVelocityY -= PLAYER_VELOCITY;
                break;

            case SDLK_a:
            case SDLK_LEFT:
                playerVelocityX += PLAYER_VELOCITY;
                break;

            case SDLK_d:
            case SDLK_RIGHT:
                playerVelocityX -= PLAYER_VELOCITY;
                break;
        }
    }
}

void move_player()
{
    playerPositionX += playerVelocityX;
    playerPositionY += playerVelocityY;

    if(playerPositionX < 0 || (playerPositionX + playerWidth) > SCREEN_WIDTH){
        playerPositionX -= playerVelocityX;
    }

    if(playerPositionY < 0 || (playerPositionY + playerHeight) > SCREEN_HEIGHT){
        playerPositionY -= playerVelocityY;
    }

}

void render_player()
{
    render_image(playerPositionX, playerPositionY, playerWidth, playerHeight, 0, playerTexture, NULL, NULL, SDL_FLIP_NONE);
}

void free_player_resources()
{
    SDL_DestroyTexture(playerTexture);
    playerTexture = NULL;
}
