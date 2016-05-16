#ifndef GAME_H
#define GAME_H

#include <Arduino.h>
#include "globals.h"
#include "inputs.h"
#include "player.h"
#include "enemies.h"
#include "elements.h"
#include "levels.h"

byte gameOverFase;
int gameX;
byte overX;
boolean highScoreVisible;
boolean scoreVisible;

void stateGamePrepareLevel()
{
  level = 0;
  scorePlayer = 0;
  setWeapons();
  setEnemies();
  setMermaid();
  setBosses();
  gameState = STATE_GAME_NEXT_LEVEL;
  gameOverFase = 0;
  gameX = -32;
  overX = 132;
  highScoreVisible = false;
  scoreVisible = false;
};


void stateGameNextLevel()
{
  currentWave = 0;
  previousWave = 255;
  waveTimer = 0;
  level++;
  shark.isVisible = false;
  seahorse.isVisible = false;
  pirateShip.isVisible = false;
  gameState = STATE_GAME_PLAYING;
};


void stateGamePlaying()
{
  checkCollisions();
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
  drawScoreHUD(93, 0);
};

void stateGamePause()
{
  if (buttons.justPressed(A_BUTTON)) gameState = STATE_GAME_PLAYING;
};


void gameOverWait()
{
  if (arduboy.everyXFrames(4)) waveTimer++;
  if (waveTimer > 8)
  {
    gameOverFase++;
    waveTimer = 0;
  }
}

void gameOverSlideToMiddle()
{
  if (gameX < 33)
  {
    gameX += 2;
    overX -= 2;
  }
  else gameOverFase++;
}

void gameOverSlideOpen()
{
  if (gameX > 33)
  {
    gameX -= 2;
    overX += 2;
  }
  else gameOverFase++;
}

void gameOverShowHighScore()
{
  highScoreVisible = true;
  gameOverFase++;
}

void gameOverShowScore()
{
  scoreVisible = true;
  gameOverFase++;
}

void gameOverEnd()
{
  if (buttons.justPressed(A_BUTTON | B_BUTTON)) gameState = STATE_MENU_MAIN;
}

typedef void (*FunctionPointer) ();
const FunctionPointer PROGMEM gameOverFases[] =
{
  gameOverSlideToMiddle,
  //gameOverSlideOpen,
  //gameOverSlideToMiddle,
  //gameOverSlideOpen,
  //gameOverSlideToMiddle,
  gameOverWait,
  gameOverShowHighScore,
  gameOverWait,
  gameOverShowScore,
  gameOverWait,
  gameOverEnd,
};




void stateGameOver()
{
  ((FunctionPointer) pgm_read_word (&gameOverFases[gameOverFase]))();
  sprites.drawSelfMasked(gameX, 20, game, 0);
  sprites.drawSelfMasked(overX, 20, over, 0);
  if (highScoreVisible)sprites.drawSelfMasked(35, 32, highscore, 0);
  if (scoreVisible) drawScoreHUD(51, 44);
};





#endif
