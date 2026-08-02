#include <stdlib.h>
#include <stdio.h>
#include <raylib.h>
#include "entities.h"
#include "raygui.h"
#include "modals.h"
#include "constants.h"
#include "box.h"
#include "entities.h"

const int MODAL_WIDTH = 400;
const int MODAL_HEIGHT = 600;

const int MODAL_PADDING_MID = 20;
const int MODAL_PADDING_SMALL = 10;

const int FONT_SIZE_BIG = 16;
const int FONT_SIZE_SMALL = 10;

int TITLE_TEXT_X;
int TITLE_TEXT_Y;

int NAME_TEXTFIELD_LABEL_X = 20;
int NAME_TEXTFIELD_LABEL_Y = 60;
int NAME_TEXTFIELD_HEIGHT = 30;
int NAME_TEXTFIELD_WIDTH;

int LINE_1_X = 0;
int LINE_1_Y = 0;

int FIELD_LABEL_X = 0;
int FIELD_LABEL_Y = 0;
int FIELD_LABEL_WIDTH = 0;
int FIELD_LABEL_HEIGHT = 0;

static bool NEW_ENTITY_FIELD_DROPDOWN_OPEN = false;
static bool NEW_ENTITY_FIELD_NAME_EDIT_MODE = false;
static bool NEW_ENTITY_FIELD_VALID_NAME = true;

static EntityPrototypeField *NEW_ENTITY_PROTOTYPE_FIELD = NULL;

Rectangle NAME_TEXTFIELD_RECT;

void modalConstantsInit(Rectangle *modalRect)
{
  modalRect->x = WINDOW_WIDTH / 2 - MODAL_WIDTH / 2;
  modalRect->y = WINDOW_HEIGHT / 2 - MODAL_HEIGHT / 2;
  modalRect->width = MODAL_WIDTH;
  modalRect->height = MODAL_HEIGHT;

  TITLE_TEXT_X = modalRect->x + MODAL_PADDING_MID;
  TITLE_TEXT_Y = modalRect->y + MODAL_PADDING_SMALL;

  NAME_TEXTFIELD_LABEL_X = TITLE_TEXT_X;
  NAME_TEXTFIELD_LABEL_Y = TITLE_TEXT_Y + FONT_SIZE_BIG + MODAL_PADDING_SMALL;
  NAME_TEXTFIELD_WIDTH = modalRect->width - 2 * MODAL_PADDING_MID;

  NAME_TEXTFIELD_RECT = (Rectangle){
      NAME_TEXTFIELD_LABEL_X,
      NAME_TEXTFIELD_LABEL_Y + MODAL_PADDING_MID,
      NAME_TEXTFIELD_WIDTH,
      NAME_TEXTFIELD_HEIGHT};

  LINE_1_X = NAME_TEXTFIELD_RECT.x;
  LINE_1_Y = NAME_TEXTFIELD_RECT.y + NAME_TEXTFIELD_RECT.height + MODAL_PADDING_MID;

  FIELD_LABEL_X = NAME_TEXTFIELD_RECT.x;
  FIELD_LABEL_Y = LINE_1_Y + MODAL_PADDING_SMALL;

  Vector2 fieldsLabelSize = MeasureTextEx(GetFontDefault(), "Fields", (float)FONT_SIZE_SMALL, 1.0f);
  FIELD_LABEL_WIDTH = (int)fieldsLabelSize.x;
  FIELD_LABEL_HEIGHT = (int)fieldsLabelSize.y;
}

void modalNewEntityInit(Box *box)
{
  Modal *modal = (Modal *)box;
  modalConstantsInit(&modal->base.rect);

  if (modal->state.entityState.entity != NULL)
  {
    free(modal->state.entityState.entity);
  }
  Entity *newEntity = (Entity *)calloc(1, sizeof(Entity));
  modal->state.entityState.name[0] = '\0';
  modal->state.entityState.nameEditMode = false;
  modal->state.entityState.createNewField = false;
  modal->state.entityState.openDropdownIndex = -1;
  newEntity->name = modal->state.entityState.name;
  modal->state.entityState.entity = newEntity;
}

static void initNewFieldInput(Modal *modal)
{
  if (NEW_ENTITY_PROTOTYPE_FIELD != NULL)
    return;

  NEW_ENTITY_FIELD_DROPDOWN_OPEN = false;
  NEW_ENTITY_FIELD_NAME_EDIT_MODE = false;
  NEW_ENTITY_FIELD_VALID_NAME = true;
  NEW_ENTITY_PROTOTYPE_FIELD = (EntityPrototypeField *)calloc(1, sizeof(EntityPrototypeField));
  NEW_ENTITY_PROTOTYPE_FIELD->name = (char *)calloc(64, sizeof(char));

  if (NEW_ENTITY_PROTOTYPE_FIELD != NULL)
  {
    modal->state.entityState.createNewField = true;
    modal->state.entityState.openDropdownIndex = -1;
  }
}

static void drawNewFieldInput(Entity *entity, Rectangle labelFieldRect, Rectangle inputRect, int *openIndex)
{
  Rectangle fieldNameRect = (Rectangle){
      inputRect.x,
      inputRect.y,
      inputRect.width / 3,
      inputRect.height,
  };

  Rectangle dropdownRect = (Rectangle){
      inputRect.x + inputRect.width / 3,
      inputRect.y,
      inputRect.width / 3,
      inputRect.height,
  };

  Rectangle acceptButtonRect = (Rectangle){
      dropdownRect.x + dropdownRect.width + MODAL_PADDING_SMALL,
      inputRect.y,
      (inputRect.width / 3 - MODAL_PADDING_SMALL) / 2,
      inputRect.height,
  };

  Rectangle cancelButtonRect = (Rectangle){
      acceptButtonRect.x + acceptButtonRect.width + MODAL_PADDING_SMALL,
      inputRect.y,
      acceptButtonRect.width,
      inputRect.height,
  };

  DrawText("Field name", labelFieldRect.x, labelFieldRect.y, FONT_SIZE_SMALL, COLOR_5);

  if (GuiTextBox(fieldNameRect, NEW_ENTITY_PROTOTYPE_FIELD->name, 64, NEW_ENTITY_FIELD_NAME_EDIT_MODE))
  {
    NEW_ENTITY_FIELD_NAME_EDIT_MODE = !NEW_ENTITY_FIELD_NAME_EDIT_MODE;
    NEW_ENTITY_PROTOTYPE_FIELD->name = NEW_ENTITY_PROTOTYPE_FIELD->name; // Update the name in the prototype field
    int index = searchEntityPrototypeFieldByName(entity, NEW_ENTITY_PROTOTYPE_FIELD->name);
    if (index >= 0)
    {
      NEW_ENTITY_FIELD_VALID_NAME = false;
    }
  }

  DrawText("Type", dropdownRect.x, labelFieldRect.y, FONT_SIZE_SMALL, COLOR_5);
  
  if (GuiDropdownBox(dropdownRect, ENTITY_FIELD_TYPE_NAMES_DROPDOWN, openIndex, NEW_ENTITY_FIELD_DROPDOWN_OPEN))
  {
    NEW_ENTITY_FIELD_DROPDOWN_OPEN = !NEW_ENTITY_FIELD_DROPDOWN_OPEN;
    NEW_ENTITY_PROTOTYPE_FIELD->type = (FieldType)(*openIndex + 1); // +1 to skip "None" type
  }

  if (GuiButton(acceptButtonRect, "Add"))
  {
    if (NEW_ENTITY_FIELD_VALID_NAME && NEW_ENTITY_PROTOTYPE_FIELD->name[0] != '\0' && NEW_ENTITY_PROTOTYPE_FIELD->type != ENTITY_TYPE_NONE)
    {
      entityAddField(entity, NEW_ENTITY_PROTOTYPE_FIELD);
      free(NEW_ENTITY_PROTOTYPE_FIELD->name);
      free(NEW_ENTITY_PROTOTYPE_FIELD);
      NEW_ENTITY_PROTOTYPE_FIELD = NULL;
    }
  }
  if (GuiButton(cancelButtonRect, "Cancel"))
  {
    free(NEW_ENTITY_PROTOTYPE_FIELD->name);
    free(NEW_ENTITY_PROTOTYPE_FIELD);
    NEW_ENTITY_PROTOTYPE_FIELD = NULL;
  }

  // entityFieldPrototypeDraw(
  //     NEW_ENTITY_PROTOTYPE_FIELD,
  //     (Vector2){dropdownRect.x + dropdownRect.width + MODAL_PADDING_SMALL, dropdownRect.y},
  //     (Rectangle){dropdownRect.x + dropdownRect.width + MODAL_PADDING_SMALL, dropdownRect.y,
  //                 inputRect.width / 3,
  //                 inputRect.height});
}

void modalNewEntityDraw(Box *box)
{
  Modal *modal = (Modal *)box;

  DrawRectangleRec(modal->base.rect, COLOR_3);
  DrawText("New Entity Modal", TITLE_TEXT_X, TITLE_TEXT_Y, FONT_SIZE_BIG, COLOR_5);
  DrawText("Entity name", NAME_TEXTFIELD_LABEL_X, NAME_TEXTFIELD_LABEL_Y, FONT_SIZE_SMALL, COLOR_5);

  if (GuiTextBox(NAME_TEXTFIELD_RECT,
                 modal->state.entityState.name,
                 (int)sizeof(modal->state.entityState.name),
                 modal->state.entityState.nameEditMode))
  {
    modal->state.entityState.nameEditMode = !modal->state.entityState.nameEditMode;
  }

  DrawLine(LINE_1_X, LINE_1_Y, LINE_1_X + NAME_TEXTFIELD_WIDTH, LINE_1_Y, COLOR_5);

  // FIELDS
  DrawText("Fields", FIELD_LABEL_X, FIELD_LABEL_Y, FONT_SIZE_BIG, COLOR_5);

  if (GuiButton((Rectangle){
                    FIELD_LABEL_WIDTH + MODAL_PADDING_SMALL + FIELD_LABEL_X,
                    FIELD_LABEL_Y,
                    MODAL_PADDING_MID,
                    MODAL_PADDING_MID},
                PLUS_ICON))
  {
    initNewFieldInput(modal);
  }

  Rectangle labelFieldRect = (Rectangle){
      FIELD_LABEL_X,
      FIELD_LABEL_Y + FIELD_LABEL_HEIGHT + MODAL_PADDING_SMALL,
      NAME_TEXTFIELD_WIDTH,
      FIELD_LABEL_HEIGHT};
  Rectangle fieldRect = (Rectangle){
      FIELD_LABEL_X,
      labelFieldRect.y + labelFieldRect.height + MODAL_PADDING_SMALL,
      NAME_TEXTFIELD_WIDTH,
      NAME_TEXTFIELD_HEIGHT};
  
  if (NEW_ENTITY_PROTOTYPE_FIELD != NULL)
  {
    drawNewFieldInput(modal->state.entityState.entity, labelFieldRect, fieldRect, &modal->state.entityState.openDropdownIndex);
    labelFieldRect.y += fieldRect.y + fieldRect.height + MODAL_PADDING_SMALL;
    fieldRect.y += labelFieldRect.y + labelFieldRect.height + MODAL_PADDING_SMALL;
    
  }

  for (int i = 0; i < modal->state.entityState.entity->fieldCount; i++)
  {
    EntityPrototypeField *field = &modal->state.entityState.entity->fields[i];
    DrawText(field->name, labelFieldRect.x, labelFieldRect.y, FONT_SIZE_SMALL, COLOR_5);

    labelFieldRect.y += fieldRect.height + MODAL_PADDING_SMALL;


  }
}

Modal modalNewEntity = (Modal){
    .base = (Box){
        .init = modalNewEntityInit,
        .draw = modalNewEntityDraw,
    }};