#ifndef PLAYER_H
#define PLAYER_H

#include <Arduino.h>
#include "globals.h"

#define WEAPON_TYPE_TRIDENT          0
#define WEAPON_TYPE_BUBBLES          1
#define WEAPON_TYPE_SEASHELL         2
#define WEAPON_TYPE_MAGIC            3

#define SEASHELL_GO_STRAIGHT         0
#define SEASHELL_GO_UP               1
#define SEASHELL_GO_DOWN             -1

#define WEAPON_COOLDOWN_TRIDENT      24
#define WEAPON_COOLDOWN_BUBBLES      16
#define WEAPON_COOLDOWN_SEASHELL     24
#define WEAPON_COOLDOWN_MAGIC        24

#define DAMAGE_TRIDENT               2
#define DAMAGE_BUBBLES               1
#define DAMAGE_SEASHELL              1
#define DAMAGE_MAGIC                 1  //charges up to 4

#define BULLET_SPEED_TRIDENT         2
#define BULLET_SPEED_BUBBLES         3
#define BULLET_SPEED_SEASHELL        2
#define BULLET_SPEED_MAGIC           3

#define MAX_ONSCREEN_BULLETS         8
#define MAX_ONSCREEN_SPARKLES        8

#define MERMAID_IMUNE_TIME           30
#define MERMAID_SUPER_TIME           250

#define MERMAID_COLLISION_OFFSET     4
#define MERMAID_COLLISION_SIZE       8

#define TRIDENT_COLLISION_OFFSET     6
#define BUBBLES_COLLISION_OFFSET     14
#define SEASHELL_COLLISION_OFFSET    0
#define MAGIC_COLLISION_OFFSET       8


int seaShellSpeedY[] = {SEASHELL_GO_STRAIGHT, SEASHELL_GO_UP, SEASHELL_GO_DOWN};
byte coolDown[] = { WEAPON_COOLDOWN_TRIDENT, WEAPON_COOLDOWN_BUBBLES, WEAPON_COOLDOWN_SEASHELL, WEAPON_COOLDOWN_MAGIC};
byte coolDownMax[] = { WEAPON_COOLDOWN_TRIDENT, WEAPON_COOLDOWN_BUBBLES, WEAPON_COOLDOWN_SEASHELL, WEAPON_COOLDOWN_MAGIC};
byte bulletSpeed[] = {BULLET_SPEED_TRIDENT, BULLET_SPEED_BUBBLES, BULLET_SPEED_SEASHELL, BULLET_SPEED_MAGIC};
byte bulletDamage[] = {DAMAGE_TRIDENT, DAMAGE_BUBBLES, DAMAGE_SEASHELL, DAMAGE_MAGIC};
byte bulletCollisionOffset[] = {TRIDENT_COLLISION_OFFSET, BUBBLES_COLLISION_OFFSET, SEASHELL_COLLISION_OFFSET, MAGIC_COLLISION_OFFSET};


//////// define player and weapons /////////
////////////////////////////////////////////

struct Players
{
  public:
    byte x;
    byte y;
    byte weaponType;
    boolean isVisible;
    boolean isImune;
    boolean isSuper;
    boolean magicCharging;
    byte imuneTimer;
    byte HP;
    byte frame;
    byte chargeBarFrame;
    byte currentBullet;
    byte currentSeaShell;
};

Players mermaid;

struct Bullets
{
  public:
    byte x;
    int y;
    byte damage;
    boolean isVisible = false;
    byte type;
    byte frame;
    int speedY;
};

struct Sparkles
{
  public:
    int x;
    int y;
    int speedX;
    int speedY;
    byte frame;
};


Bullets bullet[MAX_ONSCREEN_BULLETS];
Sparkles sparkle[MAX_ONSCREEN_SPARKLES];


//////// Player functions //////////////////
////////////////////////////////////////////

void setMermaid()
{
  mermaid.x = 0;
  mermaid.y = 20;
  mermaid.weaponType = WEAPON_TYPE_TRIDENT;
  mermaid.isVisible = true;
  mermaid.HP = 4;
  mermaid.imuneTimer = 0;
}


void checkMermaid()
{
  if (mermaid.isImune)
  {
    if (arduboy.everyXFrames(3))
    {
      mermaid.imuneTimer++;
      mermaid.isVisible = !mermaid.isVisible;
    }
    if (mermaid.imuneTimer > MERMAID_IMUNE_TIME)
    {
      mermaid.imuneTimer = 0;
      mermaid.isImune = false;
      mermaid.isVisible = true;
    }
  }

  if (mermaid.isSuper)
  {
    if (arduboy.everyXFrames(3)) 
    {
      mermaid.imuneTimer++;
      mermaid.isVisible = !mermaid.isVisible;
    }
    if (mermaid.imuneTimer > MERMAID_SUPER_TIME)
    {
      mermaid.imuneTimer = 0;
      mermaid.isSuper = false;
      mermaid.isVisible = true;
    }
  }

  if (mermaid.HP < 2)
  {
    rightX = 132;
    gameState = STATE_GAME_OVER;
  }
  if (arduboy.everyXFrames(10)) mermaid.frame++;
  if (mermaid.frame > 5 ) mermaid.frame = 0;
  if (arduboy.everyXFrames(5))
  {
    for (byte i = 0; i < MAX_ONSCREEN_SPARKLES; i++)
    {
      sparkle[i].frame++;
      if (sparkle[i].frame > 7 ) sparkle[i].frame = 0;
    }
  }
}


void drawMermaid()
{
  if (mermaid.isVisible) sprites.drawPlusMask(mermaid.x, mermaid.y, mermaid_plus_mask, mermaid.frame);
  if (mermaid.magicCharging)
  {
    for (byte i = 0; i < MAX_ONSCREEN_SPARKLES; i++)
    {
      sprites.drawSelfMasked(mermaid.x + sparkle[i].x + (sparkle[i].speedX * sparkle[i].frame), mermaid.y + sparkle[i].y + (sparkle[i].speedY * sparkle[i].frame), chargeSparkles, sparkle[i].frame);
    }
    sprites.drawPlusMask(mermaid.x, mermaid.y, chargeBar_plus_mask, mermaid.chargeBarFrame);
  }
}


//////// Weapon functions //////////////////
////////////////////////////////////////////

void setWeapons()
{
  mermaid.magicCharging = false;
  mermaid.chargeBarFrame = 0;
  mermaid.currentBullet = 0;
  mermaid.currentSeaShell = 0;
  for (byte i = 0; i < MAX_ONSCREEN_BULLETS; i++)
  {
    bullet[i].isVisible = false;
    bullet[i].frame = 0;
  }
  sparkle[0] = { .x = 18, .y = -6, .speedX = -2, .speedY = 3, .frame = 0};
  sparkle[1] = { .x = -6, .y = 6, .speedX = 2, .speedY = 0, .frame = 7};
  sparkle[2] = { .x = 18, .y = 18, .speedX = -2, .speedY = -3, .frame = 6};
  sparkle[3] = { .x = 8, .y = -7, .speedX = 0, .speedY = 2, .frame = 5};
  sparkle[4] = { .x = -5, .y = 18, .speedX = 2, .speedY = -3, .frame = 4};
  sparkle[5] = { .x = 19, .y = 6, .speedX = -2, .speedY = 0, .frame = 3};
  sparkle[6] = { .x = -5, .y = -6, .speedX = 2, .speedY = 3, .frame = 2};
  sparkle[7] = { .x = 7, .y = 19, .speedX = 0, .speedY = -2, .frame = 1};
}

void checkWeapons()
{
  if (coolDown[mermaid.weaponType] < coolDownMax[mermaid.weaponType])
  {
    coolDown[mermaid.weaponType]--;
    if (coolDown[mermaid.weaponType] < 1) coolDown[mermaid.weaponType] = coolDownMax[mermaid.weaponType];
  }
  for (byte i = 0; i < MAX_ONSCREEN_BULLETS; i++)
  {
    if (bullet[i].type == WEAPON_TYPE_BUBBLES && arduboy.everyXFrames(3)) bullet[i].frame = !bullet[i].frame;
    if (bullet[i].type == WEAPON_TYPE_MAGIC && arduboy.everyXFrames(2)) bullet[i].frame++;
    if (bullet[i].type == WEAPON_TYPE_MAGIC && bullet[i].frame > 3) bullet[i].frame = 0;

    bullet[i].x += bulletSpeed[bullet[i].type];
    if (bullet[i].type == WEAPON_TYPE_SEASHELL) bullet[i].y += bullet[i].speedY;
    if (bullet[i].x > 128 || bullet[i].y < -7 || bullet[i].y > 64)
    {
      bullet[i].isVisible = false;
    }
  }
}



void shootWeapon()
{
  arduboy.audio.tone(880, 20);
  if (!bullet[mermaid.currentBullet].isVisible)
  {
    if (bullet[mermaid.currentBullet].type != WEAPON_TYPE_SEASHELL)bullet[mermaid.currentBullet].frame = 0;
    bullet[mermaid.currentBullet].type = mermaid.weaponType;
    bullet[mermaid.currentBullet].isVisible = true;
    bullet[mermaid.currentBullet].x = mermaid.x + 8;
    bullet[mermaid.currentBullet].y = mermaid.y + 6;
    bullet[mermaid.currentBullet].damage = bulletDamage[bullet[mermaid.currentBullet].type];
    if (bullet[mermaid.currentBullet].type == WEAPON_TYPE_MAGIC) bullet[mermaid.currentBullet].damage += mermaid.chargeBarFrame;
    if (bullet[mermaid.currentBullet].type == WEAPON_TYPE_SEASHELL)
    {
      bullet[mermaid.currentBullet].speedY = seaShellSpeedY[mermaid.currentSeaShell];
      bullet[mermaid.currentBullet].frame = mermaid.currentSeaShell;
      mermaid.currentSeaShell++;
      if (mermaid.currentSeaShell > 2) mermaid.currentSeaShell = 0;
    }
    mermaid.chargeBarFrame = 0;
  }
  mermaid.currentBullet++;
  if (mermaid.currentBullet > MAX_ONSCREEN_BULLETS - 1) mermaid.currentBullet = 0;
}


void drawWeapons()
{
  for (byte i = 0; i < MAX_ONSCREEN_BULLETS; i++)
  {
    if (bullet[i].isVisible) sprites.drawSelfMasked(bullet[i].x, bullet[i].y, weapons[bullet[i].type], bullet[i].frame);
  }
}


#endif
