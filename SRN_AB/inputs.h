#ifndef INPUTS_H
#define INPUTS_H

#include <Arduino.h>
#include "globals.h"
#include "player.h"

void checkInputs()
{
  if (buttons.pressed(DOWN_BUTTON) && (mermaid.y < GAME_BOTTOM))
  {
    mermaid.y++;
  }
  if (buttons.pressed(LEFT_BUTTON) && (mermaid.x > GAME_LEFT))
  {
    mermaid.x--;
  }
  if (buttons.pressed(UP_BUTTON) && (mermaid.y > GAME_TOP))
  {
    mermaid.y--;
  }
  if (buttons.pressed(RIGHT_BUTTON) && (mermaid.x < GAME_RIGHT))
  {
    mermaid.x++;
  }

  if (buttons.justPressed(A_BUTTON))
  {
    mermaid.weaponType++;
    if (mermaid.weaponType > 3) mermaid.weaponType = 0;
  }
  if (buttons.justPressed(B_BUTTON) && (coolDown[mermaid.weaponType] == coolDownMax[mermaid.weaponType]))
  {
    coolDown[mermaid.weaponType]--;
    shootWeapon[mermaid.weaponType]();
  }
}


#endif
