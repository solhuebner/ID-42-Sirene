#ifndef PLAYER_H
#define PLAYER_H

#include <Arduino.h>
#include "globals.h"

byte mermaidFrame = 0;
byte currentBullets[] = {0, 0, 0, 0};
byte maxBullets[] = {1, 2, 5, 0};

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
    byte speed;
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
  currentBullets[WEAPON_TYPE_SEASHELL]++;
  if (currentBullets[WEAPON_TYPE_SEASHELL] > maxBullets[WEAPON_TYPE_SEASHELL]) currentBullets[WEAPON_TYPE_SEASHELL] = 0;
  if (!seaShell[currentBullets[WEAPON_TYPE_SEASHELL]].isActive)
  {
    seaShell[currentBullets[WEAPON_TYPE_SEASHELL]].isActive = true;
    seaShell[currentBullets[WEAPON_TYPE_SEASHELL]].x = mermaid.x + 8;
    seaShell[currentBullets[WEAPON_TYPE_SEASHELL]].y = mermaid.y + 6;
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
    trident[i].speed = 2;
    trident[i].damage = 2;
  }
  for (byte i = 0; i < 3; i++)
  {
    bubbles[i].speed = 3;
    bubbles[i].damage = 1;
  }
  for (byte i = 0; i < 6; i++)
  {
    seaShell[i].speed = 2;
    seaShell[i].damage = 1;
  }
  for (byte i = 0; i < 1; i++)
  {
    magic[i].speed = 1;
    magic[i].damage = 1;
  }
}

void checkWeapons()
{
  for (byte i = 0; i < 2; i++)
  {
    if (trident[i].isActive) trident[i].x += trident[i].speed;
    if (trident[i].x > 128)
    {
      trident[i].x = 0;
      trident[i].isActive = false;
    }
  }
  for (byte i = 0; i < 3; i++)
  {
    if (bubbles[i].isActive) bubbles[i].x += bubbles[i].speed;
    if (bubbles[i].x > 128)
    {
      bubbles[i].x = 0;
      bubbles[i].isActive = false;
    }
  }
  for (byte i = 0; i < 6; i++)
  {
    if (seaShell[i].isActive) seaShell[i].x += seaShell[i].speed;
    if (seaShell[i].x > 128)
    {
      seaShell[i].x = 0;
      seaShell[i].isActive = false;
    }
  }
  for (byte i = 0; i < 1; i++)
  {
    if (magic[i].isActive) magic[i].x += magic[i].speed;
    if (magic[i].x > 128)
    {
      magic[i].x = 0;
      magic[i].isActive = false;
    }
  }
}

void drawWeapons()
{
  for (byte i = 0; i < 2; i++)
  {
    if (trident[i].isActive) sprites.drawPlusMask(trident[i].x, trident[i].y, trident_plus_mask, 0);
  }
  for (byte i = 0; i < 3; i++)
  {
    if (bubbles[i].isActive) sprites.drawPlusMask(bubbles[i].x, bubbles[i].y, bubbles_plus_mask, 0);
  }
  for (byte i = 0; i < 6; i++)
  {
    if (seaShell[i].isActive) sprites.drawPlusMask(seaShell[i].x, seaShell[i].y, seaShell_plus_mask, 0);
  }
  for (byte i = 0; i < 1; i++)
  {
    if (magic[i].isActive) sprites.drawPlusMask(magic[i].x, magic[i].y, magic_plus_mask, 0);
  }
}

void drawPlayer()
{
  if (arduboy.everyXFrames(10)) mermaidFrame++;
  if (mermaidFrame > 5 ) mermaidFrame = 0;
  sprites.drawPlusMask(mermaid.x, mermaid.y, mermaid_plus_mask, mermaidFrame);
}

#endif
