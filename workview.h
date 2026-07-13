#pragma once

#include <raylib.h>
#include "pannels.h"

typedef struct
{
  Pannel *modal;
  Pannel *pannel;
} WorkView;

void initWorkView();
void drawWorkView();
void openModal(Pannel *pannel);
void closeModal();

static WorkView WORKVIEW;