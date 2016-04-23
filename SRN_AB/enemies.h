#ifndef ENEMIES_H
#define ENEMIES_H

#include <Arduino.h>
#include "globals.h"


void drawPirateShip()
{
  sprites.drawSelfMasked(21 + (22 * i), 60, menuText, i);
}


#endif
