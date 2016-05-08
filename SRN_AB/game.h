#ifndef GAME_H
#define GAME_H

#include <Arduino.h>
#include "globals.h"
#include "inputs.h"
#include "player.h"
#include "enemies.h"
#include "elements.h"
#include "levels.h"



void stateGamePrepareLevel()
{
  level = 0;
  scorePlayer = 0;
  mermaid.life = 3;
  setWeapons();
  setEnemies();
  gameState = STATE_GAME_NEXT_LEVEL;
};


void stateGameNextLevel()
{
  gameState = STATE_GAME_PLAYING;
  currentWave = 0;
  previousWave = 255;
  level++;
};


void stateGamePlaying()
{
  checkInputs();
  checkWeapons();
  checkMermaid();
  checkEnemies();
  checkBosses();
  if (arduboy.everyXFrames(2))Levels[level-1][currentWave]();
  if (checkEndLevel()) gameState = STATE_GAME_NEXT_LEVEL;
  drawBosses();
  drawEnemies();
  drawPlayer();
  drawWeapons();
  drawLifeHUD();
  drawScoreHUD();
  
};

void stateGamePause()
{
  if (buttons.justPressed(A_BUTTON)) gameState = STATE_GAME_PLAYING;
};

void stateGameOver()
{

};





#endif
