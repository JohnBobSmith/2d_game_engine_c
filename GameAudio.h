#ifndef GAMEAUDIO_H
#define GAMEAUDIO_H

#include "GameEngine.h"

Mix_Chunk *laserShoot;
Mix_Chunk *asteroidExplode;

bool load_audio_subsystem();
void play_sfx(Mix_Chunk *nameOfChunk);
void close_audio();

#endif // GAMEAUDIO_H
