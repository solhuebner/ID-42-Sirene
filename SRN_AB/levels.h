#ifndef LEVELS_H
#define LEVELS_H

#include <Arduino.h>
#include "globals.h"
#include "enemies.h"

#define WAVE_SPEED             3
#define WAVE_DURATION          63
#define WAVE_TOTAL_AMOUNT      5


void updateLevel()
{
  if (arduboy.everyXFrames(WAVE_SPEED ))waveDuration++;
  if (waveDuration > WAVE_DURATION)
  {
    waveDuration = 0;
    currentWave++;
  }
  if (currentWave > WAVE_TOTAL_AMOUNT - 1) currentWave = WAVE_TOTAL_AMOUNT-1;
}

void wave000()
{
}

void wave001()
{
  if (currentWave != previousWave)
  {
    for (byte i = 0; i < MAX_ONSCREEN_FISHY; i++)
    {
      enemy[i].isActive = true;
      enemy[i].y = 12;
      enemy[i].x = 128 + (20 * i);
      enemy[i].HP = 2;
    }
    previousWave = currentWave;
  }
  for (byte i = 0; i < MAX_ONSCREEN_FISHY; i++)
  {
    enemy[i].x = enemy[i].x - 1;
    if (enemy[i].x < -32) enemy[i].isActive = false;
  }
}

void wave002()
{
  if (currentWave != previousWave)
  {
    for (byte i = 0; i < MAX_ONSCREEN_FISHY; i++)
    {
      enemy[i].isActive = true;
      enemy[i].y = 28;
      enemy[i].x = 128 + (20 * i);
      enemy[i].HP = 2;
    }
    previousWave = currentWave;
  }
  for (byte i = 0; i < MAX_ONSCREEN_FISHY; i++)
  {
    enemy[i].x = enemy[i].x - 1;
    if (enemy[i].x < -32) enemy[i].isActive = false;
  }
}

void wave003()
{
  if (currentWave != previousWave)
  {
    for (byte i = 0; i < MAX_ONSCREEN_FISHY; i++)
    {
      enemy[i].isActive = true;
      enemy[i].y = 44;
      enemy[i].x = 128 + (20 * i);
      enemy[i].HP = 2;
    }
    previousWave = currentWave;
  }
  for (byte i = 0; i < MAX_ONSCREEN_FISHY; i++)
  {
    enemy[i].x = enemy[i].x - 1;
    if (enemy[i].x < -32) enemy[i].isActive = false;
  }
}


typedef void (*FunctionPointer) ();

FunctionPointer Level01[] = {
  wave000,
  wave001,
  wave002,
  wave003,
  wave000,
};


#endif
