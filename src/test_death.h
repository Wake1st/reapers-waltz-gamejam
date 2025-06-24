#ifndef TEST_DEATH
#define TEST_DEATH

#include <iostream>
#include "raylib.h"

#include "game_state.h"
#include "input.h"
#include "actor.h"
#include "trap.h"

#define TEST_TRAP_COUNT 2
#define ACTOR_START (4 + 10 * MAP_WIDTH)

typedef struct TestDeathResources
{
  Texture2D playerTexture;
  Texture2D crushyStoneCleanTexture;
  Texture2D crushyStoneBloodTexture;
  Sound crush;
  Texture2D spikeOpenedTexture;
  Texture2D spikeClosedTexture;
  Sound spike;
} TestDeathResources;

class TestDeath
{
public:
  TestDeath(TestDeathResources res)
  {
    input = new InputHandler();
    actor = new Actor(res.playerTexture, ACTOR_START);

    traps[0] = new CrushTrap(res.crushyStoneCleanTexture, res.crushyStoneBloodTexture, res.crush, 4 + 4 * MAP_WIDTH);
    traps[1] = new SpikeTrap(res.spikeOpenedTexture, res.spikeClosedTexture, res.spike, 8 + 4 * MAP_WIDTH);
  }

  void update();
  void draw();

private:
  InputHandler *input;
  Actor *actor;

  Trap *traps[TEST_TRAP_COUNT];
};

void TestDeath::update()
{
  if (GameState::active == GameStates::LOOSE)
  {
    // create new actor
    actor->setCell(ACTOR_START);

    // reset traps
    for (int i = 0; i < TEST_TRAP_COUNT; i++)
    {
      traps[i]->activate(false);
    }

    // update state
    GameState::setState(GameStates::PLAY);
    actor->isFrozen = false;
  }
  else if (GameState::active == GameStates::PLAY)
  {
    Command command = input->handleInput();
    if (command && actor->canMove())
    {
      actor->move(&command);
    }

    // check for traps
    for (int i = 0; i < TEST_TRAP_COUNT; i++)
    {
      if (actor->currentCell == traps[i]->cell)
      {
        GameState::setState(GameStates::LOOSE);
        traps[i]->activate(true);
        actor->isFrozen = true;
      }
    }

    actor->update();
  }
}

void TestDeath::draw()
{
  actor->draw();

  for (int i = 0; i < TEST_TRAP_COUNT; i++)
  {
    traps[i]->draw();
  }
}

#endif
