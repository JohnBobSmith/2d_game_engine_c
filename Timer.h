#ifndef TIMER_H
#define TIMER_H

#include <SDL2/SDL.h>
#include <stdint.h>
#include <stdbool.h>

//The various clock actions
void start();
void stop();
void pause();
void unpause();

//Gets the timer's time
int getTicks();

//Checks the status of the timer
bool isStarted();
bool isPaused();

//The clock time when the timer started
int mStartTicks;

//The ticks stored when the timer was paused
int mPausedTicks;

//The timer status
bool mPaused;
bool mStarted;

#endif // TIMER_H
