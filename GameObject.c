#include "GameObject.h"
#include "Game.h"
#include "Player.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

SDL_Texture *bulletTexture = NULL;
SDL_Texture *asteroidTexture = NULL;

const int BULLET_VELOCITY = 7;
const int MAX_BULLETS = 25;
const int MAX_ASTEROIDS = 60;

int currentAsteroid = 25;

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
        objectStorage[i].xPosition = 0 ;
        objectStorage[i].yPosition = 0;
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

        for(int j = MAX_BULLETS; j < MAX_BULLETS + MAX_ASTEROIDS; j++){
            if(!objectStorage[i].isDead && !objectStorage[j].isDead){
                if(check_collision(objectStorage[i].xPosition, objectStorage[i].yPosition, objectStorage[i].width,
                            objectStorage[i].height, objectStorage[j].xPosition - camera.x - camera.x,
                            objectStorage[j].yPosition - camera.y - camera.y, objectStorage[j].width, objectStorage[j].height)){

                    objectStorage[i].isDead = true;
                    objectStorage[j].isDead = true;
                }
            }
        }
    }
}

void randomize_asteroid_position()
{
    //Randomize the asteroid positions.
    int randomXPosition = rand() % (LEVEL_WIDTH - 100);
    int randomYPosition = rand() % (LEVEL_HEIGHT - 100);
    int randomAngle = rand() % 360;

    //start randomization where bullets left off.
    objectStorage[currentAsteroid].xPosition = randomXPosition;
    objectStorage[currentAsteroid].yPosition = randomYPosition;
    objectStorage[currentAsteroid].angle = randomAngle;

    currentAsteroid += 1;
}

bool check_collision(int xA, int yA, int wA, int hA, int xB, int yB, int wB, int hB)
{
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    leftA = xA;
    rightA = xA + wA;
    topA = yA;
    bottomA = yA + hA;

    leftB = xB;
    rightB = xB + wB;
    topB = yB;
    bottomB = yB + hB;

    if(bottomA <= topB){
        return false;
    }

    if(topA >= bottomB){
        return false;
    }

    if(rightA <= leftB){
        return false;
    }

    if(leftA >= rightB){
        return false;
    }

    return true;
}

void render_object()
{
    //Render moving objects, namely the bullets
    for(int i = 0; i < MAX_BULLETS; i++){
        if(!objectStorage[i].isDead){
            render_image(objectStorage[i].xPosition - camera.x, objectStorage[i].yPosition - camera.y, objectStorage[i].width,
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
