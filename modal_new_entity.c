#include "modals.h"
#include <stdlib.h>
#include <raylib.h>

const int MODAL_WIDTH = 400;
const int MODAL_HEIGHT = 300;

void modalNewEntityInit(Modal *modal)
{
  modal->rect = (Rectangle)
  { 
    WINDOW_WIDTH / 2 - MODAL_WIDTH / 2,
    WINDOW_HEIGHT / 2 - MODAL_HEIGHT / 2,
    MODAL_WIDTH,
    MODAL_HEIGHT 
  };
  modal->state = NULL;
  modal->next = NULL; // Next is not necessary in Modal
}

void modalNewEntityDraw(Modal *modal)
{
  DrawRectangleRec(modal->rect, COLOR_3);
  DrawText("New Entity Modal", modal->rect.x + 20, modal->rect.y + 20, 20, COLOR_1);
}

Modal modalNewEntity = (Modal){
  .rect = (Rectangle){ 0, 0, MODAL_WIDTH, MODAL_HEIGHT },
  .state = NULL,
  .init = modalNewEntityInit,
  .draw = modalNewEntityDraw,
  .next = NULL
};