#ifndef ACTOR
#define ACTOR

#include <iostream>
#include <cmath>
#include "raylib.h"
#include "raymath.h"

#include "globals.h"

#define SPEED 135.f

#define FRAME_SPEED 4
#define FRAMES 4
#define LAYERS 4

class Actor
{
public:
  bool isMoving;
  bool isFrozen;
  int currentCell;
  Vector2 position;

  Actor(Texture2D text, int startCell, float spd = SPEED)
  {
    isMoving = false;
    currentCell = startCell;
    speed = spd;

    texture = text;
    offset = {24.f, 80.f};

    position = PositionOfCell(startCell);
    frameRec = {0.0f, 0.0f, (float)texture.width / FRAMES, (float)texture.height / LAYERS};
    currentFrame = 0;
    currentLayer = 1;
    framesCounter = 0;
    framesSpeed = FRAME_SPEED;
  }
  void update();
  void setCell(int cell);
  void setTexture(Texture2D text);
  void move(Command *command);
  bool canMove();
  void draw();
  void draw2D();

private:
  Texture2D texture;
  Vector2 offset;
  float speed;

  Rectangle frameRec;
  int currentLayer;
  int currentFrame;
  int framesCounter;
  int framesSpeed;

  void animate();
};

void Actor::update()
{
  // stand still when motionless
  Actor::animate();

  // reset for next frame
  isMoving = false;
}

void Actor::setCell(int cell)
{
  currentCell = cell;
  position = PositionOfCell(cell);
}

void Actor::setTexture(Texture2D text)
{
  texture = text;
}

void Actor::move(Command *command)
{
  // we are now in motion
  isMoving = true;

  // update position
  Vector2 direction = (Vector2){0.f, 0.f};
  switch (*command)
  {
  case Command::N:
    direction += (Vector2){0.f, -1.f};
    currentLayer = 3;
    break;
  case Command::NE:
    direction += (Vector2){DIAGONAL, -DIAGONAL};
    currentLayer = 3;
    break;
  case Command::E:
    direction += (Vector2){1.f, 0.f};
    currentLayer = 2;
    break;
  case Command::SE:
    direction += (Vector2){DIAGONAL, DIAGONAL};
    currentLayer = 0;
    break;
  case Command::S:
    direction += (Vector2){0.f, 1.f};
    currentLayer = 0;
    break;
  case Command::SW:
    direction += (Vector2){-DIAGONAL, DIAGONAL};
    currentLayer = 0;
    break;
  case Command::W:
    direction += (Vector2){-1.f, 0.f};
    currentLayer = 1;
    break;
  case Command::NW:
    direction += (Vector2){-DIAGONAL, -DIAGONAL};
    currentLayer = 3;
    break;
  default:
    return;
  }

  position += Vector2Scale(direction, speed * GetFrameTime());
  // printf(TextFormat("\tpos x: %f\tpos y: %f\tcurrent cell: %i", position.x, position.y, currentCell));

  // update current cell
  Vector2 center = {(position.x + HALF_CELL), (position.y + HALF_CELL)};
  currentCell = (int)floor(center.x / CELL_SIZE) + (int)floor(center.y / CELL_SIZE) * MAP_WIDTH;
}

void Actor::draw()
{
  DrawText(TextFormat("pos x: %f\tpos y: %f\tcurrent cell: %i", position.x, position.y, currentCell), 20, 20, 40, WHITE);

  DrawRectangleLines(position.x, position.y, CELL_SIZE, CELL_SIZE, LIME);
}

void Actor::draw2D()
{
  DrawTextureRec(texture, frameRec, position - offset, WHITE);
}

void Actor::animate()
{
  // only animate when in motion
  if (isMoving)
  {
    // move with the flow
    framesCounter++;
    if (framesCounter >= (FRAME_RATE / framesSpeed))
    {
      currentFrame++;
      framesCounter = 0;
      if (currentFrame >= FRAMES)
      {
        currentFrame = 0;
      }
    }
  }
  else
  {
    currentFrame = 0;
  }

  // anways update animation rect
  frameRec.x = (float)currentFrame * (float)texture.width / FRAMES;
  frameRec.y = (float)currentLayer * (float)texture.height / LAYERS;
}

bool Actor::canMove()
{
  return !isFrozen;
}

#endif
