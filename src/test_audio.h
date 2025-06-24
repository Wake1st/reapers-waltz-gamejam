#ifndef TEST_AUDIO
#define TEST_AUDIO

#include <iostream>
#include "raylib.h"

#define SOUND_COUNT 4

typedef struct TestAudioResources
{
  Sound crushed;
  Sound spiked;
  Sound death;
  Sound footsteps;
} TestAudioResources;

class TestAudio
{
public:
  TestAudio(TestAudioResources res)
  {
    crushed = res.crushed;
    spiked = res.spiked;
    death = res.death;
    footsteps = res.footsteps;
  }
  void update();
  void draw();

private:
  int index = 0;
  Sound crushed;
  Sound spiked;
  Sound death;
  Sound footsteps;
};

void TestAudio::update()
{
  if (IsKeyPressed(KEY_SPACE))
  {
    switch (index)
    {
    case 0:
      PlaySound(crushed);
      printf("\nplaying... crushed\t\t");
      break;
    case 1:
      PlaySound(spiked);
      printf("\nplaying... spiked\t\t");
      break;
    case 2:
      PlaySound(death);
      printf("\nplaying... death\t\t");
      break;
    case 3:
      PlaySound(footsteps);
      printf("\nplaying... footsteps\t\t");
      break;
    }
    index = (index + 1) % SOUND_COUNT;
  }
}

void TestAudio::draw()
{
  DrawText("Press space to loop through sounds.", 20, 10, 20, WHITE);
}

#endif
