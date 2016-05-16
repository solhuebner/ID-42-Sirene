#ifndef LEVELS_H
#define LEVELS_H

#include <Arduino.h>
#include "globals.h"
#include "enemies.h"

#define TOTAL_AMOUNT_OF_LEVELS  4
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
    test = test + enemy[i].isAlive;
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
  enemySwimRightLeft(0, 3, 2);
  checkEndWave();
}

void wave002()
{
  if (checkStartWave())enemySetInLine(ENEMY_FISHY, 0, 3, 128, 32, 20, 0);
  enemySwimRightLeft(0, 3, 2);
  checkEndWave();
}

void wave003()
{
  if (checkStartWave())enemySetInLine(ENEMY_FISHY, 0, 3, 128, 56, 20, 0);
  enemySwimRightLeft(0, 3, 2);
  checkEndWave();
}

void wave004()
{
  if (checkStartWave())enemySetInLine(ENEMY_FISHY, 0, 3, 128, 12, 20, 0);
  enemySwimToMiddle(0, 3, 2);
  checkEndWave();
}

void wave005()
{
  if (checkStartWave())enemySetInLine(ENEMY_FISHY, 0, 3, 128, 56, 20, 0);
  enemySwimToMiddle(0, 3, 2);
  checkEndWave();
}

void wave006()
{
  if (checkStartWave())enemySetInLine(ENEMY_FISHY, 0, 3, 128, 32, 20, 0);
  enemySwimSine(0, 3, 2);
  checkEndWave();
}

void wave007()
{
  if (checkStartWave())enemySetInLine(ENEMY_FISHY, 0, 1,  128, 12, 0, 0);
  enemySwimRightLeft(0, 1, 2);
  checkEndWave();
}

void wave008()
{
  if (checkStartWave())enemySetInLine(ENEMY_FISHY, 0, 1, 128, 32, 0, 0);
  enemySwimRightLeft(0, 1, 2);
  checkEndWave();
}

void wave009()
{
  if (checkStartWave())enemySetInLine(ENEMY_FISHY, 0, 1, 128, 56, 0, 0);
  enemySwimRightLeft(0, 1, 2);
  checkEndWave();
}

void wave010()
{
  if (checkStartWave())enemySetInLine(ENEMY_FISHY, 0, 1, 128, 12, 0, 0);
  enemySwimRightLeft(0, 1, 3);
  checkEndWave();
}

void wave011()
{
  if (checkStartWave())enemySetInLine(ENEMY_FISHY, 0, 1, 128, 32, 0, 0);
  enemySwimRightLeft(0, 1, 3);
  checkEndWave();
}

void wave012()
{
  if (checkStartWave())enemySetInLine(ENEMY_FISHY, 0, 1, 128, 56, 0, 0);
  enemySwimRightLeft(0, 1, 3);
  checkEndWave();
}

void wave013()
{
  if (checkStartWave())enemySetInLine(ENEMY_JELLYFISH, 0, 3, 96, 64, -40, 16);
  enemySwimDownUp(0, 3, 2);
  checkEndWave();
}

void wave014()
{
  if (checkStartWave())enemySetInLine(ENEMY_JELLYFISH, 0, 3, 16, 64, 40, 16);
  enemySwimDownUp(0, 3, 2);
  checkEndWave();
}

void wave015()
{
  if (checkStartWave())enemySetInLine(ENEMY_JELLYFISH, 0, 3, 16, 64, 40, 0);
  enemySwimDownUp(0, 3, 2);
  checkEndWave();
}

void wave016()
{
  if (checkStartWave())enemySetInLine(ENEMY_JELLYFISH, 0, 2, 32, 64, 48, 0);
  enemySwimDownUp(0, 2, 2);
  checkEndWave();
}

void wave017()
{
  if (checkStartWave())enemySetInLine(ENEMY_EEL, 0, 1, 128, 12, 0, 0);
  enemySwimRightLeft(0, 1, 2);
  checkEndWave();
}

void wave018()
{
  if (checkStartWave())enemySetInLine(ENEMY_OCTOPUS, 0, 1, 128, 12, 0, 0);
  enemySwimRightLeft(0, 1, 2);
  checkEndWave();
}

void wave019()
{
  if (checkStartWave())enemySetInLine(ENEMY_FISH, 0, 3, 128, 12, 24, 0);
  enemySwimRightLeft(0, 3, 2);
  checkEndWave();
}

void wave020()
{
  if (checkStartWave())enemySetInLine(ENEMY_FISH, 0, 3, 128, 48, 24, 0);
  enemySwimRightLeft(0, 3, 2);
  checkEndWave();
}



// BOSS ATTACKS
///////////////

void wave250()
{
  //Shark attack
  if (checkStartWave())setShark();
  ((FunctionPointer) pgm_read_word (&sharkAttackFases[shark.attackFase]))();
  if (!shark.isAlive) currentWave++;
}

void wave251()
{
  //seahorse attack
  if (checkStartWave())setSeahorse();
  ((FunctionPointer) pgm_read_word (&seahorseAttackFases[seahorse.attackFase]))();
  if (!seahorse.isAlive) currentWave++;
}


void wave252()
{
  //pirateShip attack
  if (checkStartWave())setPirateShip();
  ((FunctionPointer) pgm_read_word (&pirateShipAttackFases[pirateShip.attackFase]))();
  if (!pirateShip.isAlive) currentWave++;
}



typedef void (*FunctionPointer) ();
const FunctionPointer PROGMEM Levels[TOTAL_AMOUNT_OF_LEVELS][TOTAL_AMOUNT_OF_WAVES] =
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
    wave252,
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
  },
    { //LEVEL 04
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
  Rect mermaidRect = {.x = mermaid.x + 2, .y = mermaid.y + 2, .width = 12, .height = 12};
  Rect sharkRect = {.x = shark.x, .y = shark.y + 2, .width = 32, .height = 12};
  Rect seahorseRect = {.x = seahorse.x, .y = seahorse.y + 2, .width = 32, .height = 12};
  Rect pirateShipRect = {.x = pirateShip.x, .y = pirateShip.y + 2, .width = 32, .height = 12};

  ////// Check collision bullets with enemies and bosses /////
  ////////////////////////////////////////////////////////////
  for (byte k = 0; k < MAX_ONSCREEN_BULLETS; k++)
  {
    if (bullet[k].isVisible)
    {
      Rect bulletsRect {.x = bullet[k].x, .y = bullet[k].y, .width = 8, .height = 8};
      for (byte i = 0; i < MAX_ONSCREEN_ENEMIES; i++)
      {
        Rect enemyRect = {.x = enemy[i].x, .y = enemy[i].y, .width = 16, .height = 16};
        if (enemy[i].isVisible && !enemy[i].isDying && physics.collide(bulletsRect, enemyRect))
        {
          if (!enemy[i].isImune)
          {
            enemy[i].HP -= bullet[k].damage;
            enemy[i].isImune = true;
          }
          if (bullet[k].type != WEAPON_TYPE_MAGIC)
          {
            bullet[k].isVisible = false;
          }
        }
      }
      if (shark.isVisible && !shark.isDying && physics.collide(bulletsRect, sharkRect))
      {
        if (!shark.isImune)
        {
          shark.isImune = true;
          bullet[k].isVisible = false;
          shark.HP -= bullet[k].damage;
        }
      }
    }
  }


  ////// Check collision mermaid with enemies and bosses /////
  ////////////////////////////////////////////////////////////

  for (byte i = 0; i < MAX_ONSCREEN_ENEMIES; i++)
  {
    Rect enemyRect = {.x = enemy[i].x, .y = enemy[i].y, .width = 16, .height = 16};
    if (enemy[i].isVisible && !enemy[i].isDying && physics.collide(mermaidRect, enemyRect))
    {
      if (!mermaid.isImune)
      {
        mermaid.isImune = true;
        mermaid.HP -= 1;
      }
      if (!enemy[i].isImune)
      {
        enemy[i].isDying = true;
      }
    }
  }
  if (shark.isVisible)
  {
    if (shark.isVisible && !shark.isDying && physics.collide(mermaidRect, sharkRect))
    {
      if (!shark.isImune)
      {
        shark.isImune = true;
        shark.HP--;
      }
      if (!mermaid.isImune)
      {
        mermaid.isImune = true;
        mermaid.HP -= 1;
      }
    }
  }
  if (seahorse.isVisible) {}
  if (pirateShip.isVisible) {}

}

void drawLifeHUD()
{
  sprites.drawPlusMask(0, 0, hearts_plus_mask, mermaid.HP - 2);
}

void drawScoreHUD(byte x, byte y)
{
  char buf[10];
  //scorePlayer = arduboy.cpuLoad();
  ltoa(scorePlayer, buf, 10);
  char charLen = strlen(buf);
  char pad = 7 - charLen;

  //draw 0 padding
  for (byte i = 0; i < pad; i++)
  {
    sprites.drawPlusMask(x + (5 * i), y, numbers_plus_mask, 0);
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
    sprites.drawPlusMask(x + (pad * 5) + (5 * i), y, numbers_plus_mask, digit);
  }
}

#endif
