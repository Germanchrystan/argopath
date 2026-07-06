#include <stdio.h>
#include <stdlib.h>
#include <raylib.h>
#include <string.h>

#include "macos_presentation.h"
#include "constants.h"

#include "pannels.h"

int main(int args, char *argv[])
{
  // char *levelFileLocation = getLevelName(args, argv);
  // if (levelFileLocation == NULL)
  // {
  //   fprintf(stderr, "Failed to get level name\n");
  //   return 1;
  // }

  // SetConfigFlags(FLAG_WINDOW_UNDECORATED);
  InitWindow(1280, 720, "Pathfinder");

  int monitor = GetCurrentMonitor();
  WINDOW_WIDTH = GetMonitorWidth(0);
  WINDOW_HEIGHT = GetMonitorHeight(0);
  SetWindowPosition(0, 0);
  SetWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);

  WINDOW_WIDTH = GetScreenWidth();
  WINDOW_HEIGHT = GetScreenHeight();

  enableMacOSKioskPresentation(); // MACOS
  SetTargetFPS(60);
  pannelSceneSelect.init(&pannelSceneSelect);

  float dt;
  while (!WindowShouldClose())
  {
    // Update
    dt = GetFrameTime();

    // Draw
    BeginDrawing();
    ClearBackground(BLUE);
    pannelSceneSelect.draw(&pannelSceneSelect);
    EndDrawing();
  }

  // free(levelFileLocation);
  disableMacOSKioskPresentation(); // MACOS
  CloseWindow();
  return 0;
}