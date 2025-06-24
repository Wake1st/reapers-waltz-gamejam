#ifndef MAP
#define MAP

#include <cstdio>
#include <vector>
#include "raylib.h"

#include "globals.h"
#include "tile.h"
#include "floorplan.h"

typedef struct MapResources
{
  Texture2D wallTexture;
  Texture2D floorTexture;
} MapResources;

class Map
{
public:
  Map(MapResources res)
  {
    //  Leave room for outer boundary, no special checks needed
    tiles = std::vector<Tile *>();
    for (int i = 0; i < MAP_SIZE; i++)
    {
      Vector2 position = PositionOfCell(i);
      tiles.push_back(new Tile(position));
    }

    // go over floorplans and determine which tiles are floors
    Floorplan *plan = Floorplans::plans[0];
    for (Rectangle *room : plan->rooms)
    {
      for (int j = room->y; j < (room->y + room->height); j++)
      {
        for (int i = room->x; i < (room->x + room->width); i++)
        {
          int cell = i + j * MAP_WIDTH;
          tiles[cell]->isWall = false;
        }
      }
    }

    floorTexture = res.floorTexture;
    wallTexture = res.wallTexture;
  }
  void update();
  void draw2D();
  std::vector<Tile *> getNeighbors(int cell);

private:
  std::vector<Tile *> tiles;
  Texture2D wallTexture;
  Texture2D floorTexture;
};

void Map::draw2D()
{
  for (Tile *tile : tiles)
  {
    if (tile->isWall)
      DrawRectangle(tile->position.x, tile->position.y, CELL_SIZE, CELL_SIZE, BLACK);
    else
      DrawTextureEx(floorTexture, tile->position, 0.f, 1.0f, WHITE);
    // DrawRectangle(tile->position.x, tile->position.y, CELL_SIZE, CELL_SIZE, DARKGRAY);
  }
}

std::vector<Tile *> Map::getNeighbors(int cell)
{
  return std::vector<Tile *>{
      tiles[cell - MAP_WIDTH],     // N
      tiles[cell - MAP_WIDTH + 1], // NE
      tiles[cell + 1],             // E
      tiles[cell + MAP_WIDTH + 1], // SE
      tiles[cell + MAP_WIDTH],     // S
      tiles[cell + MAP_WIDTH - 1], // SW
      tiles[cell - 1],             // W
      tiles[cell - MAP_WIDTH - 1], // NW
  };
}

#endif
