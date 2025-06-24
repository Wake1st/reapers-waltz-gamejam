#ifndef INTERACTABLE
#define INTERACTABLE

#include "raylib.h"

#include "globals.h"

#define ORB_RADIUS 8.f
#define TEXT_OFFSET_X 240.f
#define TEXT_OFFSET_Y 180.f

class Interactable
{
public:
  int cell;

  // Interactable(Texture2D text, int cellIndex, const char *dialogueText)
  Interactable(int cellIndex, const char *dialogueText)
  {
    // texture = text;
    cell = cellIndex;
    position = PositionOfCell(cellIndex);
    dialogue = dialogueText;
  }
  bool checkActive(int checkCell);
  const char *getText();
  void draw();
  void draw2D();

private:
  // Texture2D texture;
  Vector2 position;

  bool active;
  const char *dialogue;
};

bool Interactable::checkActive(int checkCell)
{
  active = cell == checkCell;
  return active;
}

const char *Interactable::getText()
{
  return dialogue;
}

void Interactable::draw()
{
  if (active)
  {
    DrawText("Press 'X' to open dialogue.", SCREEN_WIDTH / 2.f - TEXT_OFFSET_X, SCREEN_HEIGHT - TEXT_OFFSET_Y, 40, WHITE);
  }
}

void Interactable::draw2D()
{
  DrawCircle(position.x + CELL_SIZE / 2.f, position.y + CELL_SIZE / 2.f, ORB_RADIUS, YELLOW);
}

#endif
