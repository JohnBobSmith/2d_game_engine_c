#include "GameObject.h"
#include "Game.h"
#include "GameAudio.h"
#include "Player.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

SDL_Texture *bulletTexture = NULL;
SDL_Texture *asteroidTexture = NULL;
SDL_Texture *buttonTexture = NULL;
SDL_Texture *fontTexturePlay = NULL;
SDL_Texture *fontTextureExit = NULL;
SDL_Texture *explosionTexture = NULL;

const int BULLET_VELOCITY = 7;

const int MAX_BUTTONS = 2;
const int MAX_FONT_OBJECTS = 2;
const int MAX_BULLETS = 25;
const int MAX_ASTEROIDS = 15;
const int MAX_EFFECTS = 15;

int currentAsteroid = 0;
int currentEffect = 0;

bool load_asteroid()
{
    char pathToAsteroidImage[] = "images/asteroid.png";

    asteroidTexture = load_image_from_file(pathToAsteroidImage);
    if(asteroidTexture == NULL){
        printf("Failed to load %s ", pathToAsteroidImage);
        return false;
    }

    return true;
}

bool load_bullet()
{
    char pathToBulletImage[] = "images/bullet.png";

    bulletTexture = load_image_from_file(pathToBulletImage);
    if(bulletTexture == NULL){
        printf("Failed to load %s ", pathToBulletImage);
        return false;
    }

    return true;
}

bool load_button()
{
    char pathToButtonImage[] = "images/button.png";

    buttonTexture = load_image_from_file(pathToButtonImage);
    if(buttonTexture == NULL){
        printf("Failed to load %s. ", pathToButtonImage);
        return false;
    }

    return true;
}

bool load_effect()
{
    char pathToExplosionImage[] = "images/effects/explosion.png";

    explosionTexture = load_image_from_file(pathToExplosionImage);
    if(explosionTexture == NULL){
        printf("Failed to load %s. ", pathToExplosionImage);
        return false;
    }

    return true;
}


void create_asteroid()
{
    Asteroid = malloc(sizeof(gameObject) * MAX_ASTEROIDS);

    for(int i = 0; i < MAX_ASTEROIDS; i++){
        Asteroid[i].angle = 0;
        Asteroid[i].xPosition = 0;
        Asteroid[i].yPosition = 0;
        Asteroid[i].width = 70;
        Asteroid[i].height = 70;
        Asteroid[i].xVelocity = 0;
        Asteroid[i].yVelocity = 0;
        Asteroid[i].texture = asteroidTexture;
        Asteroid[i].isDead = true;
    }
}

void create_bullet()
{
    //Allocate memory to bullets
    Bullet = malloc(sizeof(gameObject) * MAX_BULLETS);

    for(int i = 0; i < MAX_BULLETS; i++){
        Bullet[i].angle = 0;
        Bullet[i].xPosition = 0;
        Bullet[i].yPosition = 0;
        Bullet[i].width = 25;
        Bullet[i].height = 50;
        Bullet[i].xVelocity = 0;
        Bullet[i].yVelocity = 0;
        Bullet[i].texture = bulletTexture;
        Bullet[i].isDead = true;
    }
}

void create_button()
{
    Button = malloc(sizeof(gameObject) * MAX_BUTTONS);

    for(int i = 0; i < MAX_BUTTONS; i++){
        Button[i].angle = 0;
        Button[i].xPosition = 0;
        Button[i].yPosition = 0;
        Button[i].width = 256;
        Button[i].height = 96;
        Button[i].xVelocity = 0;
        Button[i].yVelocity = 0;
        Button[i].texture = buttonTexture;
        Button[i].isDead = true;
    }
}

void create_effect()
{
    ExplosionFX = malloc(sizeof(gameObject) * MAX_EFFECTS);

    for(int i = 0; i < MAX_EFFECTS; i++){
        ExplosionFX[i].angle = 0;
        ExplosionFX[i].xPosition = 250;
        ExplosionFX[i].yPosition = 250;
        ExplosionFX[i].width = 70;
        ExplosionFX[i].height = 70;
        ExplosionFX[i].xVelocity = 0;
        ExplosionFX[i].yVelocity = 0;
        ExplosionFX[i].texture = explosionTexture;
        ExplosionFX[i].isDead = false;
    }
}

void create_font_object()
{
    FontObject = malloc(sizeof(gameObject) * MAX_FONT_OBJECTS);

    for(int i = 0; i < MAX_FONT_OBJECTS; i++){
        FontObject[i].angle = 0;
        FontObject[i].xPosition = 0;
        FontObject[i].yPosition = 0;
        FontObject[i].width = 200;
        FontObject[i].height = 70;
        FontObject[i].xVelocity = 0;
        FontObject[i].yVelocity = 0;
        FontObject[i].texture = NULL;
        FontObject[i].isDead = true;
    }
}

void init_button()
{
    Button[0].xPosition = SCREEN_WIDTH / 2 - Button[0].width / 2;
    Button[0].yPosition = 100;

    Button[1].xPosition = SCREEN_WIDTH / 2 - Button[1].width / 2;
    Button[1].yPosition = 250;
}

void init_font_object()
{
    char textExit[] = "EXIT";
    char textPlay[] = "PLAY";

    SDL_Color textColor = {255, 255, 255, 255};

    fontTextureExit = load_rendered_text(textExit, textColor);
    fontTexturePlay = load_rendered_text(textPlay, textColor);

    FontObject[0].xPosition = Button[0].xPosition + 25;
    FontObject[0].yPosition = Button[0].yPosition + 12;
    FontObject[0].texture = fontTexturePlay;

    FontObject[1].xPosition = Button[1].xPosition + 25;
    FontObject[1].yPosition = Button[1].yPosition + 12;
    FontObject[1].texture = fontTextureExit;
}

void init_asteroid_position()
{
    //Randomize the asteroid positions.
    int randomXPosition = rand() % (LEVEL_WIDTH - 100);
    int randomYPosition = rand() % (LEVEL_HEIGHT - 100);
    int randomAngle = rand() % 360;

    //start randomization where bullets left off.
    Asteroid[currentAsteroid].xPosition = randomXPosition;
    Asteroid[currentAsteroid].yPosition = randomYPosition;
    Asteroid[currentAsteroid].angle = randomAngle;
    Asteroid[currentAsteroid].isDead = false;

    currentAsteroid += 1;
}

void init_effect_position()
{
    ExplosionFX[currentEffect].xPosition = Asteroid[currentAsteroid].xPosition;
    ExplosionFX[currentEffect].yPosition = Asteroid[currentAsteroid].yPosition;

    currentEffect += 1;
    currentAsteroid += 1;
}

bool load_gameobject_subsystem()
{
    char textPlay[] = "Play";
    char textExit[] = "Exit";

    SDL_Color textColor = {255, 255, 255, 255};

    load_asteroid(); //Load all our files...
    load_bullet();
    load_button();
    load_effect();

    create_asteroid(); //And create the actual GameObject's associated with
    create_bullet(); //Those files.
    create_button();
    create_font_object();
    create_effect();

    init_button(); //Initialize our buttons.
    init_font_object(); //Initialize our font objects.

    for(int i = 0; i < MAX_ASTEROIDS; i++){
        init_asteroid_position(); //Randomly place asteroids.
    }

    currentAsteroid = 0;

    for(int i = 0; i < MAX_EFFECTS; i++){
        init_effect_position();
    }

    return true;
}

void move_bullet()
{
    //Move our bullets if they are not dead.
    //Set the point of origin for spawning bullets
    //to the player. Also check for collisions.

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

        //If the bullets collide with the asteroids...
        for(int j = 0; j < MAX_ASTEROIDS; j++){
            if(!Bullet[i].isDead && !Asteroid[j].isDead){
                if(check_collision(Bullet[i].xPosition, Bullet[i].yPosition, Bullet[i].width, Bullet[i].height,
                                    Asteroid[j].xPosition - camera.x - camera.x, Asteroid[j].yPosition - camera.y - camera.y,
                                    Asteroid[j].width, Asteroid[j].height)){

                    Bullet[i].isDead = true; //They both die.
                    Asteroid[j].isDead = true;
                }
            }
        }
    }
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

void render_buttons()
{
    //Render buttons
    for(int i = 0; i < MAX_BUTTONS; i++){
        if(!Button[i].isDead){
            render_image(Button[i].xPosition, Button[i].yPosition, Button[i].width,
                        Button[i].height, 0, Button[i].texture, NULL, NULL, SDL_FLIP_NONE);
        }
    }
}

void render_bullets()
{
    //Render bullets
    for(int i = 0; i < MAX_BULLETS; i++){
        if(!Bullet[i].isDead){
            render_image(Bullet[i].xPosition, Bullet[i].yPosition, Bullet[i].width,
                        Bullet[i].height, Bullet[i].angle, Bullet[i].texture, NULL, NULL, SDL_FLIP_NONE);
        }
    }
}

void render_asteroids()
{
    //Render Asteroids
    for(int i = 0; i < MAX_ASTEROIDS; i++){
        if(!Asteroid[i].isDead){
            render_image(Asteroid[i].xPosition - camera.x - camera.x, Asteroid[i].yPosition - camera.y - camera.y,
                        Asteroid[i].width, Asteroid[i].height, Asteroid[i].angle, Asteroid[i].texture, NULL, NULL, SDL_FLIP_NONE);
        }
    }
}

void render_effects()
{
    //Render effects for a short period of time.
    for(int i = 0; i < MAX_EFFECTS; i++){
        if(Asteroid[i].isDead){
            ExplosionFX[i].angle += 2;
            render_image(ExplosionFX[i].xPosition - camera.x - camera.x, ExplosionFX[i].yPosition - camera.y - camera.y,
                            ExplosionFX[i].width, ExplosionFX[i].height, ExplosionFX[i].angle, ExplosionFX[i].texture,
                            NULL, NULL, SDL_FLIP_NONE);
        }
    }
}

void render_font_objects()
{
    //Render font objects
    for(int i = 0; i < MAX_FONT_OBJECTS; i++){
        if(!FontObject[i].isDead){
            render_image(FontObject[i].xPosition, FontObject[i].yPosition, FontObject[i].width, FontObject[i].height, 0,
                                FontObject[i].texture, NULL, NULL, SDL_FLIP_NONE);
        }
    }
}

void free_gameobject_resources()
{
    //Cleanup resources
    free(Button);
    free(Bullet);
    free(Asteroid);
    free(FontObject);
    free(ExplosionFX);

    SDL_DestroyTexture(bulletTexture);
    SDL_DestroyTexture(asteroidTexture);
    SDL_DestroyTexture(buttonTexture);
    SDL_DestroyTexture(fontTexturePlay);
    SDL_DestroyTexture(fontTextureExit);
    SDL_DestroyTexture(explosionTexture);

    bulletTexture = NULL;
    asteroidTexture = NULL;
    buttonTexture = NULL;
    fontTexturePlay = NULL;
    fontTextureExit = NULL;
    explosionTexture = NULL;
}
