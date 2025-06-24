#ifndef TEST_MOVEMENT
#define TEST_MOVEMENT

#include "input.h"
#include "actor.h"

typedef struct TestMovementResources
{
  Texture2D texture;
} TestMovementResources;

class TestMovement
{
public:
  TestMovement(TestMovementResources res)
  {
    input = new InputHandler();
    actor = new Actor(res.texture, 0);
  }
  void update();
  void draw();

private:
  InputHandler *input;
  Actor *actor;
};

void TestMovement::update()
{
  Command command = input->handleInput();
  if (command)
  {
    actor->move(&command);
  }

  actor->update();
}

void TestMovement::draw()
{
  actor->draw();
}

#endif
