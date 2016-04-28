#ifndef PLAYER_H
#define PLAYER_H

#include <Arduino.h>
#include "globals.h"

byte mermaidFrame = 0;
byte currentBullets[] = {0, 0, 0};
byte maxBullets[] = {2, 2, 5};
int ySpeed[] = {0, 1, -1, 0, 1, -1,};
byte magicFrame = 0;
boolean magicCharging = false;
byte chargeBarFrame = 0;
byte bubblesFrame = false;
byte coolDown[] = { WEAPON_COOLDOWN_TRIDENT, WEAPON_COOLDOWN_BUBBLES, WEAPON_COOLDOWN_SEASHELL, WEAPON_COOLDOWN_MAGIC};
byte coolDownMax[] = { WEAPON_COOLDOWN_TRIDENT, WEAPON_COOLDOWN_BUBBLES, WEAPON_COOLDOWN_SEASHELL, WEAPON_COOLDOWN_MAGIC};


struct Players
{
  public:
    byte x;
    byte y;
    byte weaponType;
    boolean isActive;
    byte life;
};

struct Weapons
{
  public:
    byte x;
    int y;
    byte damage;
    byte xSpeed;
    boolean isActive = false;
};

struct Sparkles
{
  public:
    int x;
    int y;
    int xSpeed;
    int ySpeed;
    byte frame;
};

Players mermaid = { .x = 20, .y = 20, .weaponType = WEAPON_TYPE_TRIDENT, .isActive = true, .life = 4};
Weapons trident[3];
Weapons bubbles[3];
Weapons seaShell[6];
Weapons magic;
Sparkles sparkle[8];

void rotateBullets()
{
  currentBullets[mermaid.weaponType]++;
  if (currentBullets[mermaid.weaponType] > maxBullets[mermaid.weaponType]) currentBullets[mermaid.weaponType] = 0;
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
  if (!magic.isActive)
  {
    magic.isActive = true;
    magic.x = mermaid.x + 8;
    magic.y = mermaid.y + 6;
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
    trident[i].xSpeed = 2;
    trident[i].damage = 2;
    bubbles[i].xSpeed = 3;
    bubbles[i].damage = 1;
    seaShell[i].xSpeed = 2;
    seaShell[i].damage = 1;
    seaShell[i + 3].xSpeed = 2;
    seaShell[i + 3].damage = 1;
  }
  magic.xSpeed = 3;
  magic.damage = 1;
  sparkle[0] = { .x = 18, .y = -6, .xSpeed = -2, .ySpeed = 3, .frame = 0};
  sparkle[1] = { .x = -6, .y = 6, .xSpeed = 2, .ySpeed = 0, .frame = 7};
  sparkle[2] = { .x = 18, .y = 18, .xSpeed = -2, .ySpeed = -3, .frame = 6};
  sparkle[3] = { .x = 8, .y = -7, .xSpeed = 0, .ySpeed = 2, .frame = 5};
  sparkle[4] = { .x = -5, .y = 18, .xSpeed = 2, .ySpeed = -3, .frame = 4};
  sparkle[5] = { .x = 19, .y = 6, .xSpeed = -2, .ySpeed = 0, .frame = 3};
  sparkle[6] = { .x = -5, .y = -6, .xSpeed = 2, .ySpeed = 3, .frame = 2};
  sparkle[7] = { .x = 7, .y = 19, .xSpeed = 0, .ySpeed = -2, .frame = 1};

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
    if (trident[i].isActive) trident[i].x += trident[i].xSpeed;
    if (trident[i].x > 128)
    {
      trident[i].x = 0;
      trident[i].isActive = false;
    }
  }

  if (arduboy.everyXFrames(3)) bubblesFrame = !bubblesFrame;
  for (byte i = 0; i < 3; i++)
  {
    if (bubbles[i].isActive) bubbles[i].x += bubbles[i].xSpeed;
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
      seaShell[i].x += seaShell[i].xSpeed;
      seaShell[i].y += ySpeed[i];
    }
    if (seaShell[i].x > 128 || seaShell[i].y + 8 < 1 || seaShell[i].y > 64)
    {
      seaShell[i].x = 0;
      seaShell[i].y = 0;
      seaShell[i].isActive = false;
    }
  }
  if (magic.isActive) magic.x += magic.xSpeed;
  if (magic.x > 128)
  {
    magic.x = 0;
    magic.isActive = false;
  }
  if (arduboy.everyXFrames(2)) magicFrame++;
  if (magicFrame > 3) magicFrame = 0;
}

void checkMermaid()
{
  if (arduboy.everyXFrames(10)) mermaidFrame++;
  if (mermaidFrame > 5 ) mermaidFrame = 0;
  for (byte i = 0; i < 8; i++)
  {
    if (arduboy.everyXFrames(5)) sparkle[i].frame++;
    if (sparkle[i].frame > 7 ) sparkle[i].frame = 0;
  }
}

void drawWeapons()
{
  for (byte i = 0; i < 3; i++)
  {
    if (trident[i].isActive) sprites.drawPlusMask(trident[i].x, trident[i].y, trident_plus_mask, 0);
    if (bubbles[i].isActive) sprites.drawPlusMask(bubbles[i].x, bubbles[i].y, bubbles_plus_mask, bubblesFrame);
    if (seaShell[i].isActive) sprites.drawPlusMask(seaShell[i].x, seaShell[i].y, seaShell_plus_mask, i);
    if (seaShell[i + 3].isActive) sprites.drawPlusMask(seaShell[i + 3].x, seaShell[i + 3].y, seaShell_plus_mask, i);
    if (magic.isActive) sprites.drawPlusMask(magic.x, magic.y, magic_plus_mask, magicFrame);
  }
}

void drawPlayer()
{
  if (mermaid.isActive) sprites.drawPlusMask(mermaid.x, mermaid.y, mermaid_plus_mask, mermaidFrame);
  if (magicCharging)
  {
    for (byte i = 0; i < 8; i++) sprites.drawSelfMasked(mermaid.x + sparkle[i].x + (sparkle[i].xSpeed * sparkle[i].frame), mermaid.y + sparkle[i].y + (sparkle[i].ySpeed * sparkle[i].frame), chargeSparkles, sparkle[i].frame);
    sprites.drawPlusMask(mermaid.x, mermaid.y, chargeBar_plus_mask, chargeBarFrame);
  }
}

void drawLifeHUD()
{
  sprites.drawPlusMask(0, 0,hearts_plus_mask, mermaid.life-2);  
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
