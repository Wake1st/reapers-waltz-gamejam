#ifndef INPUT
#define INPUT

#include "raylib.h"
#include "globals.h"

class InputHandler
{
public:
  Command handleInput();
};

Command InputHandler::handleInput()
{
  if (IsKeyDown(KEY_RIGHT) && IsKeyDown(KEY_UP))
    return Command::NE;
  if (IsKeyDown(KEY_RIGHT) && IsKeyDown(KEY_DOWN))
    return Command::SE;
  if (IsKeyDown(KEY_RIGHT))
    return Command::E;
  if (IsKeyDown(KEY_LEFT) && IsKeyDown(KEY_UP))
    return Command::NW;
  if (IsKeyDown(KEY_LEFT) && IsKeyDown(KEY_DOWN))
    return Command::SW;
  if (IsKeyDown(KEY_LEFT))
    return Command::W;
  if (IsKeyDown(KEY_UP))
    return Command::N;
  if (IsKeyDown(KEY_DOWN))
    return Command::S;
  if (IsKeyPressed(KEY_X))
    return Command::ACTION;

  // nothing pressed
  return Command::NONE;
}

#endif
