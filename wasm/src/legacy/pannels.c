#include "pannels.h"

float PANNEL_PADDING_1 = 0.0f;
float PANNEL_HEIGHT_1 = 0.0f;
float PANNEL_HEIGHT_2 = 0.0f;
float PANNEL_HEIGHT_3 = 0.0f;
float PANNEL_WIDTH_1 = 0.0f;

void initPannelConstants(void)
{
  
  PANNEL_HEIGHT_1 = (float)WINDOW_HEIGHT / 6.0f;
  PANNEL_HEIGHT_2 = (float)WINDOW_HEIGHT / 3.0f;
  PANNEL_HEIGHT_3 = (float)WINDOW_HEIGHT / 2.0f;
  PANNEL_WIDTH_1 = (float)WINDOW_WIDTH / 12.0f;
  
  PANNEL_PADDING_1 = (float)PANNEL_WIDTH_1 / 12.0f;
}
