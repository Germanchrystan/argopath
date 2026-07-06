#include <raylib.h>

typedef struct Pannel Pannel;
typedef void (PannelMethod) (Pannel *pannel);

typedef struct StateSceneSelect 
{
  int scene;
  bool openDropdown;
} StateSceneSelect;

typedef union PannelState
{
  StateSceneSelect sceneSelect;
} PannelState;

typedef struct Pannel
{
  Rectangle rect;
  PannelState *state;
  PannelMethod *init;
  PannelMethod *update;
  PannelMethod *draw;
} Pannel;

extern Pannel pannelSceneSelect;
extern Pannel pannelEntity;