#include <stdio.h>
#include <stdlib.h>
#include <raylib.h>
#include <string.h>

#include "macos_presentation.h"
#include "constants.h"
#include "pannels.h"
#include "workview.h"

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
  fprintf(stderr, "Current monitor: %d\n", monitor);
  if (monitor < 0)
  {
    fprintf(stderr, "Failed to get current monitor\n");
    WINDOW_WIDTH = GetScreenWidth();
    WINDOW_HEIGHT = GetScreenHeight();
  }
  else
  {
    WINDOW_WIDTH = GetMonitorWidth(0);
    WINDOW_HEIGHT = GetMonitorHeight(0);
  }

  // Maybe check if the window is larger than the monitor and resize it if so
  SetWindowPosition(0, 0);
  SetWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
  
  initPannelConstants();
  
  enableMacOSKioskPresentation(); // MACOS
  SetTargetFPS(60);
  
  fprintf(stderr, "Monitor width: %d, height: %d\n", GetMonitorWidth(monitor), GetMonitorHeight(monitor));
  initWorkView();
  fprintf(stderr, "Work view initialized\n");
  
  float dt;
  while (!WindowShouldClose())
  {
    // Update
    dt = GetFrameTime();

    // Draw
    BeginDrawing();
    ClearBackground(COLOR_5);
    drawWorkView();
    EndDrawing();
  }

  // free(levelFileLocation);
  disableMacOSKioskPresentation(); // MACOS
  CloseWindow();
  return 0;
}