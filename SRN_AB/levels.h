#ifndef LEVELS_H
#define LEVELS_H

#include <Arduino.h>
#include "globals.h"
#include "enemies.h"

#define WAVE_SPEED             60
#define WAVE_DURATION          128


void updateLevel()
{
  if (arduboy.everyXFrames(WAVE_SPEED ))waveDuration++;
  if (waveDuration > WAVE_DURATION) waveDuration = 0;
}

void wave000()
{
}

void wave001()
{
}

void wave002()
{
}

void wave003()
{
}


typedef void (*FunctionPointer) ();

FunctionPointer Level01[] = {
  wave000,
  wave001,
  wave002,
  wave003,
};


#endif
