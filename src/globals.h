#ifndef GLOBALS
#define GLOBALS

#define SCREEN_WIDTH 1800
#define SCREEN_HEIGHT 850

#define FRAME_RATE 60

#define LEVEL_COUNT 1

#define FLOOR_SCALE 3
#define MAP_WIDTH 600
#define MAP_HEIGHT 400
#define MAP_SIZE (MAP_WIDTH * MAP_HEIGHT)

#define CELL_SIZE 32.f
#define HALF_CELL 16.f
#define OUTER_BUFFER 14.f

#define DIAGONAL 0.7071

typedef enum Command
{
  NONE,
  N,
  NE,
  E,
  SE,
  S,
  SW,
  W,
  NW,
  ACTION,
} Command;

Vector2 PositionOfCell(int cell)
{
  return {(cell % MAP_WIDTH) * CELL_SIZE, (cell / MAP_WIDTH) * CELL_SIZE};
}

#endif
