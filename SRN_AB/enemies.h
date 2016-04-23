#ifndef ENEMIES_H
#define ENEMIES_H

#include <Arduino.h>
#include "globals.h"

struct EndBoss
{
  public:
    byte x;
    byte y;
    byte HP;
};

EndBoss pirateShip = { .x = 64, .y = 12, .HP = 0};

void drawPirateShip()
{
  sprites.drawSelfMasked(pirateShip.x+16, pirateShip.y+20, pirateshipShip, 0);
  sprites.drawSelfMasked(pirateShip.x+24, pirateShip.y+5, pirateshipSail, 0);
  sprites.drawSelfMasked(pirateShip.x, pirateShip.y+19, pirateshipBowsprit, 0);
  sprites.drawSelfMasked(pirateShip.x+36, pirateShip.y+0, pirateshipCrowsnest, 0);
}


#endif
