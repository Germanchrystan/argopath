#pragma once
#include <raylib.h>
#include "grid.h"

typedef enum FieldType
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
} FieldType;

#define ENTITY_FIELD_TYPE_NAMES { \
  "None", \
  "Number", \
  "String", \
  "Bool", \
  "Vector2", \
  "Rect", \
  "Color", \
  "Dropdown" \
}

#define ENTITY_FIELD_TYPE_NAMES_DROPDOWN \
  "Number;" \
  "String;" \
  "Bool;" \
  "Vector2;" \
  "Rect;" \
  "Color;" \
  "Dropdown"

typedef struct EntitySprite
{
  Rectangle rect;
  Texture2D *texture;
} EntitySprite;

typedef union FieldValue
{
  char *string;
  bool boolean;
  int number;
  int dropdownIndex;
  Vector2 vector2;
  Rectangle rect;
  Color color;
} FieldValue;


// ====== Entity Prototype ====== //
typedef struct EntityPrototypeField
{
  char *name;
  FieldType type;
  FieldValue defaultValue;
} EntityPrototypeField;

typedef struct Entity
{
  int fieldCount;
  EntityPrototypeField *fields;
  char *name;
  EntitySprite *sprite;
  Color *color;
} Entity;

typedef bool (*EntityPrototypeFieldDrawMethod)(EntityPrototypeField *field, Vector2 labelPosition, Rectangle inputRect);
bool entityFieldPrototypeDraw(EntityPrototypeField *field, Vector2 labelPosition, Rectangle inputRect);

void entityInit(Entity *entity);
void entityAddField(Entity *entity, EntityPrototypeField *field);
void entityRemoveField(Entity *entity, const int index);
int searchEntityPrototypeFieldByName(Entity *entity, const char *name);
void entityFree(Entity *entity);

// ====== Entity Instance ====== //
typedef struct EntityInstanceField
{
  char *name;
  bool isEditable;
  FieldType type;
  FieldValue value;
} EntityInstanceField;

typedef struct EntityInstance
{
  Entity *entity;
  EntityInstanceField *fields;
  GridPosition position;
} EntityInstance;

typedef bool (*EntityInstanceFieldDrawMethod)(EntityInstanceField *field, Vector2 labelPosition, Rectangle inputRect);
bool entityInstanceFieldDraw(EntityInstanceField *field, Vector2 labelPosition, Rectangle inputRect);