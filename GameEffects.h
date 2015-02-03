#ifndef GAMEEFFECTS_H
#define GAMEEFFECTS_H

#include "GameEngine.h"

const int MAX_EFFECTS;

typedef struct Effect
{
    SDL_Texture *texture;
    int xPosition, yPosition;
    int width, height;
    int angle;

    bool isDead;

} effect;

effect *Explosion;

bool init_effect();
bool load_effect();

#endif //GAMEEFFECTS_H
