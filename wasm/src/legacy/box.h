#pragma once
#include <raylib.h>

typedef struct Box Box;
typedef void (BoxMethod) (Box *box);


typedef struct Box
{
  BoxMethod *init;
  BoxMethod *draw;
  Rectangle rect;
} Box;