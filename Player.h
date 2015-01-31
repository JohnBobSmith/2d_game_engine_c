#ifndef PLAYER_H
#define PLAYER_H

#include "GameEngine.h"

//Not much inside this header. Just some prototypes,
//and our constant PLAYER_VELOCITY variable.

const int PLAYER_VELOCITY;

int playerPositionX, playerPositionY;
int playerVelocityX, playerVelocityY;
int playerWidth, playerHeight;
int playerAngle;

bool init_player();
bool load_player();
void handle_player_events(SDL_Event *event);
void move_player();
void render_player(int camX, int camY);
void free_player_resources();

#endif // PLAYER_H
