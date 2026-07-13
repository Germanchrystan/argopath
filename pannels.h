#pragma once

#include <raylib.h>
#include "constants.h"
#include "grid.h"

extern float PANNEL_PADDING_1;
extern float PANNEL_HEIGHT_1;
extern float PANNEL_HEIGHT_2;
extern float PANNEL_HEIGHT_3;
extern float PANNEL_WIDTH_1;

typedef struct Pannel Pannel;

void initPannelConstants(void);

typedef void (PannelMethod) (Pannel *pannel);

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

// #ifndef Pannel
typedef struct Pannel
{
  Rectangle rect;
  PannelState *state;
  PannelMethod *init;
  PannelMethod *draw;
  Pannel *next;
} Pannel;
// #endif
extern Pannel pannelSceneSelect; // FIRST PANNEL
extern Pannel pannelEntityPalette;
extern Pannel pannelGridEdit;
