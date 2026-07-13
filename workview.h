#pragma once

#include <raylib.h>
#include "pannels.h"
#include "modals.h"

typedef struct
{
  Modal *modal;
  Pannel *pannel;
} WorkView;

void initWorkView();
void drawWorkView();
void openModal(Modal *modal);
void closeModal();
