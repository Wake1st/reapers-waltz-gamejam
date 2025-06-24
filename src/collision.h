#ifndef COLLISION
#define COLLISION

#include <vector>
#include "raylib.h"

#include "globals.h"
#include "tile.h"

class Collision
{
public:
  static bool check(Command *command, Vector2 position, std::vector<Tile *> tiles);
};

bool Collision::check(Command *command, Vector2 position, std::vector<Tile *> tiles)
{
  Rectangle playerRect = {position.x, position.y, CELL_SIZE, CELL_SIZE};

  Rectangle nRect = {tiles[0]->position.x, tiles[0]->position.y, CELL_SIZE, CELL_SIZE};
  Rectangle eRect = {tiles[2]->position.x, tiles[2]->position.y, CELL_SIZE, CELL_SIZE};
  Rectangle sRect = {tiles[4]->position.x, tiles[4]->position.y, CELL_SIZE, CELL_SIZE};
  Rectangle wRect = {tiles[6]->position.x, tiles[6]->position.y, CELL_SIZE, CELL_SIZE};
  Rectangle neRect = {tiles[1]->position.x, tiles[1]->position.y, CELL_SIZE, CELL_SIZE};
  Rectangle seRect = {tiles[3]->position.x, tiles[3]->position.y, CELL_SIZE, CELL_SIZE};
  Rectangle swRect = {tiles[5]->position.x, tiles[5]->position.y, CELL_SIZE, CELL_SIZE};
  Rectangle nwRect = {tiles[7]->position.x, tiles[7]->position.y, CELL_SIZE, CELL_SIZE};

  bool nCollided = tiles[0]->isWall && CheckCollisionRecs(playerRect, nRect);
  bool eCollided = tiles[2]->isWall && CheckCollisionRecs(playerRect, eRect);
  bool sCollided = tiles[4]->isWall && CheckCollisionRecs(playerRect, sRect);
  bool wCollided = tiles[6]->isWall && CheckCollisionRecs(playerRect, wRect);
  bool neCollided = tiles[1]->isWall && CheckCollisionRecs(playerRect, neRect);
  bool seCollided = tiles[3]->isWall && CheckCollisionRecs(playerRect, seRect);
  bool swCollided = tiles[5]->isWall && CheckCollisionRecs(playerRect, swRect);
  bool nwCollided = tiles[7]->isWall && CheckCollisionRecs(playerRect, nwRect);

  switch (*command)
  {
  case Command::N:
    return nwCollided || nCollided || neCollided;
  case Command::NE:
    return nCollided || neCollided || eCollided;
  case Command::E:
    return neCollided || eCollided || seCollided;
  case Command::SE:
    return eCollided || seCollided || sCollided;
  case Command::S:
    return seCollided || sCollided || swCollided;
  case Command::SW:
    return sCollided || swCollided || wCollided;
  case Command::W:
    return swCollided || wCollided || nwCollided;
  case Command::NW:
    return wCollided || nwCollided || nCollided;
  default:
    return false;
  }
}

#endif
