#pragma once

#include <raylib.h>
#include "constants.h"
#include "grid.h"
#include "box.h"

extern float PANNEL_PADDING_1;
extern float PANNEL_HEIGHT_1;
extern float PANNEL_HEIGHT_2;
extern float PANNEL_HEIGHT_3;
extern float PANNEL_WIDTH_1;

typedef struct Pannel Pannel;

void initPannelConstants(void);

typedef struct StateSceneSelect 
{
  int scene;
  bool openDropdown;
} StateSceneSelect;

typedef struct StateEntityPalette
{
  int selectedButton;
} StateEntityPalette;

typedef struct StateGridEdit
{
  Grid *grid;
} StateGridEdit;

typedef union PannelState
{
  StateEntityPalette entityPalette;
  StateSceneSelect sceneSelect;
  StateGridEdit gridEdit;
} PannelState;

typedef struct Pannel
{
  Box base;
  PannelState *state;
  Pannel *next;
} Pannel;

extern Pannel pannelSceneSelect; // FIRST PANNEL
extern Pannel pannelEntityPalette;
extern Pannel pannelGridEdit;
