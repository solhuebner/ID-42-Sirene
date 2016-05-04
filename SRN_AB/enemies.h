#ifndef ENEMIES_H
#define ENEMIES_H

#include <Arduino.h>
#include "globals.h"

#define MAX_ONSCREEN_FISHY           3
#define MAX_ONSCREEN_FISH            3
#define MAX_ONSCREEN_EEL             2
#define MAX_ONSCREEN_JELLYFISH       3
#define MAX_ONSCREEN_OCTOPUS         2


#define ENEMIE_TYPE_FISHY            0
#define ENEMIE_TYPE_FISH             1
#define ENEMIE_TYPE_EEL              2
#define ENEMIE_TYPE_JELLYFISH        3
#define ENEMIE_TYPE_OCTOPUS          4

#define MAX_FRAME_FISHY              3
#define MAX_FRAME_FISH               3
#define MAX_FRAME_EEL                3
#define MAX_FRAME_JELLYFISH          10
#define MAX_FRAME_OCTOPUS            3

#define ARRAY_START_FISHY            0
#define ARRAY_START_FISH             MAX_ONSCREEN_FISHY
#define ARRAY_START_EEL              MAX_ONSCREEN_FISHY + MAX_ONSCREEN_FISH
#define ARRAY_START_JELLYFISH        MAX_ONSCREEN_FISHY + MAX_ONSCREEN_FISH + MAX_ONSCREEN_EEL
#define ARRAY_START_OCTOPUS          MAX_ONSCREEN_FISHY + MAX_ONSCREEN_FISH + MAX_ONSCREEN_EEL + MAX_ONSCREEN_JELLYFISH

#define ARRAY_MAX_AMOUNT             MAX_ONSCREEN_FISHY + MAX_ONSCREEN_FISH + MAX_ONSCREEN_EEL + MAX_ONSCREEN_JELLYFISH +  MAX_ONSCREEN_OCTOPUS



byte enemiesMaxFrames[] = {MAX_FRAME_FISHY, MAX_FRAME_FISH, MAX_FRAME_EEL, MAX_FRAME_JELLYFISH, MAX_FRAME_OCTOPUS};
byte enemiesArrayLocation[] = {ARRAY_START_FISHY, ARRAY_START_FISH, ARRAY_START_EEL, ARRAY_START_JELLYFISH, ARRAY_START_OCTOPUS, ARRAY_MAX_AMOUNT};
byte jellyFrame = 0;


struct Enemies
{
  public:
    int x;
    int y;
    int HP;
    boolean isActive = false;
    byte frame;
};

struct EndBoss
{
  public:
    int x = 64;
    byte y = 12;
    int HP;
    boolean isActive = false;

};

Enemies enemy[ARRAY_MAX_AMOUNT];
EndBoss pirateShip;

void setEnemies()
{
  for (byte g = 0; g < sizeof(enemiesMaxFrames); g++)
  {
    for (byte i = enemiesArrayLocation[g]; i < enemiesArrayLocation[g + 1]; i++)
    {
      enemy[i].frame += i;
    }
  }
}


void checkEnemies()
{
  if (arduboy.everyXFrames(6))
  {
    for (byte g = 0; g < sizeof(enemiesMaxFrames); g++)
    {
      for (byte i = enemiesArrayLocation[g]; i < enemiesArrayLocation[g + 1]; i++)
      {
        enemy[i].frame++;
        if (enemy[i].frame > enemiesMaxFrames[g]) enemy[i].frame = 0;
        if (enemy[i].x < -32) enemy[i].isActive = false;
        if (enemy[i].y < -32) enemy[i].isActive = false;
      }
    }
  }
}


void checkBosses()
{

}

void drawEnemies()
{
  for (byte i = ARRAY_START_FISHY; i < ARRAY_START_FISH; i++)
  {
    if (enemy[i].isActive) sprites.drawPlusMask(enemy[i].x, enemy[i].y, enemyFishy_plus_mask, enemy[i].frame);
  }
  for (byte i = ARRAY_START_FISH; i < ARRAY_START_EEL; i++)
  {
    if (enemy[i].isActive) sprites.drawPlusMask(enemy[i].x, enemy[i].y, enemyFish_plus_mask, enemy[i].frame);
  }
  for (byte i = ARRAY_START_EEL; i < ARRAY_START_JELLYFISH; i++)
  {
    if (enemy[i].isActive) sprites.drawPlusMask(enemy[i].x, enemy[i].y, enemyEel_plus_mask, enemy[i].frame);
  }
  for (byte i = ARRAY_START_JELLYFISH; i < ARRAY_START_OCTOPUS; i++)
  {
    jellyFrame = enemy[i].frame;
    if (jellyFrame > 4) jellyFrame = 0;
    if (enemy[i].isActive) sprites.drawPlusMask(enemy[i].x, enemy[i].y, enemyJellyfish_plus_mask, jellyFrame);
  }
  for (byte i = ARRAY_START_OCTOPUS; i < ARRAY_MAX_AMOUNT; i++)
  {
    if (enemy[i].isActive) sprites.drawPlusMask(enemy[i].x, enemy[i].y, enemyOctopus_plus_mask, enemy[i].frame);
  }
}


void drawPirateShip()
{
  sprites.drawSelfMasked(pirateShip.x + 16, pirateShip.y + 20, pirateshipShip, 0);
  sprites.drawSelfMasked(pirateShip.x + 24, pirateShip.y + 5, pirateshipSail, 0);
  sprites.drawSelfMasked(pirateShip.x, pirateShip.y + 19, pirateshipBowsprit, 0);
  sprites.drawSelfMasked(pirateShip.x + 36, pirateShip.y + 0, pirateshipCrowsnest, 0);
}

void drawBosses()
{
  if (pirateShip.isActive) drawPirateShip();
}



#endif
