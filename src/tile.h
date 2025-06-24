#ifndef TILE
#define TILE

#include "raylib.h"

#include "globals.h"

class Tile
{
public:
  Vector2 position;
  bool isWall;

  Tile(Vector2 pos, bool wall = true)
  {
    position = pos;
    isWall = wall;
  }
};

#endif
