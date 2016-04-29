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
  level = 1;
  scorePlayer = 0;
  mermaid.life = 3;
  setWeapons();
  gameState = STATE_GAME_NEXT_LEVEL;
};


void stateGameNextLevel()
{
  gameState = STATE_GAME_PLAYING;
  currentWave = 0;
  previousWave = 255;
};


void stateGamePlaying()
{
  checkInputs();
  checkWeapons();
  checkMermaid();
  checkEnemies();
  checkBosses();
  updateLevel();
  Level01[currentWave]();
  drawBosses();
  drawEnemies();
  drawPlayer();
  drawWeapons();
  drawLifeHUD();
  drawScoreHUD();
  //Serial.println(sizeof(&Level01));
};

void stateGamePause()
{
  if (buttons.justPressed(A_BUTTON)) gameState = STATE_GAME_PLAYING;
};

void stateGameOver()
{

};





#endif
