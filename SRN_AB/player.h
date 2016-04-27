#ifndef PLAYER_H
#define PLAYER_H

#include <Arduino.h>
#include "globals.h"

byte mermaidFrame = 0;
byte currentBullets[] = {0, 0, 0};
byte maxBullets[] = {2, 2, 5};
int ySpeed[] = {0, 1, -1, 0, 1, -1,};
byte magicFrame = 0;
byte magicCharge = 0;
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

Players mermaid = { .x = 20, .y = 20, .weaponType = WEAPON_TYPE_TRIDENT, .isActive = true};
Weapons trident[3];
Weapons bubbles[3];
Weapons seaShell[6];
Weapons magic;


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
}

#endif
