#include "GameObject.h"
#include "Game.h"
#include "GameAudio.h"
#include "GameEffects.h"
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

int currentAsteroid = 0;

void create_object()
{
    //Allocate memory to all pointers of gameObject.
    Button = malloc(sizeof(gameObject) * MAX_BUTTONS);
    Bullet = malloc(sizeof(gameObject) * MAX_BULLETS);
    Asteroid = malloc(sizeof(gameObject) * MAX_ASTEROIDS);

    for(int i = 0; i < MAX_BUTTONS; i++){
        Button[i].angle = 0;
        Button[i].xPosition = 0;
        Button[i].yPosition = 0;
        Button[i].width = 256;
        Button[i].height = 96;
        Button[i].xVelocity = 0;
        Button[i].yVelocity = 0;
        Button[i].texture = buttonTexture;
        Button[i].fontTexture = NULL;
        Button[i].isDead = true;
    }

    for(int i = 0; i < MAX_BULLETS; i++){
        Bullet[i].angle = 0;
        Bullet[i].xPosition = 0;
        Bullet[i].yPosition = 0;
        Bullet[i].width = 25;
        Bullet[i].height = 50;
        Bullet[i].xVelocity = 0;
        Bullet[i].yVelocity = 0;
        Bullet[i].texture = bulletTexture;
        Bullet[i].fontTexture = NULL;
        Bullet[i].isDead = true;
    }

    for(int i = 0; i < MAX_ASTEROIDS; i++){
        Asteroid[i].angle = 0;
        Asteroid[i].xPosition = 0;
        Asteroid[i].yPosition = 0;
        Asteroid[i].width = 70;
        Asteroid[i].height = 70;
        Asteroid[i].xVelocity = 0;
        Asteroid[i].yVelocity = 0;
        Asteroid[i].texture = asteroidTexture;
        Asteroid[i].fontTexture = NULL;
        Asteroid[i].isDead = true;
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

    for(int i = 0; i < MAX_BULLETS; i++){
        if(!Bullet[i].isDead){
            Bullet[i].xPosition += Bullet[i].xVelocity;
            Bullet[i].yPosition += Bullet[i].yVelocity;
        }

        if(Bullet[i].xPosition < 0 || Bullet[i].xPosition > SCREEN_WIDTH ||
                    Bullet[i].yPosition < 0 || Bullet[i].yPosition > SCREEN_HEIGHT){

            Bullet[i].isDead = true;
        }

        if(Bullet[i].isDead){
            Bullet[i].xPosition = playerPositionX - camera.x;
            Bullet[i].yPosition = playerPositionY - camera.y;
        }

        for(int j = 0; j < MAX_ASTEROIDS; j++){
            if(!Bullet[i].isDead && !Asteroid[j].isDead){
                if(check_collision(Bullet[i].xPosition, Bullet[i].yPosition, Bullet[i].width, Bullet[i].height,
                                    Asteroid[j].xPosition - camera.x - camera.x, Asteroid[j].yPosition - camera.y - camera.y,
                                    Asteroid[j].width, Asteroid[j].height)){

                    Bullet[i].isDead = true;
                    Asteroid[j].isDead = true;
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
    Asteroid[currentAsteroid].xPosition = randomXPosition;
    Asteroid[currentAsteroid].yPosition = randomYPosition;
    Asteroid[currentAsteroid].angle = randomAngle;

    currentAsteroid += 1;
}

void init_button()
{
    Button[0].xPosition = SCREEN_WIDTH / 2 - Button[0].width / 2;
    Button[0].yPosition = 100;
    Button[0].fontTexture = fontTexture01;

    Button[1].xPosition = SCREEN_WIDTH / 2 - Button[1].width / 2;
    Button[1].yPosition = 250;
    Button[1].fontTexture = fontTexture02;
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
        if(!Button[i].isDead){
            render_image(Button[i].xPosition, Button[i].yPosition, Button[i].width,
                        Button[i].height, 0, Button[i].texture, NULL, NULL, SDL_FLIP_NONE);

            render_image(Button[i].xPosition + 25, Button[i].yPosition + 25, Button[i].width - 50,
                        Button[i].height - 50, 0, Button[i].fontTexture, NULL, NULL, SDL_FLIP_NONE);
        }
   }

    //Render bullets
    for(int i = 0; i < MAX_BULLETS; i++){
        if(!Bullet[i].isDead){
            render_image(Bullet[i].xPosition, Bullet[i].yPosition, Bullet[i].width,
                        Bullet[i].height, Bullet[i].angle, Bullet[i].texture, NULL, NULL, SDL_FLIP_NONE);
        }
    }

    //Render Asteroids
    for(int i = 0; i < MAX_ASTEROIDS; i++){
        if(!Asteroid[i].isDead){
            render_image(Asteroid[i].xPosition - camera.x - camera.x, Asteroid[i].yPosition - camera.y - camera.y,
                        Asteroid[i].width, Asteroid[i].height, Asteroid[i].angle, Asteroid[i].texture, NULL, NULL, SDL_FLIP_NONE);
        }
    }
}

void free_object_resources()
{
    //Cleanup resources
    free(Button);
    free(Bullet);
    free(Asteroid);

    SDL_DestroyTexture(bulletTexture);
    SDL_DestroyTexture(asteroidTexture);
    SDL_DestroyTexture(buttonTexture);
    SDL_DestroyTexture(fontTexture01);
    SDL_DestroyTexture(fontTexture02);

    bulletTexture = NULL;
    asteroidTexture = NULL;
    buttonTexture = NULL;
    fontTexture01 = NULL;
    fontTexture02 = NULL;
}
