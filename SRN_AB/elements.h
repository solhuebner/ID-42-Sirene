#ifndef ELEMENTS_H
#define ELEMENTS_H

#include <Arduino.h>
#include "globals.h"

struct Background
{
  public:
    int x;
};

Background Column[3];

void setBackground()
{
  backgroundIsVisible = true;
  Column[0].x = 28;
  Column[1].x = 92;
  Column[3].x = 128;
}

void checkBackground()
{
  if (arduboy.everyXFrames(10))
  {
    Column[0].x--;
    Column[1].x--;
  }
  if (arduboy.everyXFrames(3)) Column[2].x--;

  if (Column[0].x < -8) Column[0].x = 128;
  if (Column[1].x < -8) Column[1].x = 128;
  if (Column[2].x < -16) Column[2].x = 128;
}

void drawBackground()
{
  if (backgroundIsVisible)
  {
    for (byte z = 0; z < 2; z++)
    {
      for (byte i = 0; i < 3; i++)
      {
        sprites.drawSelfMasked(28 + (z * 15) + (8 * i), (8 * i), sunRay, i);
      }
    }
    sprites.drawPlusMask(Column[0].x, 20, columnSmall_plus_mask, 0);
    sprites.drawPlusMask(Column[1].x, 20, columnSmall_plus_mask, 0);
    sprites.drawPlusMask(Column[2].x, 18, columnBig_plus_mask, 0);
    sprites.drawPlusMask(Column[2].x + 8, 18, columnSmall_plus_mask, 0);
  }
}


#endif
