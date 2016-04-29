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

byte enemyFrame[] = {0, 0, 0, 0, 0};
byte enemyMaxFrame[] = {3, 3, 3, 4, 3};
const byte maxAmountEnemies =  MAX_ONSCREEN_FISHY + MAX_ONSCREEN_FISH + MAX_ONSCREEN_EEL + MAX_ONSCREEN_JELLYFISH +  MAX_ONSCREEN_OCTOPUS;

struct Enemies
{
  public:
    int x;
    byte y;
    int HP;
    boolean isActive = false;
};

struct EndBoss
{
  public:
    int x = 64;
    byte y = 12;
    int HP;
    boolean isActive = false;

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
      if (enemy[i].x < -32) enemy[i].isActive = false;
    }
  }
}


void checkBosses()
{

}

void drawEnemies()
{
  for (byte i = 0; i < MAX_ONSCREEN_FISHY; i++)
  {
    if (enemy[i].isActive) sprites.drawPlusMask(enemy[i].x, enemy[i].y, enemyFishy_plus_mask, enemyFrame[ENEMIE_TYPE_FISHY]);
  }
  for (byte i = MAX_ONSCREEN_FISHY; i < MAX_ONSCREEN_FISHY + MAX_ONSCREEN_FISH; i++)
  {
    if (enemy[i].isActive) sprites.drawPlusMask(enemy[i].x, enemy[i].y, enemyFish_plus_mask, enemyFrame[ENEMIE_TYPE_FISH]);
  }
  for (byte i = MAX_ONSCREEN_FISHY + MAX_ONSCREEN_FISH; i < MAX_ONSCREEN_FISHY + MAX_ONSCREEN_FISH + MAX_ONSCREEN_EEL; i++)
  {
    if (enemy[i].isActive) sprites.drawPlusMask(enemy[i].x, enemy[i].y, enemyEel_plus_mask, enemyFrame[ENEMIE_TYPE_EEL]);
  }
  for (byte i = MAX_ONSCREEN_FISHY + MAX_ONSCREEN_FISH + MAX_ONSCREEN_EEL; i < MAX_ONSCREEN_FISHY + MAX_ONSCREEN_FISH + MAX_ONSCREEN_EEL + MAX_ONSCREEN_JELLYFISH; i++)
  {
    if (enemy[i].isActive) sprites.drawPlusMask(enemy[i].x, enemy[i].y, enemyJellyfish_plus_mask, enemyFrame[ENEMIE_TYPE_JELLYFISH]);
  }
  for (byte i = MAX_ONSCREEN_FISHY + MAX_ONSCREEN_FISH + MAX_ONSCREEN_EEL + MAX_ONSCREEN_JELLYFISH; i < MAX_ONSCREEN_FISHY + MAX_ONSCREEN_FISH + MAX_ONSCREEN_EEL + MAX_ONSCREEN_JELLYFISH +  MAX_ONSCREEN_OCTOPUS; i++)
  {
    if (enemy[i].isActive) sprites.drawPlusMask(enemy[i].x, enemy[i].y, enemyOctopus_plus_mask, enemyFrame[ENEMIE_TYPE_OCTOPUS]);
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
