#include "modals.h"
#include <stdlib.h>
#include <raylib.h>
#include "constants.h"
#include "box.h"

const int MODAL_WIDTH = 400;
const int MODAL_HEIGHT = 300;

void modalNewEntityInit(Box *box)
{
  Modal *modal = (Modal *)box;
  modal->base.rect = (Rectangle)
  { 
    WINDOW_WIDTH / 2 - MODAL_WIDTH / 2,
    WINDOW_HEIGHT / 2 - MODAL_HEIGHT / 2,
    MODAL_WIDTH,
    MODAL_HEIGHT 
  };

  if (modal->state.newEntity.entity != NULL)
  {
    free(modal->state.newEntity.entity);
  }
  Entity *newEntity = (Entity *)malloc(sizeof(Entity));
  modal->state.newEntity.entity = newEntity;
}

void modalNewEntityDraw(Box *box)
{
  Modal *modal = (Modal *)box;
  DrawRectangleRec(modal->base.rect, COLOR_3);
  DrawText("New Entity Modal", modal->base.rect.x + 20, modal->base.rect.y + 20, 16, COLOR_5);
}

Modal modalNewEntity = (Modal){
  .base = (Box){
    .init = modalNewEntityInit,
    .draw = modalNewEntityDraw,
  }
};