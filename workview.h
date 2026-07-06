#pragma once

#include <raylib.h>
#include "grid.h"

typedef struct
{
  Grid grid;
} GridPannel;

typedef struct
{
  GridPosition *selectedGridPosition;
  GridPosition *hoveredGridPosition;
} Status;

typedef struct
{
  Status *status;
  
} WorkView;