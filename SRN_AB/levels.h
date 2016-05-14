#ifndef LEVELS_H
#define LEVELS_H

#include <Arduino.h>
#include "globals.h"
#include "enemies.h"

#define TOTAL_AMOUNT_OF_LEVELS  3
#define TOTAL_AMOUNT_OF_WAVES   22

boolean checkStartWave()
{
  if (currentWave != previousWave)
  {
    previousWave = currentWave;
    return true;
  }
  return false;
}


boolean checkEndWave()
{
  byte test = 0;
  for (byte i = 0; i < MAX_ONSCREEN_ENEMIES; i++)
  {
    test = test + enemy[i].isActive;
  }
  if (test < 1) currentWave++;
}

boolean checkEndLevel()
{
  if (currentWave > TOTAL_AMOUNT_OF_WAVES - 1)
  {
    return true;
  }
  return false;
}

void waitFor(byte amount)
{
  if (arduboy.everyXFrames(4)) waveTimer++;
  if (waveTimer > amount)
  {
    currentWave++;
    waveTimer = 0;
  }
}

void wave000()
{
  waitFor(16);
}

void wave001()
{
  if (checkStartWave())enemySetInLine(ENEMY_FISHY, 0, 3, 128, 12, 20, 0);
  enemySwimRightLeft(0, 3, 1);
  checkEndWave();
}

void wave002()
{
  if (checkStartWave())enemySetInLine(ENEMY_FISHY, 0, 3, 128, 32, 20, 0);
  enemySwimRightLeft(0, 3, 1);
  checkEndWave();
}

void wave003()
{
  if (checkStartWave())enemySetInLine(ENEMY_FISHY, 0, 3, 128, 56, 20, 0);
  enemySwimRightLeft(0, 3, 1);
  checkEndWave();
}

void wave004()
{
  if (checkStartWave())enemySetInLine(ENEMY_FISHY, 0, 3, 128, 12, 20, 0);
  enemySwimToMiddle(0, 3, 1);
  checkEndWave();
}

void wave005()
{
  if (checkStartWave())enemySetInLine(ENEMY_FISHY, 0, 3, 128, 56, 20, 0);
  enemySwimToMiddle(0, 3, 1);
  checkEndWave();
}

void wave006()
{
  if (checkStartWave())enemySetInLine(ENEMY_FISHY, 0, 3, 128, 32, 20, 0);
  enemySwimSine(0, 3, 1);
  checkEndWave();
}

void wave007()
{
  if (checkStartWave())enemySetInLine(ENEMY_FISHY, 0, 1,  128, 12, 0, 0);
  enemySwimRightLeft(0, 1, 1);
  checkEndWave();
}

void wave008()
{
  if (checkStartWave())enemySetInLine(ENEMY_FISHY, 0, 1, 128, 32, 0, 0);
  enemySwimRightLeft(0, 1, 1);
  checkEndWave();
}

void wave009()
{
  if (checkStartWave())enemySetInLine(ENEMY_FISHY, 0, 1, 128, 56, 0, 0);
  enemySwimRightLeft(0, 1, 1);
  checkEndWave();
}

void wave010()
{
  if (checkStartWave())enemySetInLine(ENEMY_FISHY, 0, 1, 128, 12, 0, 0);
  enemySwimRightLeft(0, 1, 2);
  checkEndWave();
}

void wave011()
{
  if (checkStartWave())enemySetInLine(ENEMY_FISHY, 0, 1, 128, 32, 0, 0);
  enemySwimRightLeft(0, 1, 2);
  checkEndWave();
}

void wave012()
{
  if (checkStartWave())enemySetInLine(ENEMY_FISHY, 0, 1, 128, 56, 0, 0);
  enemySwimRightLeft(0, 1, 2);
  checkEndWave();
}

void wave013()
{
  if (checkStartWave())enemySetInLine(ENEMY_JELLYFISH, 0, 3, 96, 64, -40, 16);
  enemySwimDownUp(0, 3, 1);
  checkEndWave();
}

void wave014()
{
  if (checkStartWave())enemySetInLine(ENEMY_JELLYFISH, 0, 3, 16, 64, 40, 16);
  enemySwimDownUp(0, 3, 1);
  checkEndWave();
}

void wave015()
{
  if (checkStartWave())enemySetInLine(ENEMY_JELLYFISH, 0, 3, 16, 64, 40, 0);
  enemySwimDownUp(0, 3, 1);
  checkEndWave();
}

void wave016()
{
  if (checkStartWave())enemySetInLine(ENEMY_JELLYFISH, 0, 2, 32, 64, 48, 0);
  enemySwimDownUp(0, 2, 1);
  checkEndWave();
}

void wave017()
{
  if (checkStartWave())enemySetInLine(ENEMY_EEL, 0, 1, 128, 12, 0, 0);
  enemySwimRightLeft(0, 1, 1);
  checkEndWave();
}

void wave018()
{
  if (checkStartWave())enemySetInLine(ENEMY_OCTOPUS, 0, 1, 128, 12, 0, 0);
  enemySwimRightLeft(0, 1, 1);
  checkEndWave();
}

void wave019()
{
  if (checkStartWave())enemySetInLine(ENEMY_FISH, 0, 3, 128, 12, 24, 0);
  enemySwimRightLeft(0, 3, 1);
  checkEndWave();
}

void wave020()
{
  if (checkStartWave())enemySetInLine(ENEMY_FISH, 0, 3, 128, 48, 24, 0);
  enemySwimRightLeft(0, 3, 1);
  checkEndWave();
}



// BOSS ATTACKS
///////////////

void wave250()
{
  //Shark attack
  if (checkStartWave())setShark();
  sharkAttackFases[shark.attackFase]();
  if (!shark.isActive) currentWave++;
}

void wave251()
{
  //pirateShip attack
  if (checkStartWave())setPirateShip();
  pirateShipAttackFases[pirateShip.attackFase]();
  if (!pirateShip.isActive) currentWave++;
}



typedef void (*FunctionPointer) ();

FunctionPointer Levels[TOTAL_AMOUNT_OF_LEVELS][TOTAL_AMOUNT_OF_WAVES] =
{
  { //LEVEL 01
    wave000,
    wave020,
    wave019,
    wave018,
    wave017,
    wave016,
    wave015,
    wave014,
    wave013,
    wave012,
    wave011,
    wave010,
    wave009,
    wave008,
    wave007,
    wave006,
    wave005,
    wave004,
    wave003,
    wave002,
    wave001,
    wave250,
  },
  { //LEVEL 02
    wave000,
    wave001,
    wave002,
    wave003,
    wave004,
    wave005,
    wave006,
    wave007,
    wave008,
    wave009,
    wave010,
    wave011,
    wave012,
    wave013,
    wave014,
    wave015,
    wave016,
    wave017,
    wave018,
    wave019,
    wave020,
    wave251,
  },
  { //LEVEL 03
    wave000,
    wave001,
    wave002,
    wave003,
    wave004,
    wave005,
    wave006,
    wave007,
    wave008,
    wave009,
    wave010,
    wave011,
    wave012,
    wave013,
    wave014,
    wave015,
    wave016,
    wave017,
    wave018,
    wave019,
    wave020,
    wave250,
  }
};

void checkCollisions()
{

  ////// Check collision mermaid enemies /////
  ////////////////////////////////////////////
  Rect mermaidRect = {.x = mermaid.x + 2, .y = mermaid.y + 2, .width = 12, .height = 12};
  for (byte i = 0; i < MAX_ONSCREEN_ENEMIES; i++)
  {
    Rect enemyRect = {.x = enemy[i].x, .y = enemy[i].y, .width = 16, .height = 16};

    for (byte k = 0; k < MAX_ONSCREEN_BULLETS; k++)
    {
      Rect bulletsRect {.x = bullet[k].x, .y = bullet[k].y, .width = 8, .height = 8};
      if (enemy[i].isActive && !enemy[i].isDying && bullet[k].isActive && physics.collide(bulletsRect, enemyRect))
      {
        bullet[k].isActive = false;
        enemy[i].isDying = true;
        enemy[i].frame = 0;
      }
    }

    
    if (enemy[i].isActive && !enemy[i].isDying && physics.collide(mermaidRect, enemyRect))
    {
      if (!mermaid.isImune)
      {
        mermaid.isImune = true;
        mermaid.HP -= 1;
      }
      enemy[i].isDying = true;
      enemy[i].frame = 0;
    }
  }
}

void drawLifeHUD()
{
  sprites.drawPlusMask(0, 0, hearts_plus_mask, mermaid.HP - 2);
}

void drawScoreHUD()
{
  char buf[10];
  scorePlayer = arduboy.cpuLoad();
  ltoa(scorePlayer, buf, 10);
  char charLen = strlen(buf);
  char pad = 7 - charLen;

  //draw 0 padding
  for (byte i = 0; i < pad; i++)
  {
    sprites.drawPlusMask(93 + (5 * i), 0, numbers_plus_mask, 0);
  }

  for (byte i = 0; i < charLen; i++)
  {
    char digit = buf[i];
    byte j;
    if (digit <= 48)
    {
      digit = 0;
    }
    else {
      digit -= 48;
      if (digit > 9) digit = 0;
    }

    for (byte z = 0; z < 10; z++)
    {
      if (digit == z) j = z;
    }
    sprites.drawPlusMask(93 + (pad * 5) + (5 * i), 0, numbers_plus_mask, digit);
  }
}

#endif
