#ifndef FLOORPLAN
#define FLOORPLAN

#include "raylib.h"

#include "globals.h"

#define ROOM_COUNT 24
#define ROOMS_PER_LEVEL 21

#define FS FLOOR_SCALE

typedef struct Floorplan
{
  Rectangle *rooms[ROOMS_PER_LEVEL];
} Floorplan;

typedef struct Floorplans
{
  static Floorplan *plans[LEVEL_COUNT];
} Floorplans;

Floorplan *Floorplans::plans[LEVEL_COUNT]{
    new (Floorplan){
      rooms : {
          new (Rectangle){FS * (OUTER_BUFFER + 0.f), FS *(OUTER_BUFFER + 0.f), FS * 6.f, FS * 6.f}, // room 1
          new (Rectangle){FS * (OUTER_BUFFER + 6.f), FS *(OUTER_BUFFER + 1.f), FS * 3.f, FS * 2.f}, // room 1

          new (Rectangle){FS * (OUTER_BUFFER + 9.f), FS *(OUTER_BUFFER + 1.f), FS * 10.f, FS * 7.f},  // room 2
          new (Rectangle){FS * (OUTER_BUFFER + 15.f), FS *(OUTER_BUFFER + 8.f), FS * 3.f, FS * 2.f},  // room 2
          new (Rectangle){FS * (OUTER_BUFFER + 15.f), FS *(OUTER_BUFFER + 10.f), FS * 8.f, FS * 2.f}, // room 2
          new (Rectangle){FS * (OUTER_BUFFER + 21.f), FS *(OUTER_BUFFER + 12.f), FS * 2.f, FS * 2.f}, // room 2

          new (Rectangle){FS * (OUTER_BUFFER + 18.f), FS *(OUTER_BUFFER + 14.f), FS * 8.f, FS * 5.f}, // room 3

          new (Rectangle){FS * (OUTER_BUFFER + 24.f), FS *(OUTER_BUFFER + 9.f), FS * 22.f, FS * 5.f},  // room 4
          new (Rectangle){FS * (OUTER_BUFFER + 36.f), FS *(OUTER_BUFFER + 0.f), FS * 10.f, FS * 14.f}, // room 4
          new (Rectangle){FS * (OUTER_BUFFER + 46.f), FS *(OUTER_BUFFER + 0.f), FS * 12.f, FS * 4.f},  // room 4
          new (Rectangle){FS * (OUTER_BUFFER + 52.f), FS *(OUTER_BUFFER + 4.f), FS * 5.f, FS * 3.f},   // room 4
          new (Rectangle){FS * (OUTER_BUFFER + 50.f), FS *(OUTER_BUFFER + 7.f), FS * 16.f, FS * 6.f},  // room 4

          new (Rectangle){FS * (OUTER_BUFFER + 30.f), FS *(OUTER_BUFFER + 14.f), FS * 4.f, FS * 7.f},   // room 5
          new (Rectangle){FS * (OUTER_BUFFER + 28.f), FS *(OUTER_BUFFER + 21.f), FS * 24.f, FS * 14.f}, // room 5
          new (Rectangle){FS * (OUTER_BUFFER + 20.f), FS *(OUTER_BUFFER + 35.f), FS * 38.f, FS * 20.f}, // room 5

          new (Rectangle){FS * (OUTER_BUFFER + 34.f), FS *(OUTER_BUFFER + 55.f), FS * 5.f, FS * 12.f},  // room 9
          new (Rectangle){FS * (OUTER_BUFFER + 30.f), FS *(OUTER_BUFFER + 67.f), FS * 32.f, FS * 18.f}, // room 9
          new (Rectangle){FS * (OUTER_BUFFER + 30.f), FS *(OUTER_BUFFER + 85.f), FS * 40.f, FS * 26.f}, // room 9

          new (Rectangle){FS * (OUTER_BUFFER + 70.f), FS *(OUTER_BUFFER + 90.f), FS * 18.f, FS * 7.f}, // room 11
          new (Rectangle){FS * (OUTER_BUFFER + 78.f), FS *(OUTER_BUFFER + 86.f), FS * 4.f, FS * 6.f},  // room 11
          new (Rectangle){FS * (OUTER_BUFFER + 78.f), FS *(OUTER_BUFFER + 82.f), FS * 90.f, FS * 4.f}, // room 11
      },
    },
};

// ROOM 1, 9, and 11 are needed

#endif
