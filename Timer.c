#include "Timer.h"
/*
int mStartTicks = 0;
int mPausedTicks = 0;
bool mPaused = false;
bool mStarted = false;
*/

void start()
{
    //Start and un-pause timer.
    mStarted = true;
    mPaused = false;

    //Get the current time.
    mStartTicks = SDL_GetTicks();
    mPausedTicks = 0;
}

void stop()
{
    mPaused = false;
    mStarted = false;

    mStartTicks = 0;
    mPausedTicks = 0;
}

void pause()
{
    if (mStarted && !mPaused) {
        mPaused = true;
        mPausedTicks = SDL_GetTicks() - mStartTicks;
        mStartTicks = 0;
    }

}

void unpause()
{
    if (mStarted && mPaused) {
        mPaused = false;
        mStartTicks = SDL_GetTicks() - mPausedTicks;
        mPausedTicks = 0;
    }
}

int getTicks()
{
    //The actual timer time
    int time = 0;

    //If the timer is running
    if( mStarted ) {
        //If the timer is paused
        if( mPaused ) {
            //Return the number of ticks when the timer was paused
            time = mPausedTicks;
        } else {
            //Return the current time minus the start time
            time = SDL_GetTicks() - mStartTicks;
        }
    }
    return time;
}

bool isStarted()
{
    return mStarted;
}

bool isPaused()
{
    return mStarted && mPaused;
}



