#ifndef TEST_MAP
#define TEST_MAP

#include "map.h"

typedef struct TestMapResources
{
  MapResources mapRes;
} TestMapResources;

class TestMap
{
public:
  TestMap(TestMapResources res)
  {
    map = new Map(res.mapRes);
  }
  void update();
  void draw();

private:
  Map *map;
};

void TestMap::update()
{
}

void TestMap::draw()
{
  map->draw2D();
}

#endif
