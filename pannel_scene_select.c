#include <stdio.h>
#include "pannels.h"
#include "raygui.h"

static float dropdownX;
static float dropdownY;
static float dropdownWidth;
static float dropdownHeight;

void pannelSceneSelectInit(Box *box)
{
  Pannel *pannel = (Pannel *)box;
  pannel->base.rect = (Rectangle){ 0, 0, PANNEL_WIDTH_1, PANNEL_HEIGHT_1 };
  dropdownWidth = pannel->base.rect.width - 2 * PANNEL_PADDING_1;
  dropdownHeight = 32.0f;

  dropdownX = PANNEL_PADDING_1;
  dropdownY = PANNEL_PADDING_1;
}

void pannelSceneSelectUpdate(Pannel *pannel)
{
  (void)pannel;
}

void pannelSceneSelectDraw(Box *box)
{
  Pannel *pannel = (Pannel *)box;
  DrawRectangleRec(pannel->base.rect, COLOR_4);

  if(GuiDropdownBox((Rectangle) {dropdownX, dropdownY, dropdownWidth, dropdownHeight}, "OPTION1;OPTION2", &pannel->state->sceneSelect.scene, pannel->state->sceneSelect.openDropdown))
  {
    printf("Dropdown option selected: %d\n", pannel->state->sceneSelect.scene);
    pannel->state->sceneSelect.openDropdown = !pannel->state->sceneSelect.openDropdown;
    // saveLevel(MANAGER.level, MANAGER.fileName);
  }
}

Pannel pannelSceneSelect = (Pannel){
  .base = (Box){
    .init = pannelSceneSelectInit,
    .draw = pannelSceneSelectDraw,
  },
  .state = &(PannelState){ .sceneSelect = (StateSceneSelect){ .scene = 0, .openDropdown = false } },
  .next = &pannelEntityPalette
};