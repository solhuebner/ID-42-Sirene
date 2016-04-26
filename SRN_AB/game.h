#ifndef GAME_H
#define GAME_H

#include <Arduino.h>
#include "globals.h"
#include "inputs.h"
#include "player.h"
#include "enemies.h"
#include "elements.h"


void stateGamePrepareLevel()
{
  level = 1;
  scorePlayer = 0;
  setWeapons();
  gameState = STATE_GAME_NEXT_LEVEL;
};


void stateGameNextLevel()
{
  gameState = STATE_GAME_PLAYING;
};


void stateGamePlaying()
{
  drawPirateShip();
  checkInputs();
  checkWeapons();
  drawPlayer();
  drawWeapons();
};

void stateGamePause()
{
  if (buttons.justPressed(A_BUTTON)) gameState = STATE_GAME_PLAYING;
};

void stateGameOver()
{
  
};



#endif
