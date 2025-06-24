#ifndef LEVEL
#define LEVEL

#include <iostream>
#include "raylib.h"

#include "globals.h"
#include "game_state.h"
#include "death.h"
#include "collision.h"
#include "input.h"
#include "actor.h"
#include "map.h"
#include "trap.h"
#include "enemy.h"
#include "dialogue.h"
#include "interactable.h"

#define TRAP_COUNT 10
#define DIALOGUE_COUNT 7
#define ENEMY_COUNT 2
#define SOUND_COUNT 4

#define OB OUTER_BUFFER

typedef struct LevelResources
{
  Texture2D playerTexture;
  int startCell;

  Texture2D enemyBlueNTexture;
  Texture2D enemyBlueHTexture;
  Texture2D enemyPinkNTexture;
  Texture2D enemyPinkHTexture;

  Texture2D crushyStoneCleanTexture;
  Texture2D crushyStoneBloodTexture;
  Texture2D spikesEmptyTexture;
  Texture2D spikesHalfTexture;
  Texture2D spikesFullTexture;
  Texture2D baseDoorTexture;

  Sound footsteps;
  Sound crushed;
  Sound spiked;
  Sound caught;

  MapResources mapRes;

  Texture2D dialogueBackground;

} LevelResources;

class Level
{
public:
  Level(LevelResources res)
  {
    input = new InputHandler();
    player = new Actor(res.playerTexture, res.startCell);
    startCell = res.startCell;

    map = new Map(res.mapRes);

    traps[0] = new CrushTrap(res.crushyStoneCleanTexture, res.crushyStoneBloodTexture, res.crushed, FS * (OB + 30 + (OB + 19) * MAP_WIDTH));
    traps[1] = new CrushTrap(res.crushyStoneCleanTexture, res.crushyStoneBloodTexture, res.crushed, FS * (OB + 40 + (OB + 8) * MAP_WIDTH));
    traps[2] = new CrushTrap(res.crushyStoneCleanTexture, res.crushyStoneBloodTexture, res.crushed, FS * (OB + 32 + (OB + 13) * MAP_WIDTH));
    traps[3] = new CrushTrap(res.crushyStoneCleanTexture, res.crushyStoneBloodTexture, res.crushed, FS * (OB + 31 + (OB + 11) * MAP_WIDTH));
    traps[4] = new CrushTrap(res.crushyStoneCleanTexture, res.crushyStoneBloodTexture, res.crushed, FS * (OB + 58 + (OB + 10) * MAP_WIDTH));

    traps[5] = new SpikeTrap(res.spikesEmptyTexture, res.spikesFullTexture, res.spiked, FS * (OB + 34 + (OB + 26) * MAP_WIDTH));
    traps[6] = new SpikeTrap(res.spikesEmptyTexture, res.spikesFullTexture, res.spiked, FS * (OB + 41 + (OB + 24) * MAP_WIDTH));
    traps[7] = new SpikeTrap(res.spikesEmptyTexture, res.spikesFullTexture, res.spiked, FS * (OB + 32 + (OB + 30) * MAP_WIDTH));
    traps[8] = new SpikeTrap(res.spikesEmptyTexture, res.spikesFullTexture, res.spiked, FS * (OB + 28 + (OB + 46) * MAP_WIDTH));
    traps[9] = new SpikeTrap(res.spikesEmptyTexture, res.spikesFullTexture, res.spiked, FS * (OB + 50 + (OB + 38) * MAP_WIDTH));

    std::vector<int> points1 = {
        (int)(FS * (OB + 36 + (OB + 27) * MAP_WIDTH)),
        (int)(FS * (OB + 44 + (OB + 25) * MAP_WIDTH)),
    };
    enemies[0] = new Enemy(res.enemyBlueNTexture, res.enemyBlueHTexture, (int)(FS * (OB + 36 + (OB + 27) * MAP_WIDTH)), points1);

    std::vector<int> points2 = {
        (int)(FS * (OB + 30 + (OB + 48) * MAP_WIDTH)),
        (int)(FS * (OB + 50 + (OB + 53) * MAP_WIDTH)),
    };
    enemies[1] = new Enemy(res.enemyPinkNTexture, res.enemyPinkHTexture, (int)(FS * (OB + 40 + (OB + 50) * MAP_WIDTH)), points2);

    dialogue = new Dialogue(res.dialogueBackground);

    orbs[0] = new Interactable(FS * (OB + 5 + (OB + 1) * MAP_WIDTH), "Interaction tutorials!");
    orbs[1] = new Interactable(FS * (OB + 14 + (OB + 4) * MAP_WIDTH), "Dear Diary, We're fucked.");
    orbs[2] = new Interactable(FS * (OB + 24 + (OB + 17) * MAP_WIDTH), "I'm the death god - I hope you suffer.");
    orbs[3] = new Interactable(FS * (OB + 40 + (OB + 12) * MAP_WIDTH), "Dear Diary, I hope I don't get crushed.");
    orbs[4] = new Interactable(FS * (OB + 36 + (OB + 25) * MAP_WIDTH), "I can't find the end...");
    orbs[5] = new Interactable(FS * (OB + 66 + (OB + 100) * MAP_WIDTH), "WELCOME TO THE PIT!!");
    orbs[6] = new Interactable(FS * (OB + 80 + (OB + 94) * MAP_WIDTH), "ITS NOT FAIR ITS NOT FAIR");

    sounds[0] = res.footsteps;
    sounds[1] = res.crushed;
    sounds[2] = res.spiked;
    sounds[3] = res.caught;
  }
  void update();
  void draw();
  void draw2D();

  Vector2 getPlayerPosition();

private:
  InputHandler *input;
  Actor *player;
  int startCell;

  Map *map;

  Trap *traps[TRAP_COUNT];
  Enemy *enemies[ENEMY_COUNT];

  Dialogue *dialogue;
  Interactable *orbs[DIALOGUE_COUNT];

  Sound sounds[SOUND_COUNT];

  void play(Command command);
  void death();
};

Vector2 Level::getPlayerPosition()
{
  return player->position;
}

void Level::update()
{
  //  check win condition
  if (Death::allDead())
  {
    // open the door
    printf("\n\n - - exit the game - - \n\n");
  }

  Command command = input->handleInput();

  switch (GameState::active)
  {
  case GameStates::START:
  {

    break;
  }
  case GameStates::INTRO:
  {

    break;
  }
  case GameStates::SETUP:
  {

    break;
  }
  case GameStates::PLAY:
  {
    Level::play(command);
    break;
  }
  case GameStates::PAUSE:
  {

    break;
  }
  case GameStates::LOOSE:
  {
    Level::death();
    break;
  }
  case GameStates::FINALE:
  {

    break;
  }
  case GameStates::OUTRO:
  {

    break;
  }
  case GameStates::END:
  {

    break;
  }
  }

  // check for dialogues
  for (Interactable *orb : orbs)
  {
    if (orb->checkActive(player->currentCell) && command == Command::ACTION)
    {
      const char *text = orb->getText();
      dialogue->toggle(text);

      if (dialogue->isOpened())
      {
        GameState::setState(GameStates::PLAY);
        printf("we're opened");
      }
      else
      {
        GameState::setState(GameStates::PAUSE);
        printf("we're opened");
      }
    }
  }

  for (Enemy *enemy : enemies)
  {
    enemy->update();
  }

  for (Trap *trap : traps)
  {
    trap->update();
  }

  dialogue->update();
}

void Level::draw2D()
{
  map->draw2D();

  for (Interactable *orb : orbs)
  {
    orb->draw2D();
  }

  player->draw2D();

  for (Enemy *enemy : enemies)
  {
    enemy->draw2D();
  }

  for (int i = 0; i < TRAP_COUNT; i++)
  {
    traps[i]->draw2D();
    traps[i]->draw();
  }
}

void Level::draw()
{
  for (Interactable *orb : orbs)
  {
    orb->draw();
  }

  dialogue->draw();
}

void Level::play(Command command)
{
  // move player
  if (command)
  {
    // check for collisions
    bool hasCollided = Collision::check(&command, player->position, map->getNeighbors(player->currentCell));
    // printf(TextFormat("\nplayer | collided: %i\tcan move: %i", hasCollided, player->canMove()));
    if (!hasCollided && player->canMove())
    {
      player->move(&command);
      PlaySound(sounds[0]);
    }
  }

  // check enemies
  for (Enemy *enemy : enemies)
  {
    if (enemy->inPursuit())
    {
      if (enemy->checkCaught())
      {
        GameState::active = GameStates::LOOSE;
        Death::add(DeathTypes::CAUGHT);
        player->isFrozen = true;
        PlaySound(sounds[3]);
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
  }

  // check for traps
  for (int i = 0; i < TRAP_COUNT; i++)
  {
    if (player->currentCell == traps[i]->cell)
    {
      // update level
      GameState::setState(GameStates::LOOSE);
      traps[i]->activate(true);
      player->isFrozen = true;
    }
  }

  // final update for animations
  player->update();
}

void Level::death()
{
  // reset player
  player->setCell(startCell);

  // reset traps
  for (int i = 0; i < TRAP_COUNT; i++)
  {
    traps[i]->activate(false);
  }

  // update state
  GameState::setState(GameStates::PLAY);
  player->isFrozen = false;
}

#endif
