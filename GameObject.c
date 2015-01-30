#include "GameObject.h"
#include "Game.h"
#include "Player.h"
#include <stdio.h>

SDL_Texture *bulletTexture = NULL;
const int BULLET_VELOCITY = 5;
const int MAX_BULLETS = 25;

void create_object()
{
    objectStorage = malloc(sizeof(object) * 100);

    for(int i = 0; i < MAX_BULLETS; i++){
        objectStorage[i].texture = bulletTexture;
        objectStorage[i].xPosition = 50;
        objectStorage[i].yPosition = 50;
        objectStorage[i].xVelocity = 0;
        objectStorage[i].yVelocity = 0;
        objectStorage[i].width = 25;
        objectStorage[i].height = 50;
        objectStorage[i].angle = 0;
        objectStorage[i].isDead = true;
    }
}

bool load_object()
{
    char pathToBulletImage[] = "2d_game_engine_c/images/bullet.png";

    bulletTexture = load_image_from_file(pathToBulletImage);
    if(bulletTexture == NULL){
        printf("Failed to load bullet.png");
        return false;
    }
    return true;
}

void move_bullet()
{
    for(int i = 0; i < MAX_BULLETS; i++){
        if(!objectStorage[i].isDead){
            objectStorage[i].xPosition += objectStorage[i].xVelocity;
            objectStorage[i].yPosition += objectStorage[i].yVelocity;
        }

        if(objectStorage[i].xPosition < 0 || objectStorage[i].xPosition > SCREEN_WIDTH ||
                objectStorage[i].yPosition < 0 || objectStorage[i].yPosition > SCREEN_HEIGHT){

            objectStorage[i].isDead = true;
        }

        if(objectStorage[i].isDead){
            objectStorage[i].xPosition = playerPositionX - camera.x;
            objectStorage[i].yPosition = playerPositionY - camera.y;
        }
    }
}

void render_object()
{
    for(int i = 0; i < MAX_BULLETS; i++){
        if(!objectStorage[i].isDead){
            render_image(objectStorage[i].xPosition, objectStorage[i].yPosition, objectStorage[i].width,
                        objectStorage[i].height, objectStorage[i].angle, objectStorage[i].texture, NULL, NULL, SDL_FLIP_NONE);
        }
    }
}

void free_object_resources()
{
    for(int i = 0; i < MAX_BULLETS; i++){
        free(objectStorage);
    }
}
