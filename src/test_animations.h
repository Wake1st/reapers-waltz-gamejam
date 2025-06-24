#ifndef TEST_ANIMATIONS
#define TEST_ANIMATIONS

#include "globals.h"
#include "actor.h"

typedef struct TestAnimationResources
{
  Texture2D playerTexture;
} TestAnimationResources;

class TestAnimations
{
public:
  TestAnimations(TestAnimationResources res)
  {
    player = new Actor(res.playerTexture, OUTER_BUFFER + 2 + (OUTER_BUFFER + 1) * MAP_WIDTH);
  }
  void update();
  void draw();

private:
  Actor *player;
  Actor *enemy;
};

void TestAnimations::update()
{
  player->update();
  // enemy->update();
}

void TestAnimations::draw()
{
  player->draw();
  // enemy->draw();
}

#endif
