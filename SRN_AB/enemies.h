#ifndef ENEMIES_H
#define ENEMIES_H

#include <Arduino.h>
#include "globals.h"

#define ENEMY_FISHY                  0
#define ENEMY_FISH                   1
#define ENEMY_EEL                    2
#define ENEMY_JELLYFISH              3
#define ENEMY_OCTOPUS                4

#define MAX_HP_FISHY                2
#define MAX_HP_FISH                 4
#define MAX_HP_EEL                  4
#define MAX_HP_JELLYFISH            2
#define MAX_HP_OCTOPUS              4

#define MAX_FRAME_FISHY              3
#define MAX_FRAME_FISH               3
#define MAX_FRAME_EEL                3
#define MAX_FRAME_JELLYFISH          10
#define MAX_FRAME_OCTOPUS            3

#define MAX_ONSCREEN_ENEMIES         8



byte enemiesMaxFrames[] = {MAX_FRAME_FISHY, MAX_FRAME_FISH, MAX_FRAME_EEL, MAX_FRAME_JELLYFISH, MAX_FRAME_OCTOPUS};
byte enemiesMaxHP[] = {MAX_HP_FISHY, MAX_HP_FISH, MAX_HP_EEL, MAX_HP_JELLYFISH, MAX_HP_OCTOPUS};
byte jellyFrame;
byte sharkFrame;
byte faseTimer;
byte mermaidsPosition;
boolean sharkSlow;
boolean sharkSwimsRight;


//////// Enemy functions ///////////////////
////////////////////////////////////////////

struct Enemies
{
  public:
    int x;
    int y;
    int HP;
    boolean isActive = false;
    boolean isDying = false;
    byte frame;
    byte type;
};


Enemies enemy[MAX_ONSCREEN_ENEMIES];


void setEnemies()
{
  jellyFrame = 0;
  for (byte i = 0; i < MAX_ONSCREEN_ENEMIES; i++)
  {
    enemy[i].frame = i;
    enemy[i].isActive = false;
    enemy[i].isDying = false;
    enemy[i].x = 128;
  }
}


void checkEnemies()
{
  for (byte i = 0; i < MAX_ONSCREEN_ENEMIES; i++)
  {
    if (!enemy[i].isDying && arduboy.everyXFrames(6)) enemy[i].frame++;
    if (enemy[i].isDying && arduboy.everyXFrames(3)) enemy[i].frame++;
    if ((enemy[i].frame > enemiesMaxFrames[enemy[i].type]) && !enemy[i].isDying) enemy[i].frame = 0;
    if ((enemy[i].frame > 5) && enemy[i].isDying)
    {
      enemy[i].isDying = false;
      enemy[i].isActive = false;
      enemy[i].frame = 0;
    }
    if ((enemy[i].x < -32) || (enemy[i].y < -32))
    {
      enemy[i].isActive = false;
      enemy[i].frame = 0;
    }
  }
}

void enemySetInLine(byte enemyType, byte firstEnemy, byte lastEnemy, byte x, byte y, int spacingX, int spacingY)
{
  for (byte i = firstEnemy; i < lastEnemy; i++)
  {
    enemy[i].frame = i;
    enemy[i].isActive = true;
    enemy[i].isDying = false;
    enemy[i].type = enemyType;
    enemy[i].x = x + (spacingX * (i - firstEnemy));
    enemy[i].y = y + (spacingY * (i - firstEnemy));
    enemy[i].HP = enemiesMaxHP[enemyType];
  }
}

void enemySwimRightLeft(byte firstEnemy, byte lastEnemy, byte speedEnemy)
{
  for (byte i = firstEnemy; i < lastEnemy; i++)
  {
    if (!enemy[i].isDying) enemy[i].x = enemy[i].x - speedEnemy;
  }
}

void enemySwimToMiddle(byte firstEnemy, byte lastEnemy, byte speedEnemy)
{
  for (byte i = firstEnemy; i < lastEnemy; i++)
  {
    if (!enemy[i].isDying)
    {
      enemy[i].x = enemy[i].x - speedEnemy;
      if (enemy[i].x < 64)
      {
        if (enemy[i].y < 31) enemy[i].y++;
        if (enemy[i].y > 32) enemy[i].y--;
      }
    }
  }
}

void enemySwimSine(byte firstEnemy, byte lastEnemy, byte speedEnemy)
{
  for (byte i = firstEnemy; i < lastEnemy; i++)
  {
    if (!enemy[i].isDying)
    {
      enemy[i].x = enemy[i].x - speedEnemy;
      if ((enemy[i].x < 120 ) && (enemy[i].x > 104) && (enemy[i].y > 16)) enemy[i].y--;
      if ((enemy[i].x < 105) && (enemy[i].x > 73) && (enemy[i].y < 48)) enemy[i].y++;
      if ((enemy[i].x < 74 ) && (enemy[i].x > 42) && (enemy[i].y > 16)) enemy[i].y--;
      if ((enemy[i].x < 43) && (enemy[i].x > 10) && (enemy[i].y < 48)) enemy[i].y++;
      if ((enemy[i].x < 11) && (enemy[i].y > 16)) enemy[i].y--;
    }
  }
}

void enemySwimDownUp(byte firstEnemy, byte lastEnemy, byte speedEnemy)
{
  for (byte i = firstEnemy; i < lastEnemy; i++)
  {
    if (!enemy[i].isDying)
    {
      if (enemy[i].frame > 4 && enemy[i].frame < 7 )enemy[i].y = enemy[i].y - speedEnemy - 1;
      if (enemy[i].frame > 6 )enemy[i].y = enemy[i].y - speedEnemy;
    }
  }
}



void drawEnemies()
{
  for (byte i = 0; i < MAX_ONSCREEN_ENEMIES; i++)
  {
    if (enemy[i].isActive)
    {
      if (enemy[i].isDying) sprites.drawSelfMasked(enemy[i].x, enemy[i].y, puff, enemy[i].frame);
      else
      {
        switch (enemy[i].type)
        {
          case ENEMY_FISHY:
            sprites.drawPlusMask(enemy[i].x, enemy[i].y, enemyFishy_plus_mask, enemy[i].frame);
            break;
          case ENEMY_FISH:
            sprites.drawPlusMask(enemy[i].x, enemy[i].y, enemyFish_plus_mask, enemy[i].frame);
            break;
          case ENEMY_EEL:
            sprites.drawPlusMask(enemy[i].x, enemy[i].y, enemyEel_plus_mask, enemy[i].frame);
            break;
          case ENEMY_JELLYFISH:
            jellyFrame = enemy[i].frame;
            if (jellyFrame > 4) jellyFrame = 0;
            sprites.drawPlusMask(enemy[i].x, enemy[i].y, enemyJellyfish_plus_mask, jellyFrame);
            break;
          case ENEMY_OCTOPUS:
            sprites.drawPlusMask(enemy[i].x, enemy[i].y, enemyOctopus_plus_mask, enemy[i].frame);
            break;
        }
      }
    }
  }
}




//////// BOSS functions ////////////////////
////////////////////////////////////////////

struct EndBoss
{
  public:
    int x;
    int y;
    int HP;
    boolean isActive = false;
    byte attackFase;

};

EndBoss shark;
EndBoss pirateShip;



void setBossShark()
{
  shark.x = 128;
  shark.y = 28;
  shark.HP = 10;
  shark.isActive = true;
  shark.attackFase = 0;
  sharkSlow = true;
  sharkSwimsRight = false;
  sharkFrame = 0;
  faseTimer = 0;

}


void checkBossShark()
{
  if (arduboy.everyXFrames(4 + (6 * sharkSlow))) sharkFrame++;
  if (sharkFrame > 3 ) sharkFrame = 0;
}


void sharkSwimsRightOnScreen()
{
  sharkSlow = true;
  if (shark.x > 96)shark.x--;
  else shark.attackFase++;
}


void sharkSwimsLeftOnScreen()
{
  sharkSlow = true;
  if (shark.x < 0)shark.x++;
  else shark.attackFase++;
}


void sharkSwimsLeftFollow()
{
  if (arduboy.everyXFrames(4) && (shark.x > mermaid.x))
  {
    if (shark.y < mermaid.y)shark.y++;
    if (shark.y > mermaid.y)shark.y--;
  }
  if (shark.x > -40) shark.x -= 2;
  else
  {
    sharkSwimsRight = !sharkSwimsRight;
    shark.attackFase++;
  }
}


void sharkSwimsRightFollow()
{
  if (arduboy.everyXFrames(4) && (shark.x < mermaid.x))
  {
    if (shark.y < mermaid.y)shark.y++;
    if (shark.y > mermaid.y)shark.y--;
  }
  if (shark.x < 136) shark.x += 2;
  else
  {
    sharkSwimsRight = !sharkSwimsRight;
    shark.attackFase++;
  }
}


void sharkWait()
{
  if (arduboy.everyXFrames(4)) faseTimer++;
  if (faseTimer > 16)
  {
    shark.attackFase++;
    faseTimer = 0;
  }
}


void sharkSpeedUpFrame()
{
  sharkSlow = false;
  shark.attackFase++;
}


void sharkFixMermaidsPosition()
{
  mermaidsPosition = mermaid.y;
  shark.attackFase++;
}


void sharkSwimsRightFast()
{
  if (arduboy.everyXFrames(1))
  {
    if (shark.y < mermaidsPosition)shark.y += 2;
    if (shark.y > mermaidsPosition)shark.y -= 2;
  }
  if (shark.x < 136) shark.x += 4;
  else
  {
    sharkSwimsRight = !sharkSwimsRight;
    shark.attackFase++;
  }
}


void sharkSwimsLeftFast()
{
  if (arduboy.everyXFrames(1))
  {
    if (shark.y < mermaidsPosition)shark.y += 2;
    if (shark.y > mermaidsPosition)shark.y -= 2;
  }
  if (shark.x > -40) shark.x -= 4;
  else
  {
    sharkSwimsRight = !sharkSwimsRight;
    shark.attackFase++;
  }
}


void sharkRestart()
{
  shark.attackFase = 0;
}

typedef void (*FunctionPointer) ();

FunctionPointer sharkAttackFases[] =
{
  sharkSwimsRightOnScreen,
  sharkWait,
  sharkSwimsLeftFollow,
  sharkSwimsRightFollow,
  sharkSwimsLeftFollow,

  sharkSwimsLeftOnScreen,
  sharkWait,
  sharkSpeedUpFrame,
  sharkWait,
  sharkFixMermaidsPosition,
  sharkSwimsRightFast,

  sharkSwimsRightOnScreen,
  sharkWait,
  sharkSpeedUpFrame,
  sharkWait,
  sharkFixMermaidsPosition,
  sharkSwimsLeftFast,

  sharkSwimsLeftOnScreen,
  sharkWait,
  sharkSpeedUpFrame,
  sharkWait,
  sharkFixMermaidsPosition,
  sharkSwimsRightFast,
  sharkRestart,
};


void drawShark()
{
  if (shark.isActive) sprites.drawSelfMasked(shark.x, shark.y, enemyShark, sharkFrame + (4 * sharkSwimsRight));
}


void drawPirateShip()
{
  if (pirateShip.isActive)
  {
    sprites.drawSelfMasked(pirateShip.x + 16, pirateShip.y + 20, pirateshipShip, 0);
    sprites.drawSelfMasked(pirateShip.x + 24, pirateShip.y + 5, pirateshipSail, 0);
    sprites.drawSelfMasked(pirateShip.x, pirateShip.y + 19, pirateshipBowsprit, 0);
    sprites.drawSelfMasked(pirateShip.x + 36, pirateShip.y + 0, pirateshipCrowsnest, 0);
  }
}


typedef void (*FunctionPointer) ();

FunctionPointer drawBosses[] =
{
  drawShark,
  drawPirateShip,
};



#endif
