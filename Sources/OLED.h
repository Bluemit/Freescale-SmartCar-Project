#ifndef OLED_H
#define OLED_H

#include "Type.h"

//SPI data type macro definition.
#define OLED_CMD 0
#define OLED_DATA 1
#define OLED_MAX_SCREEN 12

extern u8 g_nShow;
void OLEDInit(void);
void OLEDUpdate(u8 screen,u8 index);
void NextAction(u8 screen, u8 index);

#endif
