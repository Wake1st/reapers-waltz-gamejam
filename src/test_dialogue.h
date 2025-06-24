#ifndef TEST_DIALOGUE
#define TEST_DIALOGUE

#include "raylib.h"

#include "globals.h"
#include "game_state.h"
#include "input.h"
#include "actor.h"
#include "dialogue.h"
#include "interactable.h"

#define TEST_DIALOGUE_COUNT 2

typedef struct TestDialogueResources
{
  Texture2D playerTexture;
  Texture2D background;
} TestDialogueResources;

class TestDialogue
{
public:
  TestDialogue(TestDialogueResources res)
  {
    input = new InputHandler();
    actor = new Actor(res.playerTexture, 20 + 14 * MAP_WIDTH);

    dialogue = new Dialogue(res.background);
    orbs[0] = new Interactable(16 + 10 * MAP_WIDTH, "This is orb 1!");
    orbs[1] = new Interactable(24 + 10 * MAP_WIDTH, "Twas the other orb!");
  }
  void update();
  void draw();

private:
  InputHandler *input;
  Actor *actor;

  Dialogue *dialogue;
  Interactable *orbs[TEST_DIALOGUE_COUNT];
};

void TestDialogue::update()
{
  Command command = input->handleInput();

  if (GameState::active == GameStates::PLAY)
  {
    // move player
    if (command)
    {
      actor->move(&command);
    }
    actor->update();
  }

  // check for dialogues
  for (Interactable *orb : orbs)
  {
    if (orb->checkActive(actor->currentCell) && command == Command::ACTION)
    {
      const char *text = orb->getText();
      dialogue->toggle(text);

      if (dialogue->isOpened())
        GameState::setState(GameStates::PLAY);
      else
        GameState::setState(GameStates::PAUSE);
    }
  }

  dialogue->update();
}

void TestDialogue::draw()
{
  for (Interactable *orb : orbs)
  {
    orb->draw2D();
  }

  actor->draw2D();
  dialogue->draw();
}

#endif
