#include "entities.h"
// #include "raygui.h"
#include <stdlib.h>
#include <raylib.h>

static bool entityFieldPrototypeDrawNumber(EntityPrototypeField *field, Vector2 labelPosition, Rectangle inputRect);
static bool entityFieldPrototypeDrawString(EntityPrototypeField *field, Vector2 labelPosition, Rectangle inputRect);
static bool entityFieldPrototypeDrawBool(EntityPrototypeField *field, Vector2 labelPosition, Rectangle inputRect);
static bool entityFieldPrototypeDrawVector2(EntityPrototypeField *field, Vector2 labelPosition, Rectangle inputRect);
static bool entityFieldPrototypeDrawRect(EntityPrototypeField *field, Vector2 labelPosition, Rectangle inputRect);
static bool entityFieldPrototypeDrawColor(EntityPrototypeField *field, Vector2 labelPosition, Rectangle inputRect);
static bool entityFieldPrototypeDrawDropdown(EntityPrototypeField *field, Vector2 labelPosition, Rectangle inputRect);

static EntityPrototypeFieldDrawMethod registry[ENTITY_TYPE_LENGTH] =
{
        [ENTITY_TYPE_NONE] = NULL,
        [ENTITY_TYPE_NUMBER] = entityFieldPrototypeDrawNumber,
        [ENTITY_TYPE_STRING] = entityFieldPrototypeDrawString,
        [ENTITY_TYPE_BOOL] = entityFieldPrototypeDrawBool,
        [ENTITY_TYPE_VECTOR2] = entityFieldPrototypeDrawVector2,
        [ENTITY_TYPE_RECT] = entityFieldPrototypeDrawRect,
        [ENTITY_TYPE_COLOR] = entityFieldPrototypeDrawColor,
        [ENTITY_TYPE_DROPDOWN] = entityFieldPrototypeDrawDropdown,
};

bool entityFieldPrototypeDraw(EntityPrototypeField *field, Vector2 labelPosition, Rectangle inputRect)
{
    if (field == NULL || field->type >= ENTITY_TYPE_LENGTH)
        return false;
    EntityPrototypeFieldDrawMethod drawMethod = registry[field->type];
    if (drawMethod == NULL)
        return false;
    return drawMethod(field, labelPosition, inputRect);
}

static bool entityFieldPrototypeDrawNumber(EntityPrototypeField *field, Vector2 labelPosition, Rectangle inputRect)
{
    (void)field;
    (void)labelPosition;
    (void)inputRect;
    return true;
}

static bool entityFieldPrototypeDrawString(EntityPrototypeField *field, Vector2 labelPosition, Rectangle inputRect)
{
    (void)field;
    (void)labelPosition;
    (void)inputRect;
    return true;
}

static bool entityFieldPrototypeDrawBool(EntityPrototypeField *field, Vector2 labelPosition, Rectangle inputRect)
{
    (void)field;
    (void)labelPosition;
    (void)inputRect;
    return true;
}

static bool entityFieldPrototypeDrawVector2(EntityPrototypeField *field, Vector2 labelPosition, Rectangle inputRect)
{
    (void)field;
    (void)labelPosition;
    (void)inputRect;
    return true;
}

static bool entityFieldPrototypeDrawRect(EntityPrototypeField *field, Vector2 labelPosition, Rectangle inputRect)
{
    (void)field;
    (void)labelPosition;
    (void)inputRect;
    return true;
}

static bool entityFieldPrototypeDrawColor(EntityPrototypeField *field, Vector2 labelPosition, Rectangle inputRect)
{
    (void)field;
    (void)labelPosition;
    (void)inputRect;
    return true;
}

static bool entityFieldPrototypeDrawDropdown(EntityPrototypeField *field, Vector2 labelPosition, Rectangle inputRect)
{
    (void)field;
    (void)labelPosition;
    (void)inputRect;
    return true;
}

