#include "GameObject.h"
#include "Game.h"
#include "Player.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

SDL_Texture *bulletTexture = NULL;
SDL_Texture *asteroidTexture = NULL;
SDL_Texture *buttonTexture = NULL;
SDL_Texture *fontTexture01 = NULL;
SDL_Texture *fontTexture02 = NULL;

const int BULLET_VELOCITY = 7;
const int MAX_BUTTONS = 2;
const int MAX_BULLETS = 25;
const int MAX_ASTEROIDS = 15;

int currentAsteroid = 25;

void create_object()
{
    //Allocate memory to an array of type *object.
    objectStorage = malloc(sizeof(object) * 100);

    for(int i = 0; i < MAX_BUTTONS; i++){
        objectStorage[i].texture = buttonTexture;
        objectStorage[i].fontTexture = NULL;
        objectStorage[i].xPosition = 250;
        objectStorage[i].yPosition = 250;
        objectStorage[i].xVelocity = 0;
        objectStorage[i].yVelocity = 0;
        objectStorage[i].width = 256;
        objectStorage[i].height = 96;
        objectStorage[i].angle = 0;
        objectStorage[i].isDead = true;
    }

    //Create the bullets. Start where the last button object left off at.
    for(int i = MAX_BUTTONS; i < MAX_BULLETS; i++){
        objectStorage[i].texture = bulletTexture;
        objectStorage[i].fontTexture = NULL;
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
        objectStorage[i].fontTexture = NULL;
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
    char pathToButtonImage[] = "images/button.png";

    char text01[] = "PLAY";
    char text02[] = "EXIT";

    SDL_Color textColor = {255, 255, 255, 255};

    bulletTexture = load_image_from_file(pathToBulletImage);
    if(bulletTexture == NULL){
        printf("Failed to load %s ", pathToBulletImage);
        return false;
    }

    asteroidTexture = load_image_from_file(pathToAsteroidImage);
    if(asteroidTexture == NULL){
        printf("Failed to load %s ", pathToAsteroidImage);
        return false;
    }

    buttonTexture = load_image_from_file(pathToButtonImage);
    if(buttonTexture == NULL){
        printf("Failed to load %s. ", pathToButtonImage);
        return false;
    }

    fontTexture01 = load_rendered_text(text01, textColor);
    if(fontTexture01 == NULL){
        printf("Failed to load rendered text for fontTexture01...");
        return false;
    }

    fontTexture02 = load_rendered_text(text02, textColor);
    if(fontTexture02 == NULL){
        printf("Failed to load rendered text for fontTexture02...");
        return false;
    }

    return true;
}

void move_bullet()
{
    //Move our bullets if they are not dead.
    //Set the point of origin for spawning bullets
    //to the player.

    for(int i = MAX_BUTTONS; i < MAX_BULLETS; i++){
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

void init_button()
{
    objectStorage[0].xPosition = SCREEN_WIDTH / 2 - objectStorage[0].width / 2;
    objectStorage[0].yPosition = 100;
    objectStorage[0].fontTexture = fontTexture01;

    objectStorage[1].xPosition = SCREEN_WIDTH / 2 - objectStorage[0].width / 2;
    objectStorage[1].yPosition = 250;
    objectStorage[1].fontTexture = fontTexture02;
}

bool check_collision(int xA, int yA, int wA, int hA, int xB, int yB, int wB, int hB)
{
    //Axis alligned bounding box collision detection stuff. Takes 8 paramaters,
    //As oposed to 2 SDL_Rect's which has sometimes been buggy.
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
    //Render buttons
    for(int i = 0; i < MAX_BUTTONS; i++){
        if(!objectStorage[i].isDead){
            render_image(objectStorage[i].xPosition, objectStorage[i].yPosition, objectStorage[i].width,
                        objectStorage[i].height, 0, objectStorage[i].texture, NULL, NULL, SDL_FLIP_NONE);

            render_image(objectStorage[i].xPosition + 25, objectStorage[i].yPosition + 25, objectStorage[i].width - 50,
                        objectStorage[i].height - 50, 0, objectStorage[i].fontTexture, NULL, NULL, SDL_FLIP_NONE);
        }
   }

    //Render bullets
    for(int i = MAX_BUTTONS; i < MAX_BULLETS; i++){
        if(!objectStorage[i].isDead){
            render_image(objectStorage[i].xPosition, objectStorage[i].yPosition, objectStorage[i].width,
                        objectStorage[i].height, objectStorage[i].angle, objectStorage[i].texture, NULL, NULL, SDL_FLIP_NONE);
        }
    }

    //Render Asteroids
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
