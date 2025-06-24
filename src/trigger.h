#ifndef TRIGGER
#define TRIGGER

#include "raylib.h"

#include "globals.h"

class Trigger
{
public:
  bool active = false;

  Trigger(int cellIndex)
  {
    cell = cellIndex;
    position = PositionOfCell(cellIndex);
  }
  void activate(bool value);
  void draw();

private:
  int cell;
  Vector2 position;
};

void Trigger::activate(bool value)
{
  active = value;
}

void Trigger::draw()
{
  DrawRectangle(position.x, position.y, CELL_SIZE, CELL_SIZE, RED);
}

#endif
