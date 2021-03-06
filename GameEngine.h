#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <stdbool.h>

//All game engine functions can be found here.
//Note the render_image() function and the
//load_image_from_file() function.

const int SCREEN_WIDTH;
const int SCREEN_HEIGHT;

SDL_Texture *load_rendered_text(char text[], SDL_Color textColor);
SDL_Texture *load_image_from_file(char path[]);
void render_image(int xPosition, int yPosition, int width, int height, float angle, SDL_Texture *texture,
                                SDL_Rect *sRect, SDL_Point *center, SDL_RendererFlip flip);

void run_engine();
bool init_engine();
bool load_engine();
void close_engine();

#endif // GAMEENGINE_H
