#ifndef TEST_COLLISIONS
#define TEST_COLLISIONS

#include "map.h"
#include "actor.h"
#include "collision.h"

typedef struct TestCollisionsResources
{
  Texture2D playerTexture;
  int startCell;
  MapResources mapRes;
} TestCollisionsResources;

class TestCollisions
{
public:
  TestCollisions(TestCollisionsResources res)
  {
    input = new InputHandler();
    actor = new Actor(res.playerTexture, res.startCell);
    map = new Map(res.mapRes);
  }
  void update();
  void draw();
  void draw2D();
  Vector2 getPlayerPosition();

private:
  InputHandler *input;
  Actor *actor;
  Map *map;
};

Vector2 TestCollisions::getPlayerPosition()
{
  return actor->position;
}

void TestCollisions::update()
{
  Command command = input->handleInput();
  if (command)
  {
    // check for collisions
    if (!Collision::check(&command, actor->position, map->getNeighbors(actor->currentCell)))
    {
      actor->move(&command);
    }
  }

  actor->update();
}

void TestCollisions::draw()
{
  actor->draw();

  // std::vector<Tile *> tiles = map->getNeighbors(actor->currentCell);
  // for (int i = 0; i < 8; i++)
  // {
  //   DrawText(TextFormat("tile pos x: %f\ttile pos y: %f\tcell: %i", tiles[i]->position.x, tiles[i]->position.x, i), 20, 100 + i * 40, 40, WHITE);
  // }
}

void TestCollisions::draw2D()
{
  map->draw2D();
  actor->draw2D();
}

#endif
