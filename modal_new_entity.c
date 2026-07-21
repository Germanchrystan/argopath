#include <stdlib.h>
#include <stdio.h>
#include <raylib.h>
#include "entities.h"
#include "raygui.h"
#include "modals.h"
#include "constants.h"
#include "box.h"

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
    NAME_TEXTFIELD_HEIGHT
  };

  LINE_1_X = NAME_TEXTFIELD_RECT.x;
  LINE_1_Y = NAME_TEXTFIELD_RECT.y + NAME_TEXTFIELD_RECT.height + MODAL_PADDING_MID;

  FIELD_LABEL_X = NAME_TEXTFIELD_RECT.x;
  FIELD_LABEL_Y = LINE_1_Y + MODAL_PADDING_SMALL;

  Vector2 fieldsLabelSize = MeasureTextEx(GetFontDefault(), "Fields", (float)FONT_SIZE_BIG, 1.0f);
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
  modal->state.entityState.openDropdown = false;
  modal->state.entityState.openDropdownIndex = -1;
  newEntity->name = modal->state.entityState.name;
  modal->state.entityState.entity = newEntity;
}

static void drawNewFieldInput(Entity *entity, Rectangle inputRect, int *openIndex)
{
  if (GuiDropdownBox(inputRect, ENTITY_FIELD_TYPE_NAMES_DROPDOWN, openIndex, NEW_ENTITY_FIELD_DROPDOWN_OPEN))
  {
    NEW_ENTITY_FIELD_DROPDOWN_OPEN = !NEW_ENTITY_FIELD_DROPDOWN_OPEN;
    printf("Dropdown box clicked: openIndex=%d\n", *openIndex);
  }
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

  if (GuiButton((Rectangle) {
    FIELD_LABEL_WIDTH + MODAL_PADDING_SMALL + FIELD_LABEL_X,
    FIELD_LABEL_Y,
    FIELD_LABEL_HEIGHT,
    FIELD_LABEL_HEIGHT
  }, PLUS_ICON))
  {
    modal->state.entityState.createNewField = true;
    modal->state.entityState.openDropdown = false;
  }

  Rectangle newFieldInputRect = (Rectangle){
    FIELD_LABEL_X,
    FIELD_LABEL_Y + FIELD_LABEL_HEIGHT + MODAL_PADDING_SMALL,
    NAME_TEXTFIELD_WIDTH,
    NAME_TEXTFIELD_HEIGHT
  };
  if (modal->state.entityState.createNewField)
  {
    drawNewFieldInput(modal->state.entityState.entity, newFieldInputRect, &modal->state.entityState.openDropdownIndex);
  }

  for (int i = 0; i < modal->state.entityState.entity->fieldCount; i++)
  {
    EntityPrototypeField *field = &modal->state.entityState.entity->fields[i];
    DrawText(field->name, NAME_TEXTFIELD_LABEL_X, NAME_TEXTFIELD_LABEL_Y + (i + 1) * (NAME_TEXTFIELD_HEIGHT + MODAL_PADDING_SMALL), FONT_SIZE_SMALL, COLOR_5);
  }
  
}

Modal modalNewEntity = (Modal){
  .base = (Box){
    .init = modalNewEntityInit,
    .draw = modalNewEntityDraw,
  }
};