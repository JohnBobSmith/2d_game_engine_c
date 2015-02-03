#include "Player.h"
#include "Game.h"
#include "GameObject.h"
#include "GameAudio.h"
#include <math.h>
#include <stdio.h>

//Some global player variables
SDL_Texture *playerTexture = NULL;
const int PLAYER_VELOCITY = 2;
int currentBullet = 2;
int mouseAngle;
bool isMousePressed = false;

bool init_player()
{
    //initialize all player variables
    playerPositionX = 50;
    playerPositionY = 50;

    playerVelocityX = 0;
    playerVelocityY = 0;

    playerWidth = 50;
    playerHeight = 50;

    playerAngle = 0;

    return true;
}

bool load_player()
{
    //load our player image to the SDL_Texture datatype.
    char pathToPlayerImage[] = "images/player.png";

    playerTexture = load_image_from_file(pathToPlayerImage);
    if(playerTexture == NULL){
        printf("Failed to load %s. Image not found!", pathToPlayerImage);
        return false;
    }
    return true;
}

void handle_player_events(SDL_Event *event)
{
    //Handle all player events. Mouse, keybaord, etc.
    int xCenter, yCenter;
    int mouseX, mouseY;
    int result; //Store the result of some complex math regarding mouse position.

    if(event->type == SDL_KEYDOWN && event->key.repeat == 0){ //if we press a key...
        switch(event->key.keysym.sym){ //Look for each key...
            case SDLK_w: //If we find a key (or two, in this case)...
            case SDLK_UP:
                playerVelocityY -= PLAYER_VELOCITY; //add or subtract player velocities.
                break;

            case SDLK_s:
            case SDLK_DOWN:
                playerVelocityY += PLAYER_VELOCITY;
                break;

            case SDLK_a:
            case SDLK_LEFT:
                playerVelocityX -= PLAYER_VELOCITY;
                break;

            case SDLK_d:
            case SDLK_RIGHT:
                playerVelocityX += PLAYER_VELOCITY;
                break;

            case SDLK_ESCAPE: //If we press escape, open the menu.
                GAME_STATE_CURRENT = 2;
                break;
        }
    }

    if(event->type == SDL_KEYUP && event->key.repeat == 0){ //Likewise for key release
        switch(event->key.keysym.sym){

            case SDLK_w:
            case SDLK_UP:
                playerVelocityY += PLAYER_VELOCITY;
                break;

            case SDLK_s:
            case SDLK_DOWN:
                playerVelocityY -= PLAYER_VELOCITY;
                break;

            case SDLK_a:
            case SDLK_LEFT:
                playerVelocityX += PLAYER_VELOCITY;
                break;

            case SDLK_d:
            case SDLK_RIGHT:
                playerVelocityX -= PLAYER_VELOCITY;
                break;
        }
    }

    if(event->type == SDL_MOUSEMOTION){ // If we move the mouse..
        SDL_GetMouseState(&mouseX, &mouseY); //Get the mouse position...

        xCenter = playerPositionX - camera.x + playerWidth / 2;
        yCenter = playerPositionY - camera.y + playerHeight / 2;
        result = atan2(mouseY - yCenter, mouseX - xCenter) * 180 / 3.14; //Convert co-ordinates into an angle.

        playerAngle = result;
        mouseAngle = result;
    }

    if(event->type == SDL_MOUSEBUTTONDOWN && event->button.button == SDL_BUTTON_LEFT && GAME_STATE_CURRENT == 1){
        //If we press the left mouse button and we are playing the game...
        currentBullet += 1; //Update the bullet that is currently being fired...

        Bullet[currentBullet].isDead = false; //And set that bullets properties acordingly.
        Bullet[currentBullet].angle = mouseAngle - 90;
        //These next two lines make the bullet follow a straight line.
        Bullet[currentBullet].xVelocity = BULLET_VELOCITY * (cos(mouseAngle * 3.14 / 180));
        Bullet[currentBullet].yVelocity = BULLET_VELOCITY * (sin(mouseAngle * 3.14 / 180));

        play_sfx(laserShoot); //Play the laser sound effect.
    }

    if(event->type == SDL_MOUSEBUTTONUP && GAME_STATE_CURRENT == 1){ //If we release the left mouse button...
        if(currentBullet >= MAX_BULLETS - 1){ //If We've exceeded out bullet count...
            currentBullet = 2; //reset the bullet count
        }
    }

    if(event->type == SDL_MOUSEBUTTONDOWN && event->button.button == SDL_BUTTON_LEFT && GAME_STATE_CURRENT == 2){
        //if we press the left mouse button and we are in the main menu...
        if(check_collision(event->button.x, event->button.y, 4, 4, Button[0].xPosition, Button[0].yPosition,
                                    Button[0].width, Button[0].height)){

            GAME_STATE_CURRENT = 1; //Start playing if we press play.
        }

        if(check_collision(event->button.x, event->button.y, 4, 4, Button[1].xPosition, Button[1].yPosition,
                                    Button[1].width, Button[1].height)){

            GAME_STATE_CURRENT = 3; //Exit if we press exit.
        }
    }
}

void move_player()
{
    //Move our player by adding the velocities to the positions.
    playerPositionX += playerVelocityX;
    playerPositionY += playerVelocityY;

    //If the player moves off screen on the X axis...
    if(playerPositionX < 0 || (playerPositionX + playerWidth) > LEVEL_WIDTH){
        playerPositionX -= playerVelocityX; //Stop movement.
    }

    //If the player moves off screen on the Y axis...
    if(playerPositionY < 0 || (playerPositionY + playerHeight) > LEVEL_HEIGHT){
        playerPositionY -= playerVelocityY; //Stop movement.
    }

    for(int i = 0; i < MAX_ASTEROIDS; i++){ //If we run into the asteroids...
        if(check_collision(playerPositionX, playerPositionY, playerWidth, playerHeight, Asteroid[i].xPosition,
                            Asteroid[i].yPosition, Asteroid[i].width, Asteroid[i].height)){

            //printf("Collision between player and asteroid detected!\n");
        }
    }
}


void render_player(int camX, int camY)
{
    //Render our player relative to the camera.
    //Note that we have to subtract the players postion from the camera's position.
    render_image(playerPositionX - camX, playerPositionY - camY, playerWidth, playerHeight,
                                    playerAngle, playerTexture, NULL, NULL, SDL_FLIP_NONE);
}

void free_player_resources()
{
    //Cleanup our player.
    SDL_DestroyTexture(playerTexture);
    playerTexture = NULL;
}
