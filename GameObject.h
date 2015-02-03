#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "GameEngine.h"
#include <stdbool.h>

//Contains our Object struct. All game objects (bullets, asteroids, etc.)
//should make use of this struct.

typedef struct GameObject
{
    SDL_Texture *texture;
    SDL_Texture *fontTexture;

    int xPosition, yPosition;
    int xVelocity, yVelocity;
    int width, height;
    int angle;

    bool isDead;

} gameObject;

gameObject *Button;
gameObject *Bullet;
gameObject *Asteroid;

const int BULLET_VELOCITY;
const int MAX_BUTTONS;
const int MAX_BULLETS;
const int MAX_ASTEROIDS;

void create_object();
bool load_object();
void move_bullet();
void randomize_asteroid_position();
void init_button();
bool check_collision(int xA, int yA, int wA, int hA, int xB, int yB, int wB, int hB);
void render_object();
void free_object_resources();

#endif // GAMEOBJECT_H
