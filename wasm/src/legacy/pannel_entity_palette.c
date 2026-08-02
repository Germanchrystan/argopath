#include <stdlib.h>
#include <raylib.h>
#include "raygui.h"
#include "pannels.h"
#include "workview.h"
#include "modals.h"

static float buttonsY;
static float buttonsX;
static float buttonWidth;
static float buttonHeight;

void pannelEntityPaletteInit(Box *box)
{
  Pannel *pannel = (Pannel *)box;
  pannel->base.rect = (Rectangle){
		0,
		PANNEL_HEIGHT_1,
		PANNEL_WIDTH_1,
		WINDOW_HEIGHT - PANNEL_HEIGHT_1
  };

  buttonsX = pannel->base.rect.x + PANNEL_PADDING_1;
  buttonsY = pannel->base.rect.y + PANNEL_PADDING_1;
  // TODO: FIXED DIMENSIONS FOR NOW
  buttonWidth = 32.0f;
  buttonHeight = 32.0f;
}

void drawPalettePannel(Box *box)
{
  Pannel *pannel = (Pannel *)box;
  DrawRectangleRec(pannel->base.rect, COLOR_2);

  if (pannel == NULL)
  {
    return;
  }

  // TODO: Stop using magic numbers
  int previousGuiState = GuiGetState();

  if (pannel->state->entityPalette.selectedButton == 0)
  {
    GuiSetState(STATE_DISABLED);
  }
  if (GuiButton((Rectangle) {buttonsX, buttonsY, buttonWidth, buttonHeight}, "#21#"))
  {
    pannel->state->entityPalette.selectedButton = 0;
    // MODE_EDIT.mouseGridInput = SelectCell;
  }
  GuiSetState(previousGuiState);

  if (pannel->state->entityPalette.selectedButton == 1)
  {
    GuiSetState(STATE_DISABLED);
  }
  if (GuiButton((Rectangle) {buttonsX + buttonWidth, buttonsY, buttonWidth, buttonHeight}, "#22#"))
  {
    pannel->state->entityPalette.selectedButton = 1;
    // MODE_EDIT.mouseGridInput = AddSolidCell;
  }
  GuiSetState(previousGuiState);

  if (pannel->state->entityPalette.selectedButton == 2)
  {
    GuiSetState(STATE_DISABLED);
  }
  if (GuiButton((Rectangle) {buttonsX + 2 * buttonWidth, buttonsY, buttonWidth, buttonHeight}, "#28#"))
  {
    pannel->state->entityPalette.selectedButton = 2;
    // MODE_EDIT.mouseGridInput = RemoveSolidCell;
  }
  GuiSetState(previousGuiState);

  // Create new Entity
  if (GuiButton((Rectangle) {buttonsX, buttonsY + buttonHeight, buttonWidth * 3, buttonHeight}, "Create new"))
  {
    openModal(&modalNewEntity);
  }
}

Pannel pannelEntityPalette = (Pannel){
  .state = &(PannelState){ .entityPalette = (StateEntityPalette){ .selectedButton = 0 } },
  .base = (Box){
    .init = pannelEntityPaletteInit,
    .draw = drawPalettePannel,
  },
  .next = &pannelGridEdit,
};