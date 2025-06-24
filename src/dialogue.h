#ifndef DIALOGUE
#define DIALOGUE

#include <cmath>
#include "raylib.h"
#include "raymath.h"

#include "globals.h"

#define LERP_WEIGHT 0.28f
#define CLOSENESS 0.01

#define OPENED_HEIGHT 0.f
#define CLOSED_HEIGHT (SCREEN_HEIGHT + 100.f)

class Dialogue
{
public:
  Dialogue(Texture2D background)
  {
    texture = background;

    position.y = CLOSED_HEIGHT;
  }
  bool isOpened();
  void toggle(const char *text = "");
  void update();
  void draw();

private:
  Texture2D texture;
  const char *text;

  bool opened = false;
  bool active = false;
  bool animating = false;
  Vector2 position;
  float targetHeight;
};

bool Dialogue::isOpened()
{
  return opened;
}

void Dialogue::toggle(const char *dialogue)
{
  if (opened)
  {
    targetHeight = CLOSED_HEIGHT;
  }
  else
  {
    text = dialogue;
    targetHeight = OPENED_HEIGHT;
  }

  animating = true;
  active = true;
}

void Dialogue::update()
{
  if (animating)
  {
    position.y = Lerp(position.y, targetHeight, LERP_WEIGHT);

    // close enough to done
    if (abs(position.y - targetHeight) < CLOSENESS)
    {
      position.y = targetHeight;
      animating = false;

      // no need to display hidden textures
      active = position.y < SCREEN_HEIGHT;
      opened = position.y < SCREEN_HEIGHT;
    }
  }
}

void Dialogue::draw()
{
  if (active)
  {
    DrawTexture(texture, position.x, position.y, WHITE);

    if (opened && !animating)
      DrawText(text, SCREEN_WIDTH / 2.f - 400.f, 200.f, 60, RED);
  }
}

#endif
