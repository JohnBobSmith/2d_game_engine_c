#include "GameAudio.h"

Mix_Chunk *laserShoot = NULL;
Mix_Chunk *asteroidExplode = NULL;

bool load_audio_subsystem()
{
    char pathToLaserShootSound[] = "sounds/effects/laser_shoot.wav";
    char pathToAsteroidExplodeSound[] = "sounds/effects/asteroid_explode.wav";

    laserShoot = Mix_LoadWAV(pathToLaserShootSound);
    if(laserShoot == NULL){
        printf("Failed to load %s", pathToLaserShootSound);
        return false;
    }

    asteroidExplode = Mix_LoadWAV(pathToAsteroidExplodeSound);
    if(asteroidExplode == NULL){
        printf("Failed to load %s", pathToAsteroidExplodeSound);
        return false;
    }

    return true;
}

void play_sfx(Mix_Chunk *nameOfChunk)
{
    Mix_PlayChannel(-1, nameOfChunk, 0);
}

void close_audio()
{
    Mix_FreeChunk(laserShoot);
    Mix_FreeChunk(asteroidExplode);
}
