#ifndef ENEMIES_H
#define ENEMIES_H

#include <Arduino.h>
#include "globals.h"

#define ENEMY_FISHY                     0
#define ENEMY_FISH                      1
#define ENEMY_EEL                       2
#define ENEMY_JELLYFISH                 3
#define ENEMY_OCTOPUS                   4
#define ENEMY_SKULL                     5
#define ENEMY_SEAHORSETINY              6

#define ENDBOSS_SHARK                   0
#define ENDBOSS_SEAHORSE                1
#define ENDBOSS_PIRATESHIP              2

#define LEVEL_WITH_SHARK                1
#define LEVEL_WITH_SEAHORSE             2
#define LEVEL_WITH_PIRATESHIP           3

#define POINTS_FISHY                    5
#define POINTS_FISH                     8
#define POINTS_EEL                      15
#define POINTS_JELLYFISH                20
#define POINTS_OCTOPUS                  25
#define POINTS_SKULL                    4
#define POINTS_SEAHORSETINY             3

#define MAX_HP_FISHY                    2
#define MAX_HP_FISH                     4
#define MAX_HP_EEL                      4
#define MAX_HP_JELLYFISH                2
#define MAX_HP_OCTOPUS                  4
#define MAX_HP_SKULL                    1
#define MAX_HP_SEAHORSETINY             1

#define MAX_HP_SHARK                    18
#define MAX_HP_SEAHORSE                 27
#define MAX_HP_PIRATESHIP               36

#define POINTS_SHARK                    100
#define POINTS_SEAHORSE                 150
#define POINTS_PIRATESHIP               250

#define FRAMES_ENEMY                    3
#define FRAMES_JELLYFISH                10
#define FRAMES_DYING                    5

#define MAX_ONSCREEN_ENEMIES            8
#define MAX_ENEMY_BULLETS               3
#define MAX_BOSS_BULLETS                6

#define SHARK_IMUNE_TIME                25
#define SEAHORSE_IMUNE_TIME             25
#define PIRATESHIP_IMUNE_TIME           25

#define ENEMY_IMUNE_TIME                20

#define FISHY_COLLISION_WIDTH           14
#define FISH_COLLISION_WIDTH            14
#define EEL_COLLISION_WIDTH             30
#define JELLYFISH_COLLISION_WIDTH       16
#define OCTOPUS_COLLISION_WIDTH         16
#define SKULL_COLLISION_WIDTH           8
#define SEAHORSETINY_COLLISION_WIDTH    8

#define FISHY_COLLISION_HEIGHT          8
#define FISH_COLLISION_HEIGHT           14
#define EEL_COLLISION_HEIGHT            7
#define JELLYFISH_COLLISION_HEIGHT      13
#define OCTOPUS_COLLISION_HEIGHT        16
#define SKULL_COLLISION_HEIGHT          8
#define SEAHORSETINY_COLLISION_HEIGHT   8



byte endBossMaxHP[] = {MAX_HP_SHARK, MAX_HP_SEAHORSE, MAX_HP_PIRATESHIP};
byte enemiesMaxHP[] = {MAX_HP_FISHY, MAX_HP_FISH, MAX_HP_EEL, MAX_HP_JELLYFISH, MAX_HP_OCTOPUS, MAX_HP_SKULL, MAX_HP_SEAHORSETINY};
byte enemiesPoints[] = {POINTS_FISHY, POINTS_FISH, POINTS_EEL, POINTS_JELLYFISH, POINTS_OCTOPUS, POINTS_SKULL, POINTS_SEAHORSETINY};
byte enemyCollisionWidth[] = {FISHY_COLLISION_WIDTH, FISH_COLLISION_WIDTH, EEL_COLLISION_WIDTH, JELLYFISH_COLLISION_WIDTH, OCTOPUS_COLLISION_WIDTH, SKULL_COLLISION_WIDTH, SEAHORSETINY_COLLISION_WIDTH};
byte enemyCollisionHeight[] = {FISHY_COLLISION_HEIGHT, FISH_COLLISION_HEIGHT, EEL_COLLISION_HEIGHT, JELLYFISH_COLLISION_HEIGHT, OCTOPUS_COLLISION_HEIGHT, SKULL_COLLISION_HEIGHT, SEAHORSETINY_COLLISION_HEIGHT};

byte jellyFrame;
byte faseTimer;
byte mermaidsPosition;
boolean endBossSwitch;
boolean endBossSwimsRight;


//////// Enemy functions ///////////////////
////////////////////////////////////////////

struct Enemies
{
  public:
    int x;
    int y;
    int HP;
    boolean isVisible;
    boolean isDying;
    boolean isImune;
    boolean isAlive;
    byte imuneTimer;
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
    enemy[i].isVisible = false;
    enemy[i].isDying = false;
    enemy[i].isImune = false;
    enemy[i].isAlive = false;
    enemy[i].imuneTimer = 0;
    enemy[i].x = 128;
  }
}


void checkEnemies()
{
  for (byte i = 0; i < MAX_ONSCREEN_ENEMIES; i++)
  {
    if ((enemy[i].HP < 1) && !enemy[i].isDying)
    {
      enemy[i].isImune = false;
      enemy[i].isDying = true;
      enemy[i].frame = 0;
    }
    if (enemy[i].isImune)
    {
      if (arduboy.everyXFrames(3)) enemy[i].isVisible = !enemy[i].isVisible;
      enemy[i].imuneTimer++;
      if (enemy[i].imuneTimer > ENEMY_IMUNE_TIME)
      {
        enemy[i].imuneTimer = 0;
        enemy[i].isImune = false;
        enemy[i].isVisible = true;
      }
    }
    if (!enemy[i].isDying)
    {
      if (arduboy.everyXFrames(6)) enemy[i].frame++;
      if (enemy[i].type != ENEMY_JELLYFISH && (enemy[i].frame > FRAMES_ENEMY)) enemy[i].frame = 0;
      if (enemy[i].type == ENEMY_JELLYFISH && (enemy[i].frame > FRAMES_JELLYFISH)) enemy[i].frame = 0;
    }

    if (enemy[i].isDying)
    {
      if (arduboy.everyXFrames(3))
      {
        if (enemy[i].isVisible) scorePlayer += enemiesPoints[enemy[i].type];
        enemy[i].frame++;
      }
      if (enemy[i].frame > FRAMES_DYING)
      {
        enemy[i].isDying = false;
        enemy[i].isAlive = false;
        enemy[i].isVisible = false;
        enemy[i].frame = 0;
      }
    }
    if ((enemy[i].x < -32) || (enemy[i].y < -32))
    {
      enemy[i].isVisible = false;
      enemy[i].isAlive = false;
      enemy[i].frame = 0;
    }
  }
}

void enemySetInLine(byte enemyType, byte firstEnemy, byte lastEnemy, byte x, byte y, int spacingX, int spacingY)
{
  for (byte i = firstEnemy; i < lastEnemy; i++)
  {
    enemy[i].frame = i;
    enemy[i].isVisible = true;
    enemy[i].isDying = false;
    enemy[i].isAlive = true;
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
    if (enemy[i].isVisible)
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
          case ENEMY_SKULL:
            sprites.drawPlusMask(enemy[i].x, enemy[i].y, pirateSkull_plus_mask, enemy[i].frame);
            break;
          case ENEMY_SEAHORSETINY:
            sprites.drawPlusMask(enemy[i].x, enemy[i].y, seahorseTiny_plus_mask, 0);
            break;
        }
      }
    }
  }
}




//////// BOSS functions ////////////////////
////////////////////////////////////////////

struct EndBosses
{
  public:
    int x;
    int y;
    int HP;
    boolean isVisible;
    boolean isImune;
    boolean isDying;
    boolean isAlive;
    byte attackFase;
    byte currentBullet;
    byte imuneTimer;
    byte frame;
    byte type;
    byte actingFase;
};

EndBosses endBoss;


void setBosses()
{
  endBoss.isAlive = false;
  endBoss.isVisible = false;
  endBoss.isImune = false;
  endBoss.y = 128;
}


void setEndBoss()
{
  backgroundIsVisible = false;
  endBoss.isVisible = true;
  endBoss.isImune = false;
  endBoss.isDying = false;
  endBoss.isAlive = true;
  endBoss.attackFase = 0;
  endBoss.imuneTimer = 0;
  endBoss.frame = 0;
  endBoss.actingFase = 0;
  faseTimer = 0;
  endBossSwitch = true;
  endBossSwimsRight = false;
  switch (level)
  {
    case LEVEL_WITH_SHARK:
      endBoss.x = 128;
      endBoss.y = 28;
      endBoss.type = ENDBOSS_SHARK;
      endBoss.HP = MAX_HP_SHARK;
      break;
    case LEVEL_WITH_SEAHORSE:
      endBoss.x = 128;
      endBoss.y = 16;
      endBoss.type = ENDBOSS_SEAHORSE;
      endBoss.HP = MAX_HP_SEAHORSE;
      break;
    case LEVEL_WITH_PIRATESHIP:
      endBoss.x = 128;
      endBoss.y = 10;
      endBoss.type = ENDBOSS_PIRATESHIP;
      endBoss.HP = MAX_HP_PIRATESHIP;
      break;
  }
}


void checkEndBoss()
{
  if (endBoss.isVisible)
  {
    if (endBoss.currentBullet > MAX_BOSS_BULLETS - 1) endBoss.currentBullet = 0;
    for (byte i = 0; i < MAX_BOSS_BULLETS; i++)
    {
      if (!enemy[i].isDying)
      {
        enemy[i].x -= 1;
        if (enemy[i].type == ENEMY_SEAHORSETINY)
        {
          if (arduboy.everyXFrames(3))
          {
            switch (i)
            {
              case 1: case 4:
                enemy[i].y--;
                break;
              case 2: case 5:
                enemy[i].y++;
                break;
            }
          }
        }
      }
    }
  }

  if ((endBoss.HP < 1) && !endBoss.isDying)
  {
    endBoss.isImune = false;
    endBoss.isDying = true;
    for (byte i = 0; i < MAX_ONSCREEN_ENEMIES; i++)
    {
      enemy[i].isDying = true;
    }
    endBoss.frame = 0;
  }
  if (endBoss.isImune)
  {
    if (arduboy.everyXFrames(3)) endBoss.isVisible = !endBoss.isVisible;
    endBoss.imuneTimer++;
    if (endBoss.imuneTimer > SHARK_IMUNE_TIME)
    {
      endBoss.imuneTimer = 0;
      endBoss.isImune = false;
      endBoss.isVisible = true;
    }
  }
  if (endBoss.isVisible)
  {
    if (!endBoss.isDying)
    {
      if (endBoss.type == ENDBOSS_SHARK)
      {
        if (arduboy.everyXFrames(4 + (6 * endBossSwitch))) endBoss.frame++;
      }
      else if (arduboy.everyXFrames(10)) endBoss.frame++;
      if (endBoss.frame > 3 ) endBoss.frame = 0;
    }
    else
    {
      if (arduboy.everyXFrames(3)) endBoss.frame++;
      if (endBoss.frame > FRAMES_DYING)
      {
        endBoss.isDying = false;
        endBoss.isVisible = false;
        endBoss.isAlive = false;
        endBoss.frame = 0;
      }
    }
  }
}


void drawEnemyHud(byte currentLife, byte maxLife)
{
  for (byte i = 0; i < (currentLife / 3)  + 1; i++)
  {
    sprites.drawPlusMask(64 - 2 * (maxLife / 3) + 4 * i, 60, bossLife_plus_mask, 0);
  }
}


void drawBosses()
{
  if (endBoss.isAlive) drawEnemyHud(endBoss.HP, endBossMaxHP[endBoss.type]);
  if (endBoss.isVisible)
  {
    if (endBoss.isDying) sprites.drawSelfMasked(endBoss.x, endBoss.y, puff, endBoss.frame);
    else
    {
      switch (endBoss.type)
      {
        case ENDBOSS_SHARK:
          sprites.drawSelfMasked(endBoss.x, endBoss.y, Shark, endBoss.frame + (4 * endBossSwimsRight));
          break;
        case ENDBOSS_SEAHORSE:
          sprites.drawSelfMasked(endBoss.x, endBoss.y, seahorse, 0);
          sprites.drawSelfMasked(endBoss.x + 12, endBoss.y + 15, seahorseFin, endBoss.frame);
          break;
        case ENDBOSS_PIRATESHIP:
          sprites.drawSelfMasked(endBoss.x, endBoss.y + 23, pirateshipBowsprit, 0);
          sprites.drawSelfMasked(endBoss.x + 16, endBoss.y + 24, pirateshipHull, 0);
          sprites.drawSelfMasked(endBoss.x + 24, endBoss.y + 16, pirateshipSail, endBoss.frame);
          sprites.drawSelfMasked(endBoss.x + 24, endBoss.y + 8, pirateshipYardarm, 0);
          sprites.drawSelfMasked(endBoss.x + 36, endBoss.y, pirateshipCrowsnest, 0);
          break;
      }
    }
  }
}

//////// SHARK functions ///////////////////
////////////////////////////////////////////
void sharkSwimsRightOnScreen()
{
  endBossSwitch = true;
  endBoss.isImune = true;
  if (endBoss.x > 96)endBoss.x--;
  else endBoss.attackFase++;
}


void sharkSwimsLeftOnScreen()
{
  endBossSwitch = true;
  endBoss.isImune = true;
  if (endBoss.x < 0)endBoss.x++;
  else endBoss.attackFase++;
}


void sharkSwimsLeftFollow()
{
  if (arduboy.everyXFrames(4) && (endBoss.x > mermaid.x))
  {
    if (endBoss.y < mermaid.y)endBoss.y++;
    if (endBoss.y > mermaid.y)endBoss.y--;
  }
  if (endBoss.x > -40) endBoss.x -= 2;
  else
  {
    endBossSwimsRight = !endBossSwimsRight;
    endBoss.attackFase++;
  }
}


void sharkSwimsRightFollow()
{
  if (arduboy.everyXFrames(4) && (endBoss.x < mermaid.x))
  {
    if (endBoss.y < mermaid.y)endBoss.y++;
    if (endBoss.y > mermaid.y)endBoss.y--;
  }
  if (endBoss.x < 136) endBoss.x += 2;
  else
  {
    endBossSwimsRight = !endBossSwimsRight;
    endBoss.attackFase++;
  }
}


void sharkWait()
{
  if (arduboy.everyXFrames(4)) faseTimer++;
  if (faseTimer > 16)
  {
    endBoss.attackFase++;
    faseTimer = 0;
  }
}


void sharkSpeedUpFrame()
{
  endBossSwitch = false;
  endBoss.attackFase++;
}


void sharkFixMermaidsPosition()
{
  mermaidsPosition = mermaid.y;
  endBoss.attackFase++;
}


void sharkSwimsRightFast()
{
  if (arduboy.everyXFrames(1))
  {
    if (endBoss.y < mermaidsPosition)endBoss.y += 2;
    if (endBoss.y > mermaidsPosition)endBoss.y -= 2;
  }
  if (endBoss.x < 136) endBoss.x += 5;
  else
  {
    endBossSwimsRight = !endBossSwimsRight;
    endBoss.attackFase++;
  }
}


void sharkSwimsLeftFast()
{
  if (arduboy.everyXFrames(1))
  {
    if (endBoss.y < mermaidsPosition)endBoss.y += 2;
    if (endBoss.y > mermaidsPosition)endBoss.y -= 2;
  }
  if (endBoss.x > -40) endBoss.x -= 5;
  else
  {
    endBossSwimsRight = !endBossSwimsRight;
    endBoss.attackFase++;
  }
}


void sharkRestart()
{
  endBoss.attackFase = 0;
}


typedef void (*FunctionPointer) ();
const FunctionPointer PROGMEM sharkAttackFases[] =
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




//////// SEAHORSE functions ////////////////
////////////////////////////////////////////
void shootingSeahorse()
{
  enemy[endBoss.currentBullet].isVisible = true;
  enemy[endBoss.currentBullet].isDying = false;
  enemy[endBoss.currentBullet].type = ENEMY_SEAHORSETINY;
  enemy[endBoss.currentBullet].x = endBoss.x + 2;
  enemy[endBoss.currentBullet].y = endBoss.y + 16;
  enemy[endBoss.currentBullet].HP = MAX_HP_SEAHORSETINY;
  endBoss.currentBullet++;
}

void seahorseSwimsRightOnScreen()
{
  endBossSwitch = true;
  endBoss.isImune = true;
  if (endBoss.x > 96)endBoss.x--;
  else endBoss.attackFase++;
}

void seahorseWait()
{
  if (arduboy.everyXFrames(4)) faseTimer++;
  if (faseTimer > 16)
  {
    endBoss.attackFase++;
    faseTimer = 0;
  }
}

void seahorseSineAndShoot()
{

  if (arduboy.everyXFrames(40)) shootingSeahorse();
  if (arduboy.everyXFrames(6))
  {
    endBoss.actingFase++;
    if (endBoss.actingFase < 9)
    {
      endBoss.x -= 1;
      endBoss.y -= 1;
      return;
    }
    if (endBoss.actingFase < 17)
    {
      endBoss.x += 1;
      endBoss.y -= 1;
      return;
    }
    if (endBoss.actingFase < 25)
    {
      endBoss.x += 1;
      endBoss.y += 1;
      return;
    }
    if (endBoss.actingFase < 41)
    {
      endBoss.x -= 1;
      endBoss.y += 1;
      return;
    }
    if (endBoss.actingFase < 49)
    {
      endBoss.x += 1;
      endBoss.y += 1;
      return;
    }
    if (endBoss.actingFase < 57)
    {
      endBoss.x += 1;
      endBoss.y -= 1;
      return;
    }
    if (endBoss.actingFase < 65)
    {
      endBoss.x -= 1;
      endBoss.y -= 1;
      return;
    }
    if (endBoss.actingFase > 64)
    {
      endBoss.actingFase = 0;
    }
  }
}




typedef void (*FunctionPointer) ();
const FunctionPointer PROGMEM seahorseAttackFases[] =
{
  seahorseSwimsRightOnScreen,
  seahorseWait,
  seahorseSineAndShoot,
};


//////// PIRATESHIP functions //////////////
////////////////////////////////////////////

void shootingSkull()
{
  enemy[endBoss.currentBullet].frame = 0;
  enemy[endBoss.currentBullet].isVisible = true;
  enemy[endBoss.currentBullet].isDying = false;
  enemy[endBoss.currentBullet].type = ENEMY_SKULL;
  enemy[endBoss.currentBullet].x = endBoss.x + 16;
  enemy[endBoss.currentBullet].y = endBoss.y + 20;
  enemy[endBoss.currentBullet].HP = MAX_HP_SKULL;
  endBoss.currentBullet++;
}



void pirateShipSailsRightOnScreen()
{
  if (endBoss.x > 64)endBoss.x--;
  else endBoss.attackFase++;
}

void pirateShipWait()
{
  if (arduboy.everyXFrames(4)) faseTimer++;
  if (faseTimer > 16)
  {
    endBoss.attackFase++;
    faseTimer = 0;
  }
}

void pirateShipGoesUpDownAndShoots()
{
  if (endBossSwitch)
  {
    if (endBoss.y > -20)
    {
      if (arduboy.everyXFrames(22)) shootingSkull();
      endBoss.y -= 2;
    }
    else endBossSwitch = !endBossSwitch;
  }
  if (!endBossSwitch)
  {
    if (endBoss.y < 40)
    {
      if (arduboy.everyXFrames(22)) shootingSkull();
      endBoss.y += 2;
    }
    else
    {
      endBossSwitch = !endBossSwitch;
      endBoss.actingFase++;
    }
  }
  if (endBoss.actingFase > 4)
  {
    endBoss.actingFase = 0;
    endBoss.attackFase++;
  }
}

void pirateShipGoesToMiddle()
{
  if (endBoss.y > 11)endBoss.y -= 2;
  else endBoss.attackFase++;
}


void pirateShipGoesUpForAttack()
{
  if (endBoss.y > -11)endBoss.y -= 2;
  else endBoss.attackFase++;
}

void pirateShipBacksUp()
{
  if (endBoss.x < 71)endBoss.x++;
  else endBoss.attackFase++;
}

void pirateShipLaunches()
{
  if (endBoss.x > -21)endBoss.x -= 10;
  else endBoss.attackFase++;
}

void pirateShipTrembles()
{
  endBoss.x =  endBoss.x + (2 * (1 - (2 * endBossSwitch)));
  endBossSwitch = !endBossSwitch;
  endBoss.actingFase++;
  if (endBoss.actingFase > 5)
  {
    endBoss.actingFase = 0;
    endBoss.attackFase++;
  }

}

void pirateShipRestart()
{
  endBoss.attackFase = 0;
}


typedef void (*FunctionPointer) ();
const FunctionPointer PROGMEM pirateShipAttackFases[] =
{
  pirateShipSailsRightOnScreen,
  pirateShipWait,
  pirateShipGoesUpDownAndShoots,
  pirateShipGoesToMiddle,
  pirateShipWait,
  pirateShipGoesUpForAttack,
  pirateShipBacksUp,
  pirateShipLaunches,
  pirateShipTrembles,
  pirateShipBacksUp,
  pirateShipRestart,
};


#endif
