#include <stdlib.h>
#include <stdio.h>
#include "workview.h"
#include "pannels.h"
#include "modals.h"
#include "raygui.h"

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
    if (pannel->init != NULL)
    {
      pannel->init(pannel);
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
  modal->init(modal);
  ptr->modal = modal;
  ModalContainerX = modal->rect.x - MODAL_CONTAINER_PADDING;
  ModalContainerY = modal->rect.y - MODAL_CONTAINER_PADDING_HEADER;
  ModalContainerWidth = modal->rect.width + 2 * MODAL_CONTAINER_PADDING;
  ModalContainerHeight = modal->rect.height + MODAL_CONTAINER_PADDING_HEADER + MODAL_CONTAINER_PADDING;

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
    (Color){123, 43, 5, 128}
  );
  // Draw container button
  if (GuiButton((Rectangle) {
    ModalContainerButtonX,
    ModalContainerButtonY,
    ModalContainerButtonWidth,
    ModalContainerButtonHeight
  }, "#113#"))
  {
    closeModal();
    return;
  }

  ptr->modal->draw(WORKVIEW.modal);
}

void drawPannels()
{
  Pannel *pannel = WORKVIEW.pannel;
  while (pannel != NULL)
  {
    if (pannel->draw != NULL)
    {
      pannel->draw(pannel);
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
