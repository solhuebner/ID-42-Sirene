#ifndef PLAYER_H
#define PLAYER_H

#include <Arduino.h>
#include "globals.h"

byte mermaidFrame = 0;

struct Players
{
  public:
    int x;
    int y;
};

Players mermaid = { .x = 20, .y = 20};

void drawPlayer()
{
  if (arduboy.everyXFrames(10)) mermaidFrame++;
  if (mermaidFrame > 5 ) mermaidFrame = 0;
  sprites.drawPlusMask(mermaid.x, mermaid.y, mermaid_plus_mask, mermaidFrame);
}

#endif
