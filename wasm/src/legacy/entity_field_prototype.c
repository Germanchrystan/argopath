#include "entities.h"
// #include "raygui.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
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

int searchEntityPrototypeFieldByName(Entity *entity, const char *name)
{
    if (entity == NULL || name == NULL)
        return -1;

    for (int i = 0; i < entity->fieldCount; i++)
    {
        if (entity->fields[i].name != NULL && strcmp(entity->fields[i].name, name) == 0)
        {
            return i;
        }
    }
    return -1; // Not found
}

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


void entityAddField(Entity *entity, EntityPrototypeField *field)
{
    if (entity == NULL || field == NULL)
        return;

    // Check for duplicate field names
    if (searchEntityPrototypeFieldByName(entity, field->name) != -1)
        return; // Field with the same name already exists

    // Allocate memory for the new field
    EntityPrototypeField *newFields = (EntityPrototypeField *)realloc(entity->fields, sizeof(EntityPrototypeField) * (entity->fieldCount + 1));
    if (newFields == NULL)
        return; // Memory allocation failed

    entity->fields = newFields;

    entity->fields[entity->fieldCount] = *(EntityPrototypeField *)calloc(1, sizeof(EntityPrototypeField));
    entity->fields[entity->fieldCount].name = strdup(field->name);
    if (entity->fields[entity->fieldCount].name == NULL)
    {
        // Memory allocation failed, clean up and return
        free(entity->fields[entity->fieldCount].name);
        free(&entity->fields[entity->fieldCount]);
        fprintf(stderr, "Memory allocation failed for field name\n");
        return;
    }
    entity->fields[entity->fieldCount].type = field->type;
    entity->fieldCount++;
}