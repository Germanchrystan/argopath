#include <stdio.h>
#include "pannels.h"
#include "constants.h"
#include "raygui.h"

void pannelSceneSelectInit(Pannel *pannel)
{
  pannel->rect = (Rectangle){ 0, 0, WINDOW_WIDTH / 12, WINDOW_HEIGHT / 6 };
}

void pannelSceneSelectUpdate(Pannel *pannel)
{
  (void)pannel;
}

void pannelSceneSelectDraw(Pannel *pannel)
{
  DrawRectangleRec(pannel->rect, COLOR_4);

  if(GuiDropdownBox((Rectangle) {15, 15, 96, 32}, "OPTION1;OPTION2", &pannel->state->sceneSelect.scene, pannel->state->sceneSelect.openDropdown))
  {
    printf("Dropdown option selected: %d\n", pannel->state->sceneSelect.scene);
    pannel->state->sceneSelect.openDropdown = !pannel->state->sceneSelect.openDropdown;
    // saveLevel(MANAGER.level, MANAGER.fileName);
  }
}

Pannel pannelSceneSelect = (Pannel){
  .rect = (Rectangle){ 0, 0, 0, 30 },
  .state = &(PannelState){ .sceneSelect = (StateSceneSelect){ .scene = 0, .openDropdown = false } },
  .init = pannelSceneSelectInit,
  .update = pannelSceneSelectUpdate,
  .draw = pannelSceneSelectDraw
};