#ifndef LEVELS_H
#define LEVELS_H

#include <Arduino.h>
#include "globals.h"
#include "enemies.h"

#define WAVE_SPEED             3
#define WAVE_DURATION          63
#define WAVE_TOTAL_AMOUNT      12


void updateLevel()
{
  if (arduboy.everyXFrames(WAVE_SPEED ))waveDuration++;
  if (waveDuration > WAVE_DURATION)
  {
    waveDuration = 0;
    currentWave++;
  }
  if (currentWave > WAVE_TOTAL_AMOUNT - 1) currentWave = WAVE_TOTAL_AMOUNT - 1;
}




void wave000()
{
}

void enemySetInLine(byte firstEnemy, byte lastEnemy, byte x, byte y, byte spacing)
{
  if (currentWave != previousWave)
  {
    for (byte i = firstEnemy; i < lastEnemy; i++)
    {
      enemy[i].isActive = true;
      enemy[i].x = x + (20 * i);
      enemy[i].y = y;
      enemy[i].HP = 2;
    }
    previousWave = currentWave;
  }
}

void enemySwimLeftRight(byte firstEnemy, byte lastEnemy, byte speedEnemy)
{
  for (byte i = firstEnemy; i < lastEnemy; i++)
  {
    enemy[i].x = enemy[i].x - speedEnemy;
  }
}

void enemySwimToMiddle(byte firstEnemy, byte lastEnemy, byte speedEnemy)
{
  for (byte i = firstEnemy; i < lastEnemy; i++)
  {
    enemy[i].x = enemy[i].x - speedEnemy;
    if (enemy[i].x < 64)
    {
      if (enemy[i].y < 31) enemy[i].y++;
      if (enemy[i].y > 32) enemy[i].y--;
      }
  }
}

void wave001()
{
  enemySetInLine(0, MAX_ONSCREEN_FISHY, 128, 12, 20);
  enemySwimLeftRight(0, MAX_ONSCREEN_FISHY, 1);
}

void wave002()
{
  enemySetInLine(0, MAX_ONSCREEN_FISHY, 128, 28, 32);
  enemySwimLeftRight(0, MAX_ONSCREEN_FISHY, 1);
}

void wave003()
{
  enemySetInLine(0, MAX_ONSCREEN_FISHY, 128, 56, 48);
  enemySwimLeftRight(0, MAX_ONSCREEN_FISHY, 1);
}

void wave004()
{
  enemySetInLine(0, MAX_ONSCREEN_FISHY, 128, 12, 20);
  enemySwimToMiddle(0, MAX_ONSCREEN_FISHY, 1);
}

void wave005()
{
  enemySetInLine(0, MAX_ONSCREEN_FISHY, 128, 56, 20);
  enemySwimToMiddle(0, MAX_ONSCREEN_FISHY, 1);
}


typedef void (*FunctionPointer) ();

FunctionPointer Level01[] = {
  wave000,
  wave001,
  wave002,
  wave003,
  wave004,
  wave005,
  wave001,
  wave002,
  wave003,
  wave004,
  wave005,
  wave000,
};


#endif
