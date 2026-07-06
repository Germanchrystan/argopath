#pragma once
#include <raylib.h>
#include "grid.h"

typedef enum EntityFieldType
{
  ENTITY_TYPE_NONE,
  ENTITY_TYPE_NUMBER,
  ENTITY_TYPE_STRING,
  ENTITY_TYPE_BOOL,
  ENTITY_TYPE_VECTOR2,
  ENTITY_TYPE_RECT,
  ENTITY_TYPE_COLOR,
  ENTITY_TYPE_DROPDOWN,
  ENTITY_TYPE_LENGTH,
} EntityFieldType;

typedef struct EntitySprite
{
  Rectangle rect;
  Texture2D *texture;
} EntitySprite;

typedef union EntityFieldValue
{
  int number;
  char *string;
  bool boolean;
  Vector2 vector2;
  Rectangle rect;
  Color color;
  int dropdownIndex;
} EntityFieldValue;

typedef struct EntityField
{
  EntityFieldType type;
  EntityFieldValue value;
} EntityField;

typedef struct Entity
{
  EntitySprite *sprite;
  char *name;
  EntityField *fields;
  int fieldCount;
} Entity;

typedef struct EntityInstance
{
  Entity *entity;
  GridPosition position;
} EntityInstance;