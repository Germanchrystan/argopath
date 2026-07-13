#include <stdlib.h>
#include <stdio.h>
#include "workview.h"
#include "pannels.h"
#include "modals.h"
#include "raygui.h"
#include "constants.h"

static WorkView *ptr = &WORKVIEW;
static int MODAL_CONTAINER_PADDING_HEADER = 32;
static int MODAL_CONTAINER_PADDING = 4;
static int MODAL_CONTAINER_BUTTON_SIZE = 16;

static int ModalContainerX;
static int ModalContainerY;
static int ModalContainerWidth;
static int ModalContainerHeight;

static int ModalContainerButtonX;
static int ModalContainerButtonY;
static int ModalContainerButtonWidth;
static int ModalContainerButtonHeight;

void initWorkView()
{
  WorkView *ptr = &WORKVIEW;
  ptr->modal = NULL;
  Pannel *pannel = &pannelSceneSelect;
  ptr->pannel = pannel;

  while (pannel != NULL)
  {
    if (pannel->base.init != NULL)
    {
      pannel->base.init((Box *)pannel);
    }
    pannel = pannel->next;
  }
}

void openModal(Modal *modal)
{
  if (ptr->modal != NULL)
  {
    fprintf(stderr, "Error opening modal");
    return;
  }
  modal->base.init((Box *)modal);
  ptr->modal = modal;
  
  ModalContainerX = modal->base.rect.x - MODAL_CONTAINER_PADDING;
  ModalContainerY = modal->base.rect.y - MODAL_CONTAINER_PADDING_HEADER;
  ModalContainerWidth = modal->base.rect.width + 2 * MODAL_CONTAINER_PADDING;
  ModalContainerHeight = modal->base.rect.height + MODAL_CONTAINER_PADDING_HEADER + MODAL_CONTAINER_PADDING;

  ModalContainerButtonX = ModalContainerX + ModalContainerWidth - MODAL_CONTAINER_BUTTON_SIZE - MODAL_CONTAINER_PADDING;
  ModalContainerButtonY = ModalContainerY + MODAL_CONTAINER_PADDING;
  ModalContainerButtonWidth = MODAL_CONTAINER_BUTTON_SIZE;
  ModalContainerButtonHeight = MODAL_CONTAINER_BUTTON_SIZE;
}

void closeModal()
{
  if (ptr->modal == NULL)
  {
    fprintf(stderr, "Error closing modal");
    return;
  }
  ptr->modal = NULL;
}

static void drawModal()
{
  Modal *modal = ptr->modal;
  DrawRectangle(
    ModalContainerX,
    ModalContainerY,
    ModalContainerWidth,
    ModalContainerHeight,
    COLOR_5
  );
  // Draw container button
  if (GuiButton((Rectangle) {
    ModalContainerButtonX,
    ModalContainerButtonY,
    ModalContainerButtonWidth,
    ModalContainerButtonHeight
  }, CLOSE_ICON))
  {
    closeModal();
    return;
  }

  ptr->modal->base.draw((Box *)WORKVIEW.modal);
}

void drawPannels()
{
  Pannel *pannel = WORKVIEW.pannel;
  while (pannel != NULL)
  {
    if (pannel->base.draw != NULL)
    {
      pannel->base.draw((Box *)pannel);
    }
    pannel = pannel->next;
  }
}

void drawWorkView()
{
  if (WORKVIEW.modal == NULL)
  {
    drawPannels();
    return;
  }

  GuiLock();
  drawPannels();
  GuiUnlock();
  drawModal();
}
