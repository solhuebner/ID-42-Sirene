#ifndef LEVELS_H
#define LEVELS_H

#include <Arduino.h>
#include "globals.h"
#include "enemies.h"

#define TOTAL_AMOUNT_OF_LEVELS  9
#define TOTAL_AMOUNT_OF_WAVES   20

byte currentWave;
byte previousWave;

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
    test += enemy[i].isAlive;
  }
  test += powerUP.isActive;
  if (test < 1) currentWave++;
}

void wait()
{
  if (arduboy.everyXFrames(4)) globalCounter++;
  if (globalCounter > 16)
  {
    if (gameState == STATE_GAME_PLAYING) currentWave++;
    else gameOverAndStageFase++;
    globalCounter = 0;
  }
}

void wave000()
{
  wait();
}

void wave001()
{
  if (checkStartWave())
  {
    enemySetInLine(ENEMY_FISHY, 0, 3, 128, 12, 20, 0);
    powerUPSet(128, 24, POWER_UP_STAR);
  }
  enemySwimRightLeft(0, 3, 2);
  powerUPFloatRightLeft(1);
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
  if (checkStartWave())
  {
    enemySetInLine(ENEMY_OCTOPUS, 0, 1, 128, 8, 0, 0);
    enemySetInLine(ENEMY_OCTOPUS, 1, 2, 176, 56, 0, 0);
  }
  enemySwimRightLeft(0, 2, 2);
  enemyShoot(0, 2, 1);
  checkEndWave();
}

void wave018()
{
  if (checkStartWave())
  {
    enemySetInLine(ENEMY_OCTOPUS, 0, 3, 128, 8, 96, 0);
    enemySetInLine(ENEMY_OCTOPUS, 3, 6, 176, 48, 96, 0);
  }

  enemySwimRightLeft(0, 6, 2);
  enemyShoot(0, 6, 1);
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
  if (checkStartWave())setEndBoss();
  ((FunctionPointer) pgm_read_word (&sharkAttackFases[endBoss.attackFase]))();
  if (!endBoss.isAlive) currentWave++;
}

void wave251()
{
  //seahorse attack
  if (checkStartWave())setEndBoss();
  ((FunctionPointer) pgm_read_word (&seahorseAttackFases[endBoss.attackFase]))();
  if (!endBoss.isAlive) currentWave++;
}

void wave252()
{
  //pirateShip attack
  if (checkStartWave())setEndBoss();
  ((FunctionPointer) pgm_read_word (&pirateShipAttackFases[endBoss.attackFase]))();
  if (!endBoss.isAlive) currentWave++;
}


// END WAVES
///////////////
void wave254()
{
  gameState = STATE_GAME_NEXT_LEVEL;
}

void wave255()
{
  mermaid.x = 16;
  mermaid.y = 32;
  gameState = STATE_GAME_ENDED;
}


typedef void (*FunctionPointer) ();
const FunctionPointer PROGMEM Levels[TOTAL_AMOUNT_OF_LEVELS][TOTAL_AMOUNT_OF_WAVES] =
{
  { //LEVEL 01-01
    wave000,
    wave001,
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
    wave000,
    wave255,
  },
  { //LEVEL 01-02
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
    wave000,
    wave254,
  },
  { //LEVEL 01-03
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
    wave250,
    wave000,
    wave254,
  },
  { //LEVEL 02-01
    wave000,
    wave018,
    wave019,
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
    wave000,
    wave254,
  },
  { //LEVEL 02-02
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
    wave000,
    wave254,
  },
  { //LEVEL 02-03
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
    wave251,
    wave000,
    wave254,
  },
  { //LEVEL 03-01
    wave000,
    wave018,
    wave019,
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
    wave000,
    wave254,
  },
  { //LEVEL 03-02
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
    wave000,
    wave254,
  },
  { //LEVEL 03-03
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
    wave252,
    wave000,
    wave255,
  }
};

void checkCollisions()
{
  Rect mermaidRect = {.x = mermaid.x + MERMAID_COLLISION_OFFSET, .y = mermaid.y + MERMAID_COLLISION_OFFSET, .width = MERMAID_COLLISION_SIZE, .height = MERMAID_COLLISION_SIZE};
  Rect endBossRect = {.x = endBoss.x, .y = endBoss.y + 2, .width = 32, .height = 12};


  ////// Check collision bullets with enemies and bosses /////
  ////////////////////////////////////////////////////////////
  for (byte k = 0; k < MAX_ONSCREEN_BULLETS; k++)
  {
    if (bullet[k].isVisible)
    {
      Rect bulletsRect {.x = bullet[k].x + bulletCollisionOffset[bullet[k].type], .y = bullet[k].y, .width = 8, .height = 8};
      for (byte i = 0; i < MAX_ONSCREEN_ENEMIES; i++)
      {
        Rect enemyRect = {.x = enemy[i].x, .y = enemy[i].y, .width = enemyCollisionWidth[enemy[i].type], .height = enemyCollisionHeight[enemy[i].type]};
        if (enemy[i].isVisible && !enemy[i].isDying && arduboy.collide(bulletsRect, enemyRect))
        {
          if (!enemy[i].isImune)
          {
            arduboy.audio.tone(523, 10);
            enemy[i].HP -= bullet[k].damage;
            enemy[i].isImune = true;
          }
          if (bullet[k].type != WEAPON_TYPE_MAGIC)
          {
            bullet[k].isVisible = false;
          }
        }
      }
      if (endBoss.isVisible && !endBoss.isDying && arduboy.collide(bulletsRect, endBossRect))
      {
        if (!endBoss.isImune)
        {
          arduboy.audio.tone(523, 10);
          endBoss.isImune = true;
          bullet[k].isVisible = false;
          endBoss.HP -= bullet[k].damage;
        }
      }
    }
  }


  ////// Check collision mermaid with enemies and bosses /////
  ////////////////////////////////////////////////////////////

  for (byte i = 0; i < MAX_ONSCREEN_ENEMIES; i++)
  {
    Rect enemyRect = {.x = enemy[i].x, .y = enemy[i].y, .width = enemyCollisionWidth[enemy[i].type], .height = enemyCollisionHeight[enemy[i].type]};
    if (enemy[i].isVisible && !enemy[i].isDying && arduboy.collide(mermaidRect, enemyRect))
    {
      if (!mermaid.isImune)
      {
        arduboy.audio.tone(2349, 15);
        mermaid.isImune = true;
        mermaid.HP -= 1;
      }
      if (!enemy[i].isImune)
      {
        enemy[i].isDying = true;
      }
    }
  }
  for (byte i = 0; i < MAX_ONSCREEN_ENEMY_BULLETS; i++)
  {
    Rect enemyBulletRect = {.x = enemyBullet[i].x + 1, .y = enemyBullet[i].y + 1, .width = 6, .height = 6};
    if (enemyBullet[i].isVisible && arduboy.collide(mermaidRect, enemyBulletRect))
    {
      if (!mermaid.isImune)
      {
        arduboy.audio.tone(2349, 15);
        mermaid.isImune = true;
        mermaid.HP -= BULLET_DAMAGE;
        enemyBullet[i].isVisible = false;
      }
    }
  }

  if (endBoss.isVisible)
  {
    if (endBoss.isVisible && !endBoss.isDying && arduboy.collide(mermaidRect, endBossRect))
    {
      if (!endBoss.isImune)
      {
        arduboy.audio.tone(2349, 15);
        endBoss.isImune = true;
        endBoss.HP--;
      }
      if (!mermaid.isImune)
      {
        mermaid.isImune = true;
        mermaid.HP -= 1;
      }
    }
  }

#define POWER_UP_HEART             0
#define POWER_UP_STAR              1
#define POWER_UP_TRIDENT           2
#define POWER_UP_BUBBLE            3
#define POWER_UP_SEASHELL          4
#define POWER_UP_MAGIC             5

  if (powerUP.isActive)
  {
    Rect powerUPRect = {.x = powerUP.x, .y = powerUP.y, .width = 8, .height = 8};
    if (arduboy.collide(mermaidRect, powerUPRect))
    {
      switch (powerUP.type)
      {
        case POWER_UP_HEART:
          if (mermaid.HP < 4) mermaid.HP++;
          else scorePlayer += 1000;
          break;
        case POWER_UP_STAR:
          mermaid.isSuper = true;
          break;
        case POWER_UP_TRIDENT:
          mermaid.weaponType = WEAPON_TYPE_TRIDENT;
          break;
        case POWER_UP_BUBBLE:
          mermaid.weaponType = WEAPON_TYPE_BUBBLES;
          break;
        case POWER_UP_SEASHELL:
          mermaid.weaponType = WEAPON_TYPE_SEASHELL;
          break;
        case POWER_UP_MAGIC:
          mermaid.weaponType = WEAPON_TYPE_MAGIC;
          break;
      }
      powerUP.isActive = false;
    }
  }
}

void drawLifeHUD()
{
  for (byte i = 0; i < 3; i++) sprites.drawSelfMasked(8 * i, 0, hearts, 0);
  for (byte i = 0; i < mermaid.HP - 1; i++)sprites.drawSelfMasked(8 * i, 0, hearts, 1);
}


void drawScore(byte fontType)
{
  char buf[10];
  //scorePlayer = arduboy.cpuLoad();
  ltoa(scorePlayer, buf, 10);
  char charLen = strlen(buf);
  char pad = 7 - charLen;

  //draw 0 padding
  for (byte i = 0; i < pad; i++)
  {
    switch (fontType)
    {
      case SCORE_SMALL_FONT:
        sprites.drawSelfMasked(95 + (5 * i), 0, numbersSmall, 0);
        break;
      case SCORE_BIG_FONT:
        sprites.drawSelfMasked(40 + (7 * i), 40, numbersBig, 0);
        break;
    }
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
    switch (fontType)
    {
      case SCORE_SMALL_FONT:
        sprites.drawSelfMasked(95 + (pad * 5) + (5 * i), 0, numbersSmall, digit);
        break;
      case SCORE_BIG_FONT:
        sprites.drawSelfMasked(40 + (pad * 7) + (7 * i), 40, numbersBig, digit);
        break;
    }
  }
}


#endif
