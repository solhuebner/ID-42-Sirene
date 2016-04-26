#ifndef PLAYER_H
#define PLAYER_H

#include <Arduino.h>
#include "globals.h"

byte mermaidFrame = 0;
byte currentBullets[] = {0, 0, 0, 0};
byte maxBullets[] = {1, 2, 5, 0};
int ySpeed[] = {0, 1, -1, 0, 1, -1,};
byte magicFrame = 0;

struct Players
{
  public:
    byte x;
    byte y;
    byte weaponType;
};

struct Weapons
{
  public:
    byte x;
    byte y;
    byte damage;
    byte xSpeed;
    byte frame = 0;
    boolean isActive = false;
};

Players mermaid = { .x = 20, .y = 20, .weaponType = WEAPON_TYPE_TRIDENT};
Weapons trident[2];
Weapons bubbles[3];
Weapons seaShell[6];
Weapons magic[1];



void shootTrident()
{
  currentBullets[WEAPON_TYPE_TRIDENT]++;
  if (currentBullets[WEAPON_TYPE_TRIDENT] > maxBullets[WEAPON_TYPE_TRIDENT]) currentBullets[WEAPON_TYPE_TRIDENT] = 0;
  if (!trident[currentBullets[WEAPON_TYPE_TRIDENT]].isActive)
  {
    trident[currentBullets[WEAPON_TYPE_TRIDENT]].isActive = true;
    trident[currentBullets[WEAPON_TYPE_TRIDENT]].x = mermaid.x + 8;
    trident[currentBullets[WEAPON_TYPE_TRIDENT]].y = mermaid.y + 6;
  }
}

void shootBubbles()
{
  currentBullets[WEAPON_TYPE_BUBBLES]++;
  if (currentBullets[WEAPON_TYPE_BUBBLES] > maxBullets[WEAPON_TYPE_BUBBLES]) currentBullets[WEAPON_TYPE_BUBBLES] = 0;
  if (!bubbles[currentBullets[WEAPON_TYPE_BUBBLES]].isActive)
  {
    bubbles[currentBullets[WEAPON_TYPE_BUBBLES]].isActive = true;
    bubbles[currentBullets[WEAPON_TYPE_BUBBLES]].x = mermaid.x + 8;
    bubbles[currentBullets[WEAPON_TYPE_BUBBLES]].y = mermaid.y + 6;
  }
}

void shootSeaShell()
{
  for (byte i = 0; i < 3; i++)
  {
    currentBullets[WEAPON_TYPE_SEASHELL]++;
    if (currentBullets[WEAPON_TYPE_SEASHELL] > maxBullets[WEAPON_TYPE_SEASHELL]) currentBullets[WEAPON_TYPE_SEASHELL] = 0;
    if (!seaShell[currentBullets[WEAPON_TYPE_SEASHELL]].isActive)
    {
      seaShell[currentBullets[WEAPON_TYPE_SEASHELL]].isActive = true;
      seaShell[currentBullets[WEAPON_TYPE_SEASHELL]].x = mermaid.x + 8;
      seaShell[currentBullets[WEAPON_TYPE_SEASHELL]].y = mermaid.y + 6;
    }
  }
}

void shootMagic()
{
  if (!magic[currentBullets[WEAPON_TYPE_MAGIC]].isActive)
  {
    magic[currentBullets[WEAPON_TYPE_MAGIC]].isActive = true;
    magic[currentBullets[WEAPON_TYPE_MAGIC]].x = mermaid.x + 8;
    magic[currentBullets[WEAPON_TYPE_MAGIC]].y = mermaid.y + 6;
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
  for (byte i = 0; i < 2; i++)
  {
    trident[i].xSpeed = 2;
    trident[i].damage = 2;
  }
  for (byte i = 0; i < 3; i++)
  {
    bubbles[i].xSpeed = 3;
    bubbles[i].damage = 1;
  }
  for (byte i = 0; i < 6; i++)
  {
    seaShell[i].xSpeed = 2;
    seaShell[i].damage = 1;
  }

  for (byte i = 0; i < 1; i++)
  {
    magic[i].xSpeed = 1;
    magic[i].damage = 1;
  }
}

void checkWeapons()
{
  for (byte i = 0; i < 2; i++)
  {
    if (trident[i].isActive) trident[i].x += trident[i].xSpeed;
    if (trident[i].x > 128)
    {
      trident[i].x = 0;
      trident[i].isActive = false;
    }
  }
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
    if (seaShell[i].x > 128 || seaShell[i].y < 1 || seaShell[i].y > 64)
    {
      seaShell[i].x = 0;
      seaShell[i].y = 0;
      seaShell[i].isActive = false;
    }
  }


  if (magic[0].isActive) magic[0].x += magic[0].xSpeed;
  if (magic[0].x > 128)
  {
    magic[0].x = 0;
    magic[0].isActive = false;
  }
  if (arduboy.everyXFrames(3)) magicFrame++;
  if (magicFrame > 3) magicFrame = 0;
}

void checkMermaid()
{
  if (arduboy.everyXFrames(10)) mermaidFrame++;
  if (mermaidFrame > 5 ) mermaidFrame = 0;
}

void drawWeapons()
{
  for (byte i = 0; i < 2; i++)
  {
    if (trident[i].isActive) sprites.drawPlusMask(trident[i].x, trident[i].y, trident_plus_mask, 0);
  }
  for (byte i = 0; i < 3; i++)
  {
    if (bubbles[i].isActive) sprites.drawPlusMask(bubbles[i].x, bubbles[i].y, bubbles2_plus_mask, 0);
  }
  for (byte i = 0; i < 3; i++)
  {
    if (seaShell[i].isActive) sprites.drawPlusMask(seaShell[i].x, seaShell[i].y, seaShell_plus_mask, i);
  }
  for (byte i = 3; i < 6; i++)
  {
    if (seaShell[i].isActive) sprites.drawPlusMask(seaShell[i].x, seaShell[i].y, seaShell_plus_mask, i - 3);
  }
  for (byte i = 0; i < 1; i++)
  {
    if (magic[i].isActive) sprites.drawPlusMask(magic[i].x, magic[i].y, magic_plus_mask, magicFrame);
    if (magic[i].isActive) sprites.drawPlusMask(magic[i].x-8, magic[i].y, magicTrail_plus_mask, 0);
  }
}

void drawPlayer()
{
  sprites.drawPlusMask(mermaid.x, mermaid.y, mermaid_plus_mask, mermaidFrame);
}

#endif
