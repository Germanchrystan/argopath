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
  char *string;
  bool boolean;
  int number;
  int dropdownIndex;
  Vector2 vector2;
  Rectangle rect;
  Color color;
} EntityFieldValue;

typedef struct EntityField
{
  char *name;
  EntityFieldType type;
  EntityFieldValue value;
} EntityField;

typedef struct Entity
{
  int fieldCount;
  char *name;
  EntitySprite *sprite;
  EntityField *fields;
  Color *color;
} Entity;

typedef struct EntityInstance
{
  Entity *entity;
  GridPosition position;
} EntityInstance;

void entityInit(Entity *entity);
void entityAddField(Entity *entity, const char *name, EntityFieldType type, EntityFieldValue value);
void entityRemoveField(Entity *entity, const int index);
void entityFree(Entity *entity);