#ifndef ENEMIES_H
#define ENEMIES_H

#include <Arduino.h>
#include "globals.h"

#define ENEMY_FISHY                     0
#define ENEMY_FISH                      1
#define ENEMY_JELLYFISH                 2
#define ENEMY_OCTOPUS                   3
#define ENEMY_SKULL                     4
#define ENEMY_SEAHORSETINY              5

#define ENDBOSS_SHARK                   0
#define ENDBOSS_SEAHORSE                1
#define ENDBOSS_PIRATESHIP              2

#define LEVEL_WITH_SHARK                1
#define LEVEL_WITH_SEAHORSE             2
#define LEVEL_WITH_PIRATESHIP           3

#define POINTS_FISHY                    5
#define POINTS_FISH                     8
#define POINTS_JELLYFISH                20
#define POINTS_OCTOPUS                  25
#define POINTS_SKULL                    4
#define POINTS_SEAHORSETINY             3

#define MAX_HP_FISHY                    2
#define MAX_HP_FISH                     4
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
#define JELLYFISH_COLLISION_WIDTH       16
#define OCTOPUS_COLLISION_WIDTH         16
#define SKULL_COLLISION_WIDTH           8
#define SEAHORSETINY_COLLISION_WIDTH    8

#define FISHY_COLLISION_HEIGHT          8
#define FISH_COLLISION_HEIGHT           14
#define JELLYFISH_COLLISION_HEIGHT      13
#define OCTOPUS_COLLISION_HEIGHT        16
#define SKULL_COLLISION_HEIGHT          8
#define SEAHORSETINY_COLLISION_HEIGHT   8

#define MAX_ONSCREEN_ENEMY_BULLETS      8
#define OCTOPUS_INK_BULLET              0
#define BULLET_DAMAGE                   1



byte endBossMaxHP[] = {MAX_HP_SHARK, MAX_HP_SEAHORSE, MAX_HP_PIRATESHIP};
byte endBossStartX[] = {28, 16, 10};
byte enemiesMaxHP[] = {MAX_HP_FISHY, MAX_HP_FISH, MAX_HP_JELLYFISH, MAX_HP_OCTOPUS, MAX_HP_SKULL, MAX_HP_SEAHORSETINY};
byte enemiesPoints[] = {POINTS_FISHY, POINTS_FISH, POINTS_JELLYFISH, POINTS_OCTOPUS, POINTS_SKULL, POINTS_SEAHORSETINY};
byte enemyCollisionWidth[] = {FISHY_COLLISION_WIDTH, FISH_COLLISION_WIDTH, JELLYFISH_COLLISION_WIDTH, OCTOPUS_COLLISION_WIDTH, SKULL_COLLISION_WIDTH, SEAHORSETINY_COLLISION_WIDTH};
byte enemyCollisionHeight[] = {FISHY_COLLISION_HEIGHT, FISH_COLLISION_HEIGHT, JELLYFISH_COLLISION_HEIGHT, OCTOPUS_COLLISION_HEIGHT, SKULL_COLLISION_HEIGHT, SEAHORSETINY_COLLISION_HEIGHT};

byte jellyFrame;
byte faseTimer;
byte mermaidsPosition;
byte currentEnemyBullet;


//////// Enemy functions ///////////////////
////////////////////////////////////////////

struct Enemies
{
  public:
    int x;
    int y;
    int HP;

    byte characteristics = 0b00000000;   //this byte holds all the enemies characteristics
    //                       ||||||||
    //                       |||||||└->  0 \
    //                       ||||||└-->  1  |  These 3 bits are used to determine the enemy type
    //                       |||||└--->  2 /
    //                       ||||└---->  3 the enemy is visible  (0 = false / 1 = true)
    //                       |||└----->  4 the enemy is dying    (0 = false / 1 = true)
    //                       ||└------>  5 the enemy is imune    (0 = false / 1 = true)
    //                       |└------->  6 the enemy is alive    (0 = false / 1 = true)
    //                       └-------->  7

    byte imuneTimer;

    byte frame;
    byte bulletsShot;
};

struct EnemyBullets
{
  public:
    int x;
    int y;
    byte frame;
    boolean isVisible;
    boolean direction;
};

Enemies enemy[MAX_ONSCREEN_ENEMIES];
EnemyBullets enemyBullet[MAX_ONSCREEN_ENEMY_BULLETS];


void checkEnemyBullet()
{
  if (arduboy.everyXFrames(6))
  {
    for (byte i = 0; i < MAX_ONSCREEN_ENEMY_BULLETS; i++)
    {
      if ((enemyBullet[i].x < -8) || (enemyBullet[i].y < -8) || (enemyBullet[i].y > 64)) enemyBullet[i].isVisible = false;
      if (enemyBullet[i].isVisible)
      {
        enemyBullet[i].x -= 2;
        enemyBullet[i].frame++;
        enemyBullet[i].y += (1 - (2 * enemyBullet[i].direction));
        if ((enemyBullet[i].frame) > 3) enemyBullet[i].frame = 0;
      }
    }
  }
}

void drawEnemyBullet()
{
  for (byte i = 0; i < MAX_ONSCREEN_ENEMY_BULLETS; i++)
  {
    if (enemyBullet[i].isVisible) sprites.drawSelfMasked(enemyBullet[i].x, enemyBullet[i].y, enemyBullets, enemyBullet[i].frame);
  }
}


void setEnemies()
{
  jellyFrame = 0;
  currentEnemyBullet = 0;
  for (byte i = 0; i < MAX_ONSCREEN_ENEMIES; i++)
  {
    enemy[i].frame = i;
    enemy[i].characteristics = 0;
    enemy[i].imuneTimer = 0;
    enemy[i].x = 128;
    enemy[i].bulletsShot = 0;
  }
  for (byte i = 0; i < MAX_ONSCREEN_ENEMY_BULLETS; i++)
  {
    enemyBullet[i].isVisible = false;
  }
}


void checkEnemies()
{
  for (byte i = 0; i < MAX_ONSCREEN_ENEMIES; i++)
  {
    if ((enemy[i].HP < 1) && !bitRead(enemy[i].characteristics, 4))
    {
      bitSet(enemy[i].characteristics, 4);
      bitClear(enemy[i].characteristics, 5);
      enemy[i].frame = 0;
    }
    if (bitRead(enemy[i].characteristics, 5))
    {
      if (arduboy.everyXFrames(3)) enemy[i].characteristics = enemy[i].characteristics ^ 0b00001000;
      enemy[i].imuneTimer++;
      if (enemy[i].imuneTimer > ENEMY_IMUNE_TIME)
      {
        enemy[i].imuneTimer = 0;
        bitClear(enemy[i].characteristics, 5);
        bitSet(enemy[i].characteristics, 3);
      }
    }
    if (!bitRead(enemy[i].characteristics, 4))
    {
      if (arduboy.everyXFrames(6)) enemy[i].frame++;
      if (enemy[i].characteristics & 0B00000111 != ENEMY_JELLYFISH && (enemy[i].frame > FRAMES_ENEMY)) enemy[i].frame = 0;
      if (enemy[i].characteristics & 0B00000111 == ENEMY_JELLYFISH && (enemy[i].frame > FRAMES_JELLYFISH)) enemy[i].frame = 0;
    }

    if (bitRead(enemy[i].characteristics, 4))
    {
      if (arduboy.everyXFrames(3))
      {
        if (bitRead(enemy[i].characteristics, 3)) scorePlayer += enemiesPoints[enemy[i].characteristics & 0B00000111];
        enemy[i].frame++;
      }
      if (enemy[i].frame > FRAMES_DYING)
      {
        bitClear(enemy[i].characteristics, 3);
        bitClear(enemy[i].characteristics, 4);
        bitClear(enemy[i].characteristics, 6);
        enemy[i].frame = 0;
      }
    }
    if ((enemy[i].x < -32) || (enemy[i].y < -32))
    {
      bitClear(enemy[i].characteristics, 3);
      bitClear(enemy[i].characteristics, 6);
      enemy[i].frame = 0;
    }
  }
}

void enemySetInLine(byte enemyType, byte firstEnemy, byte lastEnemy, byte x, byte y, int spacingX, int spacingY)
{
  for (byte i = firstEnemy; i < lastEnemy; i++)
  {
    enemy[i].frame = i;
    bitSet(enemy[i].characteristics, 3);
    bitClear(enemy[i].characteristics, 4);
    bitSet(enemy[i].characteristics, 6);
    enemy[i].characteristics = (enemy[i].characteristics & 0B11111000) + enemyType;
    enemy[i].x = x + (spacingX * (i - firstEnemy));
    enemy[i].y = y + (spacingY * (i - firstEnemy));
    enemy[i].HP = enemiesMaxHP[enemyType];
    enemy[i].bulletsShot = 0;
  }
}

void enemySwimRightLeft(byte firstEnemy, byte lastEnemy, byte speedEnemy)
{
  for (byte i = firstEnemy; i < lastEnemy; i++)
  {
    if (!bitRead(enemy[i].characteristics, 4)) enemy[i].x = enemy[i].x - speedEnemy;
  }
}

void enemySwimToMiddle(byte firstEnemy, byte lastEnemy, byte speedEnemy)
{
  for (byte i = firstEnemy; i < lastEnemy; i++)
  {
    if (!bitRead(enemy[i].characteristics, 4))
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
    if (!bitRead(enemy[i].characteristics, 4))
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
    if (!bitRead(enemy[i].characteristics, 4))
    {
      if (enemy[i].frame > 4 && enemy[i].frame < 7 )enemy[i].y = enemy[i].y - speedEnemy - 1;
      if (enemy[i].frame > 6 )enemy[i].y = enemy[i].y - speedEnemy;
    }
  }
}


void enemyShoot(byte firstEnemy, byte lastEnemy, byte amount)
{
  if (arduboy.everyXFrames(50))
  {
    for (byte i = firstEnemy; i < lastEnemy; i++)
    {
      if ((!bitRead(enemy[i].characteristics, 4)) && (enemy[i].x < 128) && (enemy[i].bulletsShot < amount))
      {
        enemy[i].bulletsShot++;
        enemyBullet[currentEnemyBullet].isVisible = true;
        enemyBullet[currentEnemyBullet].x = enemy[i].x + 2;
        enemyBullet[currentEnemyBullet].y = enemy[i].y;
        if (enemy[i].y < 24) enemyBullet[currentEnemyBullet].direction = false;
        else enemyBullet[currentEnemyBullet].direction = true;
        currentEnemyBullet++;
        if (currentEnemyBullet > MAX_ONSCREEN_ENEMY_BULLETS - 1) currentEnemyBullet = 0;
      }
    }
  }
}



void drawEnemies()
{
  for (byte i = 0; i < MAX_ONSCREEN_ENEMIES; i++)
  {
    if (bitRead(enemy[i].characteristics, 3))
    {
      if (bitRead(enemy[i].characteristics, 4)) sprites.drawSelfMasked(enemy[i].x, enemy[i].y, puff, enemy[i].frame);
      else
      {
        switch (enemy[i].characteristics & 0B00000111)
        {
          case ENEMY_FISHY:
            sprites.drawPlusMask(enemy[i].x, enemy[i].y, enemyFishy_plus_mask, enemy[i].frame);
            break;
          case ENEMY_FISH:
            sprites.drawPlusMask(enemy[i].x, enemy[i].y, enemyFish_plus_mask, enemy[i].frame);
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
            sprites.drawSelfMasked(enemy[i].x, enemy[i].y, pirateSkull, enemy[i].frame);
            break;
          case ENEMY_SEAHORSETINY:
            sprites.drawSelfMasked(enemy[i].x, enemy[i].y, seahorseTiny, 0);
            break;
        }
      }
    }
  }
}


//////// BOSS functions ////////////////////
////////////////////////////////////////////
//boolean endBossSwitch;
//boolean endBossSwimsRight;
struct EndBosses
{
  public:
    int x;
    int y;
    int HP;

    byte characteristics = 0b00000000;   //this byte holds all the enemies characteristics
    //                       ||||||||
    //                       |||||||└->  0 \
    //                       ||||||└-->  1 /  These 2 bits are used to determine the boss type
    //                       |||||└--->  2 the boss swims right (0 = false / 1 = true)
    //                       ||||└---->  3 the boss is visible  (0 = false / 1 = true)
    //                       |||└----->  4 the boss is dying    (0 = false / 1 = true)
    //                       ||└------>  5 the boss is imune    (0 = false / 1 = true)
    //                       |└------->  6 the boss is alive    (0 = false / 1 = true)
    //                       └-------->  7 the boss switches    (0 = false / 1 = true)

    byte attackFase;
    byte currentBullet;
    byte imuneTimer;
    byte frame;
    byte actingFase;
};

EndBosses endBoss;


void setBosses()
{
  endBoss.characteristics = 0;
  endBoss.y = 128;
}


void setEndBoss()
{
  backgroundIsVisible = false;
  endBoss.characteristics = 0B10000000;
  endBoss.attackFase = 0;
  endBoss.imuneTimer = 0;
  endBoss.frame = 0;
  endBoss.actingFase = 0;
  faseTimer = 0;
  endBoss.x = 128;
  endBoss.y = endBossStartX[level / 3];
  endBoss.HP = endBossMaxHP[level / 3];
  endBoss.characteristics = (endBoss.characteristics & 0B11111100) + (level / 3);

}


void checkEndBoss()
{
  if (bitRead(endBoss.characteristics, 3))
  {
    if (endBoss.currentBullet > MAX_BOSS_BULLETS - 1) endBoss.currentBullet = 0;
    for (byte i = 0; i < MAX_BOSS_BULLETS; i++)
    {
      if (!bitRead(enemy[i].characteristics, 4))
      {
        enemy[i].x -= 1;
        if (enemy[i].characteristics & 0B00000111 == ENEMY_SEAHORSETINY)
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

  if ((endBoss.HP < 1) && !bitRead(endBoss.characteristics, 4))
  {
    bitSet(endBoss.characteristics, 4);
    bitClear(endBoss.characteristics, 5);
    for (byte i = 0; i < MAX_ONSCREEN_ENEMIES; i++)
    {
      bitSet(enemy[i].characteristics, 4);
    }
    endBoss.frame = 0;
  }
  
  if (bitRead(endBoss.characteristics, 5))
  {
    if (arduboy.everyXFrames(3)) endBoss.characteristics = endBoss.characteristics ^ 0B00001000;
    endBoss.imuneTimer++;
    if (endBoss.imuneTimer > SHARK_IMUNE_TIME)
    {
      endBoss.imuneTimer = 0;
      bitSet(endBoss.characteristics, 3);
      bitClear(endBoss.characteristics, 5);
    }
  }
  
  if (bitRead(endBoss.characteristics, 3))
  {
    if (!bitRead(endBoss.characteristics, 4))
    {
      if (endBoss.characteristics & 0B00000011 == ENDBOSS_SHARK)
      {
        if (arduboy.everyXFrames(4 + (6 * bitRead(endBoss.characteristics,7)))) endBoss.frame++;
      }
      else if (arduboy.everyXFrames(10)) endBoss.frame++;
      if (endBoss.frame > 3 ) endBoss.frame = 0;
    }
    else
    {
      if (arduboy.everyXFrames(3)) endBoss.frame++;
      if (endBoss.frame > FRAMES_DYING)
      {
        bitClear(endBoss.characteristics, 4);
        bitClear(endBoss.characteristics, 3);
        bitClear(endBoss.characteristics, 6);
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
  if (bitRead(endBoss.characteristics, 6)) drawEnemyHud(endBoss.HP, endBossMaxHP[endBoss.characteristics & 0B00000011]);
  if (bitRead(endBoss.characteristics, 3))
  {
    if (bitRead(endBoss.characteristics, 4)) sprites.drawSelfMasked(endBoss.x, endBoss.y, puff, endBoss.frame);
    else
    {
      switch (endBoss.characteristics & 0B00000011)
      {
        case ENDBOSS_SHARK:
          sprites.drawSelfMasked(endBoss.x, endBoss.y, shark, endBoss.frame + (4 * bitRead(endBoss.characteristics,2)));
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
  bitSet(endBoss.characteristics,7);
  bitSet(endBoss.characteristics, 5);
  if (endBoss.x > 96)endBoss.x--;
  else endBoss.attackFase++;
}


void sharkSwimsLeftOnScreen()
{
  bitSet(endBoss.characteristics,7);
  bitSet(endBoss.characteristics, 5);
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
    endBoss.characteristics = endBoss.characteristics ^ 0B00000100;
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
    endBoss.characteristics = endBoss.characteristics ^ 0B00000100;
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
  bitClear(endBoss.characteristics,7);
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
    endBoss.characteristics = endBoss.characteristics ^ 0B00000100;
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
    endBoss.characteristics = endBoss.characteristics ^ 0B00000100;
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
  bitSet(enemy[endBoss.currentBullet].characteristics, 3);
  bitClear(enemy[endBoss.currentBullet].characteristics, 4);
  enemy[endBoss.currentBullet].characteristics = (enemy[endBoss.currentBullet].characteristics & 0B11111000) + ENEMY_SEAHORSETINY;
  enemy[endBoss.currentBullet].x = endBoss.x + 2;
  enemy[endBoss.currentBullet].y = endBoss.y + 16;
  enemy[endBoss.currentBullet].HP = MAX_HP_SEAHORSETINY;
  endBoss.currentBullet++;
}

void seahorseSwimsRightOnScreen()
{
  bitSet(endBoss.characteristics,7);
  bitSet(endBoss.characteristics, 5);
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
  bitSet(enemy[endBoss.currentBullet].characteristics, 3);
  bitClear(enemy[endBoss.currentBullet].characteristics, 4);
  enemy[endBoss.currentBullet].characteristics = (enemy[endBoss.currentBullet].characteristics & 0B11111000) + ENEMY_SKULL;
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
  if (bitRead(endBoss.characteristics,7))
  {
    if (endBoss.y > -20)
    {
      if (arduboy.everyXFrames(22)) shootingSkull();
      endBoss.y -= 2;
    }
    else endBoss.characteristics = endBoss.characteristics ^ 0B10000000;
  }
  if (!bitRead(endBoss.characteristics,7))
  {
    if (endBoss.y < 40)
    {
      if (arduboy.everyXFrames(22)) shootingSkull();
      endBoss.y += 2;
    }
    else
    {
      endBoss.characteristics = endBoss.characteristics ^ 0B10000000;
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
  endBoss.x =  endBoss.x + (2 * (1 - (2 * bitRead(endBoss.characteristics,7))));
  endBoss.characteristics = endBoss.characteristics ^ 0B10000000;
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
