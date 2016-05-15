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
  setWeapons();
  setEnemies();
  setMermaid();
  gameState = STATE_GAME_NEXT_LEVEL;
};


void stateGameNextLevel()
{
  currentWave = 0;
  previousWave = 255;
  waveTimer = 0;
  level++;
  shark.isActive = false;
  seahorse.isActive = false;
  pirateShip.isActive = false;
  gameState = STATE_GAME_PLAYING;
};


void stateGamePlaying()
{
  checkInputs();
  checkWeapons();
  checkMermaid();
  checkEnemies();
  checkShark();
  checkPirateShip();

  if (arduboy.everyXFrames(2)) ((FunctionPointer) pgm_read_word (&Levels[level - 1][currentWave]))();
  if (checkEndLevel()) gameState = STATE_GAME_NEXT_LEVEL;

  drawEnemies();
  drawShark();
  drawSeahorse();
  drawPirateShip();
  drawMermaid();
  drawWeapons();
  drawLifeHUD();
  drawScoreHUD();

  checkCollisions();
};

void stateGamePause()
{
  if (buttons.justPressed(A_BUTTON)) gameState = STATE_GAME_PLAYING;
};

void stateGameOver()
{
  gameState = STATE_MENU_MAIN;
};





#endif
