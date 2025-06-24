#ifndef GAME_STATE
#define GAME_STATE

typedef enum GameStates
{
  START,  // start menu
  INTRO,  // opening cinematic
  SETUP,  // initial setup
  PLAY,   // active playing
  PAUSE,  // pause menu
  LOOSE,  // death animations
  FINALE, // final sequence
  OUTRO,  // exiting cinematic?
  END,    // fin, credits
} GameSates;

class GameState
{
public:
  static GameStates active;

  static void setState(GameStates state)
  {
    active = state;
  }

private:
  GameState() = delete;
  ~GameState() = delete;
};

GameStates GameState::active = GameStates::PLAY;

#endif
