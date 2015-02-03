#include "GameEffects.h"
#include "GameObject.h"
#include "GameAudio.h"

SDL_Texture *explosionTexture = NULL;

const int MAX_EFFECTS = 15;
int currentEffect = 0;

bool init_effect()
{
    Explosion = malloc(sizeof(effect) * 100);

    for(int i = 0; i < MAX_EFFECTS; i++){
        Explosion[i].texture = explosionTexture;
        Explosion[i].angle = 0;
        Explosion[i].height = 70;
        Explosion[i].width = 70;
        Explosion[i].xPosition = 0;
        Explosion[i].yPosition = 0;
        Explosion[i].isDead = true;
    }
    return true;
}

bool load_effect()
{
    char pathToExplosionImage[] = "images/effects/explosion.png";

    explosionTexture = load_image_from_file(pathToExplosionImage);
    if(explosionTexture == NULL){
        printf("Failed to load %s ", pathToExplosionImage);
        return false;
    }

    return true;
}
