#include <stdlib.h>
#include <stdio.h>
#include "raygui.h"
#include "constants.h"
#include "entities.h"

static bool entityFieldDrawNumber(EntityInstanceField *field, Vector2 labelPosition, Rectangle inputRect);
static bool entityFieldDrawString(EntityInstanceField *field, Vector2 labelPosition, Rectangle inputRect);
static bool entityFieldDrawBool(EntityInstanceField *field, Vector2 labelPosition, Rectangle inputRect);
static bool entityFieldDrawVector2(EntityInstanceField *field, Vector2 labelPosition, Rectangle inputRect);
static bool entityFieldDrawRect(EntityInstanceField *field, Vector2 labelPosition, Rectangle inputRect);
static bool entityFieldDrawColor(EntityInstanceField *field, Vector2 labelPosition, Rectangle inputRect);
static bool entityFieldDrawDropdown(EntityInstanceField *field, Vector2 labelPosition, Rectangle inputRect);

static EntityInstanceFieldDrawMethod registry[ENTITY_TYPE_LENGTH] =
{
        [ENTITY_TYPE_NONE] = NULL,
        [ENTITY_TYPE_NUMBER] = entityFieldDrawNumber,
        [ENTITY_TYPE_STRING] = entityFieldDrawString,
        [ENTITY_TYPE_BOOL] = entityFieldDrawBool,
        [ENTITY_TYPE_VECTOR2] = entityFieldDrawVector2,
        [ENTITY_TYPE_RECT] = entityFieldDrawRect,
        [ENTITY_TYPE_COLOR] = entityFieldDrawColor,
        [ENTITY_TYPE_DROPDOWN] = entityFieldDrawDropdown,
};


bool entityFieldDraw(EntityInstanceField *field, Vector2 labelPosition, Rectangle inputRect)
{
    if (field->type < 0 || field->type >= ENTITY_TYPE_LENGTH)
    {
      fprintf(stderr, "Error: Invalid field type %d for field '%s'\n", field->type, field->name);
      return false;
    }

    EntityInstanceFieldDrawMethod drawMethod = registry[field->type];
    if (drawMethod == NULL)
    {
      fprintf(stderr, "Error: No draw method registered for field type %d for field '%s'\n", field->type, field->name);
      return false;
    }

    return drawMethod(field, labelPosition, inputRect);
}

static bool entityFieldDrawNumber(EntityInstanceField *field, Vector2 labelPosition, Rectangle inputRect)
{
  // Hardcoded color and font size for now
    DrawText(field->name, labelPosition.x, labelPosition.y, 16, COLOR_5);

  if (GuiValueBox(inputRect,
                field->name,
                 &field->value.number,
                 0,  // Min value
                 100,  // Max value
                 field->isEditable))
  {
    field->isEditable = !field->isEditable;
  }
  return true;
}

static bool entityFieldDrawString(EntityInstanceField *field, Vector2 labelPosition, Rectangle inputRect)
{
  // Hardcoded color and font size for now
    DrawText(field->name, labelPosition.x, labelPosition.y, 16, COLOR_5);

  if (GuiTextBox(inputRect,
                 field->value.string,
                 64,  // Max size of the text box),
                 field->isEditable))
  {
    field->isEditable = !field->isEditable;
  }
  return true;
}

static bool entityFieldDrawBool(EntityInstanceField *field, Vector2 labelPosition, Rectangle inputRect)
{
  (void)field;
  (void)labelPosition;
  (void)inputRect;
  return true;
}

static bool entityFieldDrawVector2(EntityInstanceField *field, Vector2 labelPosition, Rectangle inputRect)
{
  (void)field;
  (void)labelPosition;
  (void)inputRect;
  return true;
}

static bool entityFieldDrawRect(EntityInstanceField *field, Vector2 labelPosition, Rectangle inputRect)
{
  (void)field;
  (void)labelPosition;
  (void)inputRect;
  return true;
}

static bool entityFieldDrawColor(EntityInstanceField *field, Vector2 labelPosition, Rectangle inputRect)
{
  (void)field;
  (void)labelPosition;
  (void)inputRect;
  return true;
}

static bool entityFieldDrawDropdown(EntityInstanceField *field, Vector2 labelPosition, Rectangle inputRect)
{
  (void)field;
  (void)labelPosition;
  (void)inputRect;
  return true;
}

