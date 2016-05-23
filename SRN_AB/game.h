#ifndef GAME_H
#define GAME_H

#include <Arduino.h>
#include "globals.h"
#include "inputs.h"
#include "player.h"
#include "enemies.h"
#include "elements.h"
#include "levels.h"

byte gameOverAndStageFase;
boolean objectVisible;
byte upY;


void stateMenuPlay()
{
  level = FIRST_LEVEL;
  scorePlayer = 0;
  setWeapons();
  setEnemies();
  setMermaid();
  setBosses();
  gameOverAndStageFase = 0;
  globalCounter = 0;
  upY = 64;
  objectVisible = true;
  gameState = STATE_GAME_NEXT_LEVEL;
};

void nextLevelStart()
{
  leftX = -32;
  rightX = 148;
  gameOverAndStageFase++;
}

void nextLevelWait()
{
  if (arduboy.everyXFrames(4)) globalCounter++;
  if (globalCounter > 8)
  {
    gameOverAndStageFase++;
    globalCounter = 0;
  }
}

void nextLevelSlideToMiddle()
{
  if (leftX < 39)
  {
    leftX += 4;
    rightX -= 4;
  }
  else gameOverAndStageFase++;
}

void nextLevelSlideOpen()
{
  if (leftX > 39)
  {
    leftX -= 4;
    rightX += 4;
  }
  else gameOverAndStageFase++;
}

void nextLevelFlicker()
{
  objectVisible = !objectVisible;
  nextLevelWait();
}


void nextLevelEnd()
{
  gameState = STATE_GAME_PLAYING;
  gameOverAndStageFase = 0;
  level++;
  leftX = -32;
  rightX = 148;
  mermaid.isImune = true;
  objectVisible = false;
}

typedef void (*FunctionPointer) ();
const FunctionPointer PROGMEM nextLevelFases[] =
{
  nextLevelStart,
  nextLevelWait,
  nextLevelSlideToMiddle,
  nextLevelSlideOpen,
  nextLevelSlideToMiddle,
  nextLevelWait,
  nextLevelFlicker,
  nextLevelEnd,
};


void stateGameNextLevel()
{
  checkMermaid();
  drawMermaid();
  currentWave = 0;
  previousWave = 255;
  endBoss.isVisible = false;
  if (objectVisible)
  {
    sprites.drawSelfMasked(leftX, 28, stage, 0);
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
  checkEnemies();
  checkEndBoss();

  if (arduboy.everyXFrames(2)) ((FunctionPointer) pgm_read_word (&Levels[level - 1][currentWave]))();
  if (checkEndLevel()) gameState = STATE_GAME_NEXT_LEVEL;
  
  drawBosses();
  drawEnemies();
  drawMermaid();
  drawWeapons();
  drawLifeHUD();
  drawScore(93, 0, SCORE_SMALL_FONT);
};

void stateGamePause()
{
  if (arduboy.justPressed(A_BUTTON)) gameState = STATE_GAME_PLAYING;
};

void gameOverStart()
{
  leftX = -32;
  rightX = 132;
  gameOverAndStageFase++;
}

void gameOverWait()
{
  if (arduboy.everyXFrames(4)) globalCounter++;
  if (globalCounter > 8)
  {
    gameOverAndStageFase++;
    globalCounter = 0;
  }
}

void gameOverSlideToMiddle()
{
  if (leftX < 31)
  {
    leftX += 4;
    rightX -= 4;
  }
  else gameOverAndStageFase++;
}

void gameOverSlideOpen()
{
  if (leftX > 31)
  {
    leftX -= 4;
    rightX += 4;
  }
  else gameOverAndStageFase++;
}

void gameOverShowHighScore()
{
  objectVisible = true;
  gameOverAndStageFase++;
}

void gameOverScoreSlideUp()
{
  if (upY > 41)
  {
    upY -= 4;
  }
  else gameOverAndStageFase++;
}

void gameOverScoreSlideDown()
{
  if (upY < 41)
  {
    upY += 4;
  }
  else gameOverAndStageFase++;
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
  gameOverStart,
  gameOverSlideToMiddle,
  gameOverSlideOpen,
  gameOverSlideToMiddle,
  gameOverWait,
  gameOverShowHighScore,
  gameOverWait,
  gameOverScoreSlideUp,
  gameOverScoreSlideDown,
  gameOverScoreSlideUp,
  gameOverWait,
  gameOverEnd,
};


void stateGameOver()
{
  ((FunctionPointer) pgm_read_word (&gameOverFases[gameOverAndStageFase]))();
  sprites.drawSelfMasked(leftX, 16, game, 0);
  sprites.drawSelfMasked(rightX, 16, over, 0);
  if (objectVisible)sprites.drawSelfMasked(35, 28, highscore, 0);
  drawScore(40, upY, SCORE_BIG_FONT);
};





#endif
