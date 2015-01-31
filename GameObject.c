#include "GameObject.h"
#include "Game.h"
#include "Player.h"
#include <stdio.h>

SDL_Texture *bulletTexture = NULL;
SDL_Texture *asteroidTexture = NULL;

const int BULLET_VELOCITY = 5;
const int MAX_BULLETS = 25;
const int MAX_ASTEROIDS = 15;

void create_object()
{
    //Allocate memory to an array of type *object.
    objectStorage = malloc(sizeof(object) * 100);

    //Create the bullets
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

    //Create the asteroids, start where the last bullet object left off at.
    for(int i = MAX_BULLETS; i < MAX_BULLETS + MAX_ASTEROIDS; i++){
        objectStorage[i].texture = asteroidTexture;
        objectStorage[i].xPosition = 150;
        objectStorage[i].yPosition = 150;
        objectStorage[i].xVelocity = 0;
        objectStorage[i].yVelocity = 0;
        objectStorage[i].width = 70;
        objectStorage[i].height = 70;
        objectStorage[i].angle = 0;
        objectStorage[i].isDead = false;
    }
}

bool load_object()
{
    //Load images, and store them in the appropriate SDL_Texture
    char pathToBulletImage[] = "images/bullet.png";
    char pathToAsteroidImage[] = "images/asteroid.png";

    bulletTexture = load_image_from_file(pathToBulletImage);
    if(bulletTexture == NULL){
        printf("Failed to load %s", pathToBulletImage);
        return false;
    }

    asteroidTexture = load_image_from_file(pathToAsteroidImage);
    if(asteroidTexture == NULL){
        printf("Failed to load %s ", pathToAsteroidImage);
        return false;
    }

    return true;
}

void move_bullet()
{
    //Move our bullets if they are not dead.
    //Set the point of origin for spawning bullets
    //to the player.
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
    //Render moving objects, namely the bullets
    for(int i = 0; i < MAX_BULLETS; i++){
        if(!objectStorage[i].isDead){
            render_image(objectStorage[i].xPosition, objectStorage[i].yPosition, objectStorage[i].width,
                        objectStorage[i].height, objectStorage[i].angle, objectStorage[i].texture, NULL, NULL, SDL_FLIP_NONE);
        }
    }

    //Render stationary objects, like asteroids.
    for(int i = MAX_BULLETS; i < MAX_BULLETS + MAX_ASTEROIDS; i++){
        if(!objectStorage[i].isDead){
            render_image(objectStorage[i].xPosition - camera.x - camera.x, objectStorage[i].yPosition - camera.y - camera.y, objectStorage[i].width,
                        objectStorage[i].height, objectStorage[i].angle, objectStorage[i].texture, NULL, NULL, SDL_FLIP_NONE);
        }
    }
}

void free_object_resources()
{
    //Cleanup resources
    free(objectStorage);
}
