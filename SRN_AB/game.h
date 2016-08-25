#ifndef GAME_H
#define GAME_H

#include <Arduino.h>
#include "globals.h"
#include "inputs.h"
#include "player.h"
#include "enemies.h"
#include "elements.h"
#include "levels.h"

boolean objectVisible;

void stateMenuPlay()
{
  level = LEVEL_TO_START_WITH - 1;
  scorePlayer = 0;
  setWeapons();
  setEnemies();
  setMermaid();
  setBosses();
  gameOverAndStageFase = 0;
  globalCounter = 0;
  leftX = -32;
  rightX = 148;
  gameState = STATE_GAME_NEXT_LEVEL;
};

void start()
{
  if (gameState == STATE_GAME_OVER) objectVisible = false;
  else objectVisible = true;
  gameOverAndStageFase++;
}

void slideToMiddle()
{
  byte amount;
  if (gameState == STATE_GAME_NEXT_LEVEL) amount = 39;
  else amount = 31;
  if (leftX < amount)
  {
    leftX += 4;
    rightX -= 4;
  }
  else gameOverAndStageFase++;
}

void slideOpen()
{
  byte amount;
  if (gameState == STATE_GAME_NEXT_LEVEL) amount = 39;
  else amount = 31;
  if (leftX > amount)
  {
    leftX -= 4;
    rightX += 4;
  }
  else gameOverAndStageFase++;
}

void nextLevelFlicker()
{
  objectVisible = !objectVisible;
  wait();
}


void nextLevelEnd()
{
  gameState = STATE_GAME_PLAYING;
  gameOverAndStageFase = 0;
  level++;
  leftX = -32;
  rightX = 148;
  mermaid.isImune = true;
  mermaid.isSuper = false;
  objectVisible = false;
  setBackground();
}

typedef void (*FunctionPointer) ();
const FunctionPointer PROGMEM nextLevelFases[] =
{
  start,
  wait,
  slideToMiddle,
  slideOpen,
  slideToMiddle,
  wait,
  nextLevelFlicker,
  nextLevelEnd,
};


void stateGameNextLevel()
{
  checkMermaid();
  drawMermaid();
  currentWave = 0;
  previousWave = 255;
  bitClear(endBoss.characteristics,4);
  if (objectVisible)
  {
    sprites.drawSelfMasked(leftX, 28, textStage, 0);
    sprites.drawSelfMasked(rightX, 28, numbersBig, level + 1);
  }
  ((FunctionPointer) pgm_read_word (&nextLevelFases[gameOverAndStageFase]))();
};


void stateGamePlaying()
{
  checkCollisions();
  checkInputs();
  checkWeapons();
  checkMermaid();
  checkEnemyBullet();
  checkEnemies();
  checkEndBoss();
  checkBackground();
  checkPowerUP();

  if (arduboy.everyXFrames(2)) ((FunctionPointer) pgm_read_word (&Levels[level - 1][currentWave]))();

  drawBackground();
  drawPowerUP();
  
  //drawBosses();
  drawEnemies();
  drawEnemyBullet();
  drawMermaid();
  drawWeapons();
  drawLifeHUD();
  drawScore(SCORE_SMALL_FONT);
};

void stateGamePause()
{
  sprites.drawSelfMasked(47, 24, textPause, 0);
  if (arduboy.justPressed(A_BUTTON)) gameState = STATE_GAME_PLAYING;
};

void gameOverShowHighScore()
{
  objectVisible = true;
  gameOverAndStageFase++;
}


void gameOverEnd()
{
  if (arduboy.justPressed(A_BUTTON | B_BUTTON))
  {
    gameState = STATE_MENU_MAIN;
    gameOverAndStageFase = 0;
  }
}

typedef void (*FunctionPointer) ();
const FunctionPointer PROGMEM gameOverFases[] =
{
  start,
  slideToMiddle,
  slideOpen,
  slideToMiddle,
  wait,
  gameOverShowHighScore,
  wait,
  gameOverEnd,
};


void stateGameOver()
{
  ((FunctionPointer) pgm_read_word (&gameOverFases[gameOverAndStageFase]))();
  sprites.drawSelfMasked(leftX, 16, textGame, 0);
  sprites.drawSelfMasked(rightX, 16, textOver, 0);
  if (objectVisible) {
    sprites.drawSelfMasked(35, 28, textHighscore, 0);
    drawScore(SCORE_BIG_FONT);
  }
};

typedef void (*FunctionPointer) ();
const FunctionPointer PROGMEM gameEndFases[] =
{
  start,
  wait,
  wait,
  gameOverEnd,
};

void stateGameEnded()
{
  ((FunctionPointer) pgm_read_word (&gameEndFases[gameOverAndStageFase]))();
  if (objectVisible) {
    checkMermaid();
    checkBackground();
    drawBackground();
    drawMermaid();
    sprites.drawSelfMasked(35, 28, textHighscore, 0);
    drawScore(SCORE_BIG_FONT);
  }
}



#endif
