#ifndef ENEMIES_H
#define ENEMIES_H

#include <Arduino.h>
#include "globals.h"

#define ENEMY_FISHY                  0
#define ENEMY_FISH                   1
#define ENEMY_EEL                    2
#define ENEMY_JELLYFISH              3
#define ENEMY_OCTOPUS                4
#define ENEMY_SKULL                  5

#define MAX_HP_FISHY                 2
#define MAX_HP_FISH                  4
#define MAX_HP_EEL                   4
#define MAX_HP_JELLYFISH             2
#define MAX_HP_OCTOPUS               4
#define MAX_HP_SKULL                 1

#define MAX_HP_SHARK                 18
#define MAX_HP_SEAHORSE              27
#define MAX_HP_PIRATESHIP            36

#define FRAMES_ENEMY                 3
#define FRAMES_JELLYFISH             10
#define FRAMES_DYING                 5

#define MAX_ONSCREEN_ENEMIES         8
#define MAX_ENEMY_BULLETS            3
#define MAX_BOSS_BULLETS             3

#define SHARK_IMUNE_TIME             15



byte enemiesMaxHP[] = {MAX_HP_FISHY, MAX_HP_FISH, MAX_HP_EEL, MAX_HP_JELLYFISH, MAX_HP_OCTOPUS, MAX_HP_SKULL};

byte jellyFrame;
byte faseTimer;
byte mermaidsPosition;
boolean bossSlow;
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
    if ((enemy[i].HP < 1) && !enemy[i].isDying)
    {
      enemy[i].isDying = true;
      enemy[i].frame = 0;
    }
    if (!enemy[i].isDying)
    {
      if (arduboy.everyXFrames(6)) enemy[i].frame++;
      if (enemy[i].type != ENEMY_JELLYFISH && (enemy[i].frame > FRAMES_ENEMY)) enemy[i].frame = 0;
      if (enemy[i].type == ENEMY_JELLYFISH && (enemy[i].frame > FRAMES_JELLYFISH)) enemy[i].frame = 0;
    }

    if (enemy[i].isDying)
    {
      if (arduboy.everyXFrames(3)) enemy[i].frame++;
      if (enemy[i].frame > FRAMES_DYING)
      {
        enemy[i].isDying = false;
        enemy[i].isActive = false;
        enemy[i].frame = 0;
      }
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
          case ENEMY_SKULL:
            sprites.drawPlusMask(enemy[i].x, enemy[i].y, pirateSkull_plus_mask, enemy[i].frame);
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
    boolean isImune = false;
    boolean isDying = false;
    boolean isDead = true;
    byte attackFase;
    byte currentBullet;
    byte imuneTimer;
    byte frame;
};

EndBoss shark;
EndBoss seahorse;
EndBoss pirateShip;

void setBosses()
{
  shark.isDead = true;
  seahorse.isDead = true;
  pirateShip.isDead = true;
}


void drawEnemyHud(byte currentLife, byte maxLife)
{
  for (byte i = 0; i < (currentLife / 3)  + 1; i++)
  {
    sprites.drawPlusMask(64 - 2 * (maxLife / 3) + 4 * i, 60, bossLife_plus_mask, 0);
  }
}

//////// SHARK functions ///////////////////
////////////////////////////////////////////

void setShark()
{
  shark.x = 128;
  shark.y = 28;
  shark.HP = MAX_HP_SHARK;
  shark.isActive = true;
  shark.attackFase = 0;
  bossSlow = true;
  sharkSwimsRight = false;
  shark.isImune = false;
  shark.isDying = false;
  shark.isDead = false;
  shark.imuneTimer = 0;
  shark.frame = 0;
  faseTimer = 0;
}


void checkShark()
{
  if ((shark.HP < 1) && !shark.isDying)
  {
    shark.isDying = true;
    shark.frame = 0;
  }
  if (shark.isImune)
  {
    if (arduboy.everyXFrames(3)) shark.isActive = !shark.isActive;
    shark.imuneTimer++;
    if (shark.imuneTimer > SHARK_IMUNE_TIME)
    {
      shark.imuneTimer = 0;
      shark.isImune = false;
      shark.isActive = true;
    }
  }
  if (shark.isActive)
  {
    if (!shark.isDying)
    {
      if (arduboy.everyXFrames(4 + (6 * bossSlow))) shark.frame++;
      if (shark.frame > 3 ) shark.frame = 0;
    }
    else
    {
      if (arduboy.everyXFrames(3)) shark.frame++;
      if (shark.frame > FRAMES_DYING)
      {
        shark.isDying = false;
        shark.isActive = false;
        shark.isDead = true;
        shark.frame = 0;
      }
    }
  }
}


void sharkSwimsRightOnScreen()
{
  bossSlow = true;
  if (shark.x > 96)shark.x--;
  else shark.attackFase++;
}


void sharkSwimsLeftOnScreen()
{
  bossSlow = true;
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
  bossSlow = false;
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


void drawShark()
{
  if (shark.isActive)
  {
    if (shark.isDying) sprites.drawSelfMasked(shark.x, shark.y, puff, shark.frame);
    else
    {
      sprites.drawSelfMasked(shark.x, shark.y, enemyShark, shark.frame + (4 * sharkSwimsRight));
    }
  }
  if (!shark.isDead)drawEnemyHud(shark.HP, MAX_HP_SHARK);
}

//////// SEAHORSE functions ////////////////
////////////////////////////////////////////

void setSeahorse()
{
  seahorse.x = 128;
  seahorse.y = 28;
  seahorse.HP = MAX_HP_SEAHORSE;
  seahorse.isActive = true;
  seahorse.attackFase = 0;
  seahorse.currentBullet = 0;
  seahorse.isImune = false;
  seahorse.isDying = false;
  seahorse.isDead = false;
  seahorse.imuneTimer = 0;
  bossSlow = true;
  faseTimer = 0;
}


void checkSeahorse()
{
  if (seahorse.isActive)
  {

  }
}



typedef void (*FunctionPointer) ();
const FunctionPointer PROGMEM seahorseAttackFases[] =
{
  
};

void drawSeahorse()
{
  if (seahorse.isActive)
  {

  }
}

//////// PIRATESHIP functions //////////////
////////////////////////////////////////////

void setPirateShip()
{
  pirateShip.x = 128;
  pirateShip.y = 10;
  pirateShip.HP = MAX_HP_PIRATESHIP;
  pirateShip.isActive = true;
  pirateShip.attackFase = 0;
  pirateShip.currentBullet = 0;
  pirateShip.isImune = false;
  pirateShip.isDying = false;
  pirateShip.isDead = false;
  pirateShip.imuneTimer = 0;
  bossSlow = false;
  faseTimer = 0;
}

void shootingSkull()
{
  enemy[pirateShip.currentBullet].frame = 0;
  enemy[pirateShip.currentBullet].isActive = true;
  enemy[pirateShip.currentBullet].isDying = false;
  enemy[pirateShip.currentBullet].type = ENEMY_SKULL;
  enemy[pirateShip.currentBullet].x = pirateShip.x + 16;
  enemy[pirateShip.currentBullet].y = pirateShip.y + 20;
  enemy[pirateShip.currentBullet].HP = MAX_HP_SKULL;
  pirateShip.currentBullet++;
}


void checkPirateShip()
{
  if (pirateShip.isActive)
  {
    if (pirateShip.currentBullet > MAX_BOSS_BULLETS) pirateShip.currentBullet = 0;
    for (byte i = 0; i < MAX_ONSCREEN_ENEMIES; i++)
    {
      if (!enemy[i].isDying) enemy[i].x -= 2;
    }
  }
}


void pirateShipSailsRightOnScreen()
{
  if (pirateShip.x > 64)pirateShip.x--;
  else pirateShip.attackFase++;
}

void pirateShipWait()
{
  if (arduboy.everyXFrames(4)) faseTimer++;
  if (faseTimer > 16)
  {
    pirateShip.attackFase++;
    faseTimer = 0;
  }
}

void pirateShipGoesUpAndShoots()
{
  if (pirateShip.y > -20)
  {
    if (arduboy.everyXFrames(22)) shootingSkull();
    pirateShip.y -= 2;
  }
  else pirateShip.attackFase++;

}

void pirateShipGoesDownAndShoots()
{
  if (pirateShip.y < 40)
  {
    if (arduboy.everyXFrames(22)) shootingSkull();
    pirateShip.y += 2;
  }
  else pirateShip.attackFase++;
}

void pirateShipGoesToMiddle()
{
  if (pirateShip.y > 11)pirateShip.y -= 2;
  else pirateShip.attackFase++;
}


void pirateShipRestart()
{
  pirateShip.attackFase = 0;
}

void pirateShipGoesUpForAttack()
{
  if (pirateShip.y > -11)pirateShip.y -= 2;
  else pirateShip.attackFase++;
}

void pirateShipBacksUp()
{
  if (pirateShip.x < 71)pirateShip.x++;
  else pirateShip.attackFase++;
}

void pirateShipLaunches()
{
  if (pirateShip.x > -21)pirateShip.x -= 10;
  else pirateShip.attackFase++;
}

void pirateShipTrembles()
{
  pirateShip.x =  pirateShip.x + (2 * (1 - (2 * bossSlow)));
  bossSlow = !bossSlow;
  pirateShip.attackFase++;
}


typedef void (*FunctionPointer) ();
const FunctionPointer PROGMEM pirateShipAttackFases[] =
{
  pirateShipSailsRightOnScreen,
  pirateShipWait,
  pirateShipGoesUpAndShoots,
  pirateShipGoesDownAndShoots,
  pirateShipGoesUpAndShoots,
  pirateShipGoesDownAndShoots,
  pirateShipGoesUpAndShoots,
  pirateShipGoesDownAndShoots,
  pirateShipGoesToMiddle,
  pirateShipWait,
  pirateShipGoesUpForAttack,
  pirateShipBacksUp,
  pirateShipLaunches,
  pirateShipTrembles,
  pirateShipTrembles,
  pirateShipTrembles,
  pirateShipTrembles,
  pirateShipTrembles,
  pirateShipTrembles,
  pirateShipBacksUp,
  pirateShipRestart,
};


void drawPirateShip()
{
  if (pirateShip.isActive)
  {
    sprites.drawSelfMasked(pirateShip.x + 16, pirateShip.y + 20, pirateshipShip, 0);
    sprites.drawSelfMasked(pirateShip.x + 24, pirateShip.y + 5, pirateshipSail, 0);
    sprites.drawSelfMasked(pirateShip.x, pirateShip.y + 19, pirateshipBowsprit, 0);
    sprites.drawSelfMasked(pirateShip.x + 36, pirateShip.y, pirateshipCrowsnest, 0);
    drawEnemyHud(pirateShip.HP, MAX_HP_PIRATESHIP);
  }
}




#endif
