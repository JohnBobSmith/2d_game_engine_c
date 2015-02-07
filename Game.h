#ifndef GAME_H
#define GAME_H

#include "GameEngine.h"

//Not much in here. Just our game function prototypes and the camera.
//We also have one int checking the game's current state.

int GAME_STATE_CURRENT;

SDL_Rect camera;

const int LEVEL_WIDTH;
const int LEVEL_HEIGHT;

bool init_game();
bool load_game();
void move_camera();
void render_game();
void render_menu();
void close_game();

#endif // GAME_H
