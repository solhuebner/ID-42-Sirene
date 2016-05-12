#ifndef PLAYER_H
#define PLAYER_H

#include <Arduino.h>
#include "globals.h"

#define MAX_ONSCREEN_TRIDENT         3
#define MAX_ONSCREEN_BUBBLES         3
#define MAX_ONSCREEN_SEASHELL        6
#define MAX_ONSCREEN_MAGIC           1
#define MAX_ONSCREEN_SPARKLES        8

int seaShellSpeedY[] = {0, 1, -1, 0, 1, -1,};
boolean magicCharging = false;
byte magicFrame = 0;
byte chargeBarFrame = 0;
boolean bubblesFrame = false;

byte currentBullets[] = {0, 0, 0, 0};
byte maxBullets[] = {MAX_ONSCREEN_TRIDENT, MAX_ONSCREEN_BUBBLES, MAX_ONSCREEN_SEASHELL, MAX_ONSCREEN_MAGIC};
byte coolDown[] = { WEAPON_COOLDOWN_TRIDENT, WEAPON_COOLDOWN_BUBBLES, WEAPON_COOLDOWN_SEASHELL, WEAPON_COOLDOWN_MAGIC};
byte coolDownMax[] = { WEAPON_COOLDOWN_TRIDENT, WEAPON_COOLDOWN_BUBBLES, WEAPON_COOLDOWN_SEASHELL, WEAPON_COOLDOWN_MAGIC};


struct Players
{
  public:
    byte x;
    byte y;
    byte weaponType;
    boolean isActive;
    boolean isImune;
    byte imuneTimer;
    byte HP;
    byte frame;
};

struct Weapons
{
  public:
    byte x;
    int y;
    byte damage;
    byte speedX;
    boolean isActive = false;
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

Players mermaid;
Weapons trident[MAX_ONSCREEN_TRIDENT];
Weapons bubbles[MAX_ONSCREEN_BUBBLES];
Weapons seaShell[MAX_ONSCREEN_SEASHELL];
Weapons magic[MAX_ONSCREEN_MAGIC];
Sparkles sparkle[MAX_ONSCREEN_SPARKLES];

void rotateBullets()
{
  currentBullets[mermaid.weaponType]++;
  if (currentBullets[mermaid.weaponType] > (maxBullets[mermaid.weaponType] - 1)) currentBullets[mermaid.weaponType] = 0;
}

void shootTrident()
{
  if (!trident[currentBullets[WEAPON_TYPE_TRIDENT]].isActive)
  {
    trident[currentBullets[WEAPON_TYPE_TRIDENT]].isActive = true;
    trident[currentBullets[WEAPON_TYPE_TRIDENT]].x = mermaid.x + 8;
    trident[currentBullets[WEAPON_TYPE_TRIDENT]].y = mermaid.y + 6;
  }
  rotateBullets();
}

void shootBubbles()
{
  if (!bubbles[currentBullets[WEAPON_TYPE_BUBBLES]].isActive)
  {
    bubbles[currentBullets[WEAPON_TYPE_BUBBLES]].isActive = true;
    bubbles[currentBullets[WEAPON_TYPE_BUBBLES]].x = mermaid.x + 8;
    bubbles[currentBullets[WEAPON_TYPE_BUBBLES]].y = mermaid.y + 6;
  }
  rotateBullets();
}

void shootSeaShell()
{
  for (byte i = 0; i < 3; i++)
  {
    if (!seaShell[currentBullets[WEAPON_TYPE_SEASHELL]].isActive)
    {
      seaShell[currentBullets[WEAPON_TYPE_SEASHELL]].isActive = true;
      seaShell[currentBullets[WEAPON_TYPE_SEASHELL]].x = mermaid.x + 8;
      seaShell[currentBullets[WEAPON_TYPE_SEASHELL]].y = mermaid.y + 6;
    }
    rotateBullets();
  }
}

void shootMagic()
{
  if (!magic[0].isActive)
  {
    magic[0].isActive = true;
    magic[0].x = mermaid.x + 8;
    magic[0].y = mermaid.y + 6;
    chargeBarFrame = 0;
  }
}

typedef void (*FunctionPointer) ();

FunctionPointer shootWeapon[] = {
  shootTrident,
  shootBubbles,
  shootSeaShell,
  shootMagic,
};


void setWeapons()
{
  for (byte i = 0; i < 3; i++)
  {
    trident[i].speedX = 2;
    trident[i].damage = 2;
    bubbles[i].speedX = 3;
    bubbles[i].damage = 1;
    seaShell[i].speedX = 2;
    seaShell[i].damage = 1;
    seaShell[i + 3].speedX = 2;
    seaShell[i + 3].damage = 1;
  }
  magic[0].speedX = 3;
  magic[0].damage = 1;

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
  for (byte i = 0; i < 3; i++)
  {
    if (trident[i].isActive) trident[i].x += trident[i].speedX;
    if (trident[i].x > 128)
    {
      trident[i].x = 0;
      trident[i].isActive = false;
    }
  }

  if (arduboy.everyXFrames(3)) bubblesFrame = !bubblesFrame;
  for (byte i = 0; i < 3; i++)
  {
    if (bubbles[i].isActive) bubbles[i].x += bubbles[i].speedX;
    if (bubbles[i].x > 128)
    {
      bubbles[i].x = 0;
      bubbles[i].isActive = false;
    }
  }
  for (byte i = 0; i < 6; i++)
  {
    if (seaShell[i].isActive)
    {
      seaShell[i].x += seaShell[i].speedX;
      seaShell[i].y += seaShellSpeedY[i];
    }
    if (seaShell[i].x > 128 || seaShell[i].y + 8 < 1 || seaShell[i].y > 64)
    {
      seaShell[i].x = 0;
      seaShell[i].y = 0;
      seaShell[i].isActive = false;
    }
  }
  if (magic[0].isActive) magic[0].x += magic[0].speedX;
  if (magic[0].x > 128)
  {
    magic[0].x = 0;
    magic[0].isActive = false;
  }
  if (arduboy.everyXFrames(2)) magicFrame++;
  if (magicFrame > 3) magicFrame = 0;
}

void checkMermaid()
{
  if (mermaid.isImune)
  {
    if (arduboy.everyXFrames(3)) mermaid.isActive = !mermaid.isActive;
    mermaid.imuneTimer++;
    if (mermaid.imuneTimer > 60)
    {
      mermaid.imuneTimer = 0;
      mermaid.isImune = false;
      mermaid.isActive = true;
    }
  }
  if (mermaid.HP < 2) gameState = STATE_GAME_OVER;
  if (arduboy.everyXFrames(10)) mermaid.frame++;
  if (mermaid.frame > 5 ) mermaid.frame = 0;
  if (arduboy.everyXFrames(5))
  {
    for (byte i = 0; i < 8; i++)
    {
      sparkle[i].frame++;
      if (sparkle[i].frame > 7 ) sparkle[i].frame = 0;
    }
  }
}

void setMermaid()
{
  mermaid.x = 0;
  mermaid.y = 20;
  mermaid.weaponType = WEAPON_TYPE_TRIDENT;
  mermaid.isActive = true;
  mermaid.HP = 4;
  mermaid.isImune = true;
  mermaid.imuneTimer = 0;
}

void drawWeapons()
{
  for (byte i = 0; i < 3; i++)
  {
    if (trident[i].isActive) sprites.drawPlusMask(trident[i].x, trident[i].y, trident_plus_mask, 0);
    if (bubbles[i].isActive) sprites.drawPlusMask(bubbles[i].x, bubbles[i].y, bubbles_plus_mask, bubblesFrame);
    if (seaShell[i].isActive) sprites.drawPlusMask(seaShell[i].x, seaShell[i].y, seaShell_plus_mask, i);
    if (seaShell[i + 3].isActive) sprites.drawPlusMask(seaShell[i + 3].x, seaShell[i + 3].y, seaShell_plus_mask, i);
  }
  if (magic[0].isActive) sprites.drawPlusMask(magic[0].x, magic[0].y, magic_plus_mask, magicFrame);
}


void drawMermaid()
{
  if (mermaid.isActive) sprites.drawPlusMask(mermaid.x, mermaid.y, mermaid_plus_mask, mermaid.frame);
  if (magicCharging)
  {
    for (byte i = 0; i < 8; i++) sprites.drawSelfMasked(mermaid.x + sparkle[i].x + (sparkle[i].speedX * sparkle[i].frame), mermaid.y + sparkle[i].y + (sparkle[i].speedY * sparkle[i].frame), chargeSparkles, sparkle[i].frame);
    sprites.drawPlusMask(mermaid.x, mermaid.y, chargeBar_plus_mask, chargeBarFrame);
  }
}

void drawLifeHUD()
{
  sprites.drawPlusMask(0, 0, hearts_plus_mask, mermaid.HP - 2);
}

void drawScoreHUD()
{
  char buf[10];
  scorePlayer = arduboy.cpuLoad();
  ltoa(scorePlayer, buf, 10);
  char charLen = strlen(buf);
  char pad = 7 - charLen;

  //draw 0 padding
  for (byte i = 0; i < pad; i++)
  {
    sprites.drawPlusMask(93 + (5 * i), 0, numbers_plus_mask, 0);
  }

  for (byte i = 0; i < charLen; i++)
  {
    char digit = buf[i];
    byte j;
    if (digit <= 48)
    {
      digit = 0;
    }
    else {
      digit -= 48;
      if (digit > 9) digit = 0;
    }

    for (byte z = 0; z < 10; z++)
    {
      if (digit == z) j = z;
    }
    sprites.drawPlusMask(93 + (pad * 5) + (5 * i), 0, numbers_plus_mask, digit);
  }
}

#endif
