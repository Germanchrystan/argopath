#pragma once

#include "box.h"
#include "entities.h"

typedef struct NewEntityModalState
{
  Entity *entity;
} NewEntityModalState;

typedef union ModalState
{
  NewEntityModalState newEntity;
} ModalState;

typedef struct Modal
{
  Box base;
  ModalState state;
} Modal;

extern Modal modalStart;
extern Modal modalNewEntity;