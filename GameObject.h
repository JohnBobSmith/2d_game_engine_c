#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "GameEngine.h"
#include <stdbool.h>

//Contains our Object struct. All game objects (bullets, asteroids, etc.)
//should make use of this struct.

typedef struct GameObject
{
    SDL_Texture *texture;

    int xPosition, yPosition;
    int xVelocity, yVelocity;
    int width, height;
    int angle;

    bool isDead;

} gameObject;

gameObject *Button;
gameObject *Bullet;
gameObject *Asteroid;
gameObject *FontObject;
gameObject *ExplosionFX;

const int BULLET_VELOCITY;
const int MAX_BUTTONS;
const int MAX_BULLETS;
const int MAX_ASTEROIDS;
const int MAX_FONT_OBJECTS;
const int MAX_EFFECTS;

bool load_asteroid();
bool load_bullet();
bool load_button();
bool load_effect();
void create_asteroid();
void create_bullet();
void create_button();
void create_effect();
void create_font_object();
void init_button();
void init_font_object();
void init_asteroid_position();
void init_effect_position();
bool load_gameobject_subsystem();
void move_bullet();
bool check_collision(int xA, int yA, int wA, int hA, int xB, int yB, int wB, int hB);
void render_buttons();
void render_bullets();
void render_asteroids();
void render_effects();
void render_font_objects();
void free_gameobject_resources();

#endif // GAMEOBJECT_H
