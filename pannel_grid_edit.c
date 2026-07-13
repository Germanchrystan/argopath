#include "pannels.h"
#include "raygui.h"
#include "grid.h"
#include <stdlib.h>

static int VISIBLE_CELL_ROWS = 100;
static int VISIBLE_CELL_COLUMNS = 100;
static int CELL_SIZE = 32;
static int GRID_PANNEL_LEFT_MARGIN;

void getCellSize(Pannel *pannel)
{
  float cellSizeHeight = pannel->rect.height / VISIBLE_CELL_ROWS;
  float cellSizeWidth = pannel->rect.width / VISIBLE_CELL_COLUMNS;
  CELL_SIZE = (int)(cellSizeHeight < cellSizeWidth ? cellSizeHeight : cellSizeWidth);
}

void pannelGridEditInit(Pannel *pannel)
{
  pannel->rect = (Rectangle){
    PANNEL_WIDTH_1,
    0,
    WINDOW_WIDTH - PANNEL_WIDTH_1,
    WINDOW_HEIGHT - PANNEL_HEIGHT_1
  };
  GRID_PANNEL_LEFT_MARGIN = pannel->rect.x;
  pannel->state->gridEdit.grid = (Grid *)malloc(sizeof(Grid));
  pannel->state->gridEdit.grid->rows = VISIBLE_CELL_ROWS;
  pannel->state->gridEdit.grid->cols = VISIBLE_CELL_COLUMNS;
  getCellSize(pannel);
}

void drawGridPannel(Pannel *gridPannel)
{
  // Grid *grid = &screen->grid;

  for (int row = 0; row < VISIBLE_CELL_ROWS; ++row)
  {
    for (int col = 0; col < VISIBLE_CELL_COLUMNS; ++col)
    {
      DrawRectangle(
          GRID_PANNEL_LEFT_MARGIN + col * CELL_SIZE,
          row * CELL_SIZE,
          CELL_SIZE - 1,
          CELL_SIZE - 1,
          GRAY);
    }
  }

  // Draw Gizmos
}

Pannel pannelGridEdit = (Pannel){
  .state = &(PannelState){ .gridEdit = (StateGridEdit){ .grid = NULL } },
  .init = pannelGridEditInit,
  .draw = drawGridPannel,
  .next = NULL
};