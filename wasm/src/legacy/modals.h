#pragma once

#include "box.h"
#include "entities.h"

typedef struct NewEntityModalState
{
  Entity *entity;
  char name[64];
  bool nameEditMode;
  bool createNewField;
  int openDropdownIndex;
} NewEntityModalState;

typedef union ModalState
{
  NewEntityModalState entityState;
} ModalState;

typedef struct Modal
{
  Box base;
  ModalState state;
} Modal;

extern Modal modalStart;
extern Modal modalNewEntity;