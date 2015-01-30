#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "GameEngine.h"
#include <stdbool.h>

typedef struct Object
{
    SDL_Texture *texture;

    int xPosition, yPosition;
    int xVelocity, yVelocity;
    int width, height;
    int angle;

    bool isDead;

} object;

object *objectStorage;

const int MAX_BULLETS;
const int BULLET_VELOCITY;

void create_object();
bool load_object();
void move_bullet();
void render_object();
void free_object_resources();

#endif // GAMEOBJECT_H
