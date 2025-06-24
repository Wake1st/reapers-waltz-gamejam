#ifndef TEST_ENEMY
#define TEST_ENEMY

#include <vector>
#include "raylib.h"

#include "globals.h"
#include "game_state.h"
#include "enemy.h"

typedef struct TestEnemyResources
{
  Texture2D docileTexture;
  Texture2D hostileTexture;
  Texture2D playerTexture;
} TestEnemyResources;

class TestEnemy
{
public:
  TestEnemy(TestEnemyResources res)
  {
    std::vector<int> points = {
        7 + 5 * MAP_WIDTH,
        10 + 7 * MAP_WIDTH,
        10 + 9 * MAP_WIDTH,
        7 + 11 * MAP_WIDTH,
        5 + 11 * MAP_WIDTH,
        2 + 9 * MAP_WIDTH,
        2 + 7 * MAP_WIDTH,
        5 + 5 * MAP_WIDTH,
    };
    enemy = new Enemy(res.docileTexture, res.hostileTexture, 5 + 5 * MAP_WIDTH, points);

    input = new InputHandler();
    player = new Actor(res.playerTexture, 18 + 26 * MAP_WIDTH);
  }
  void update();
  void draw();

private:
  Enemy *enemy;

  InputHandler *input;
  Actor *player;
};

void TestEnemy::update()
{
  if (GameState::active == GameStates::LOOSE)
  {
    // reset actors
    player->setCell(18 + 26 * MAP_WIDTH);
    enemy->setCell(5 + 5 * MAP_WIDTH);

    // update state
    GameState::setState(GameStates::PLAY);
    player->isFrozen = false;
  }
  else if (GameState::active == GameStates::PLAY)
  {
    // move the player
    Command command = input->handleInput();
    if (command)
    {
      player->move(&command);
    }

    // check for death or detection
    if (enemy->inPursuit())
    {
      if (enemy->checkCaught())
      {
        GameState::active = GameStates::LOOSE;
        player->isFrozen = true;
      }
      else if (!enemy->checkPursuit(player))
      {
        enemy->setState(EnemyState::IDLE);
      }
    }
    else
    {
      enemy->checkPursuit(player);
    }

    player->update();
  }

  enemy->update();
}

void TestEnemy::draw()
{
  player->draw();
  enemy->draw();
}

#endif
