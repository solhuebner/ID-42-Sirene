#ifndef MENU_H
#define MENU_H

#include <Arduino.h>
#include "globals.h"
byte hairFrame = 0;
byte eyesFrame = 0;
byte eyesSequence[] = {0, 1, 2, 3, 3, 3, 1};

void drawTitleScreen()
{
  byte eyesFrame2;
  if (arduboy.everyXFrames(10)) hairFrame++;
  if (arduboy.everyXFrames(2)) eyesFrame++;
  if (eyesFrame > 60)eyesFrame = 0;
  eyesFrame2 = eyesFrame;
  if (eyesFrame2 > 6) eyesFrame2 = 0;
  if (hairFrame > 3) hairFrame = 0;
  sprites.drawSelfMasked(36, 1, mermaidTitle, 0);
  sprites.drawSelfMasked(59, 21, mermaidTrident, 0);
  sprites.drawSelfMasked(62, 48, mermaidFin, 0);
  sprites.drawSelfMasked(4, 46, mermaidBody, 0);
  sprites.drawSelfMasked(3, 14, mermaidHair, hairFrame);
  sprites.drawSelfMasked(10, 24, mermaidBlink, eyesSequence[eyesFrame2]);
}

void stateMenuIntro()
{
  globalCounter++;
  for (byte i = 0; i < 4; i++) sprites.drawSelfMasked(32*i, 10, TEAMarg, i);
  sprites.drawSelfMasked(43, 50, TEAM_argPart5, 0);
  if (globalCounter > 180)
  {
    globalCounter = 0;
    gameState = STATE_MENU_MAIN;
  }
}

void stateMenuMain()
{
  drawTitleScreen();
  for (byte i = 0; i < 4; i++)
  {
    sprites.drawSelfMasked(108, 32 +(i*8), menuText, i);
  }
  sprites.drawPlusMask(92, 32 + 8*(menuSelection-2), trident_plus_mask, 0);
  if (buttons.justPressed(DOWN_BUTTON) && (menuSelection < 5)) menuSelection++;
  if (buttons.justPressed(UP_BUTTON) && (menuSelection > 2)) menuSelection--;
  if (buttons.justPressed(B_BUTTON)) gameState = menuSelection;
}

void stateMenuHelp()
{
  for (byte i = 0; i < 2; i++) sprites.drawSelfMasked(32, 32*i, qrcode, i);
  if (buttons.justPressed(A_BUTTON | B_BUTTON)) gameState = STATE_MENU_MAIN;
}


void stateMenuInfo()
{
  sprites.drawSelfMasked(36, 10, mermaidTitle, 0);
  sprites.drawSelfMasked(16, 36, info, 0);
  if (buttons.justPressed(A_BUTTON | B_BUTTON)) gameState = STATE_MENU_MAIN;
}

void stateMenuSoundfx()
{
  if (buttons.justPressed(DOWN_BUTTON)) soundYesNo = true;
  if (buttons.justPressed(UP_BUTTON)) soundYesNo = false;
  if (buttons.justPressed(A_BUTTON | B_BUTTON))
  {
    arduboy.audio.saveOnOff();
    gameState = STATE_MENU_MAIN;
  }
  if (soundYesNo == true) arduboy.audio.on();
  else arduboy.audio.off();
}

#endif
