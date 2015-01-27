#ifndef PLAYER_H
#define PLAYER_H

#include "GameEngine.h"

SDL_Texture *playerTexture;

const int PLAYER_VELOCITY;

int playerPositionX, playerPositionY;
int playerVelocityX, playerVelocityY;
int playerWidth, playerHeight;

bool init_player();
bool load_player();
void handle_player_events(SDL_Event event);
void move_player();
void render_player();
void free_player_resources();

#endif // PLAYER_H
