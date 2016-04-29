#ifndef ENEMIES_H
#define ENEMIES_H

#include <Arduino.h>
#include "globals.h"

#define MAX_ONSCREEN_EEL             1
#define MAX_ONSCREEN_FISHY           1
#define MAX_ONSCREEN_FISH            1
#define MAX_ONSCREEN_JELLYFISH       1
#define MAX_ONSCREEN_SHARK           1
#define MAX_ONSCREEN_OCTOPUS         1

#define ENEMIE_TYPE_EEL              0
#define ENEMIE_TYPE_FISHY            1
#define ENEMIE_TYPE_FISH             2
#define ENEMIE_TYPE_JELLYFISH        3
#define ENEMIE_TYPE_SHARK            4
#define ENEMIE_TYPE_OCTOPUS          5

byte enemyFrame[] = {0, 0, 0, 0, 0, 0};
byte enemyMaxFrame[] = {3, 3, 3, 4, 3, 3};
const byte maxAmountEnemies = MAX_ONSCREEN_EEL + MAX_ONSCREEN_FISHY + MAX_ONSCREEN_FISH + MAX_ONSCREEN_JELLYFISH + MAX_ONSCREEN_SHARK + MAX_ONSCREEN_OCTOPUS;
const byte enemyType[] =
{
  ENEMIE_TYPE_EEL,
  ENEMIE_TYPE_FISHY,
  ENEMIE_TYPE_FISH,
  ENEMIE_TYPE_JELLYFISH,
  ENEMIE_TYPE_SHARK,
  ENEMIE_TYPE_OCTOPUS,
};

struct Enemies
{
  public:
    byte x = 32;
    int y = 12;
    byte HP;
    byte isActive = true;
    byte type = 0;
};

struct EndBoss
{
  public:
    byte x = 64;
    byte y = 12;
    byte HP;
    byte isActive = false;

};

Enemies enemy[maxAmountEnemies];

EndBoss pirateShip;

void checkEnemies()
{
  if (arduboy.everyXFrames(10))
  {
    for (byte i = 0; i < maxAmountEnemies; i++)
    {
      enemyFrame[i]++;
      if (enemyFrame[i] > enemyMaxFrame[i]) enemyFrame[i] = 0;
    }
  }
}

void checkBosses()
{

}

void drawEnemies()
{
  for (byte i = 0; i < MAX_ONSCREEN_EEL; i++)
  {
    if (enemy[i].isActive) sprites.drawPlusMask(enemy[i].x, enemy[i].y, enemyEel_plus_mask, enemyFrame[ENEMIE_TYPE_EEL]);
  }
  for (byte i = 0; i < ENEMIE_TYPE_FISHY; i++)
  {
    if (enemy[i].isActive) sprites.drawPlusMask(enemy[i].x, enemy[i].y+16, enemyFishy_plus_mask, enemyFrame[ENEMIE_TYPE_FISHY]);
  }
  for (byte i = 0; i < MAX_ONSCREEN_FISH; i++)
  {
    if (enemy[i].isActive) sprites.drawPlusMask(enemy[i].x, enemy[i].y+32, enemyFish_plus_mask, enemyFrame[ENEMIE_TYPE_FISH]);
  }
  for (byte i = 0; i < MAX_ONSCREEN_JELLYFISH; i++)
  {
    if (enemy[i].isActive) sprites.drawPlusMask(enemy[i].x+64, enemy[i].y+8, enemyJellyfish_plus_mask, enemyFrame[ENEMIE_TYPE_JELLYFISH]);
  }
  for (byte i = 0; i < MAX_ONSCREEN_SHARK; i++)
  {
    if (enemy[i].isActive) sprites.drawPlusMask(enemy[i].x+24, enemy[i].y+24, enemyShark_plus_mask, enemyFrame[ENEMIE_TYPE_SHARK]);
  }
  for (byte i = 0; i < MAX_ONSCREEN_OCTOPUS; i++)
  {
    if (enemy[i].isActive) sprites.drawPlusMask(enemy[i].x+64, enemy[i].y+32, enemyOctopus_plus_mask, enemyFrame[ENEMIE_TYPE_OCTOPUS]);
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
