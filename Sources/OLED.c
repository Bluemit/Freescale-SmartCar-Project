/*
 * OLED.c
 *
 *  Created on: Jul 3, 2014
 *      Author: Administrator
 */ 
#include "HMI_OLED.h"
#include "character.h"
#include "OLED.h"
#include "World.h"
#include "Events.h"
u8 g_nShow;
void SPIWrite(u8 data0,u8 type);
void OLEDSetPos(u8 page,u8 column);
void OLEDPrintAscii(char data0[],u8 row,u8 column);
void OLEDPrintUint8(u8 num,u8 row,u8 column);
void OLEDPrintUint16(u16 num,u8 row,u8 column);
void OLEDClearScreen(void);
void OLEDSetCharPos(u8 row,u8 column);// row:[1,4] ; column:[1,16]

volatile u8 OLEDMaxIndex[OLED_MAX_SCREEN] = {4, 6, 4, 3, 3, 3, 8, 5, 8, 4, 3,4};
volatile u8 OLEDScreen = 0;
volatile u8 OLEDIndex = 0;

extern U8 LEDIndex;

void SPIWrite(u8 data0,u8 type)
{
	u8 i= 8;

	HMI_OLED_PutBit(1,0);//SCL L

	if(type == OLED_CMD)
		HMI_OLED_PutBit(3,0);//D/C L
	else if(type == OLED_DATA)
		HMI_OLED_PutBit(3,1);//D/C H

  while (i--)
  {
    if (data0 & 0x80)
    {
    	HMI_OLED_PutBit(2,1);
    }
    else
    {
    	HMI_OLED_PutBit(2,0);
    }
    HMI_OLED_PutBit(1,1);  //SCL H
    asm(nop);asm(nop);
	HMI_OLED_PutBit(1,0);  //SCL L   
    data0<<=1;   
  }
}

void OLEDInit(void)        
{
    u8 i;
  	//Output
    HMI_OLED_PutBit(1,1);//SCL H
    HMI_OLED_PutBit(0,0);//RST L
    for(i=0;i<100;i++)
    {
    	asm(nop);asm(nop);//Wait RC reset.
    }
    HMI_OLED_PutBit(0,1);//RST H
		
    SPIWrite(0xAE, OLED_CMD);  // Display Off
    SPIWrite(0xD5, OLED_CMD);
    SPIWrite(0xA0, OLED_CMD);
    //SPIWrite(0x80, OLED_CMD);  // Set Clock as 100 Frames/Sec
    SPIWrite(0xA8, OLED_CMD);
    SPIWrite(0x3F, OLED_CMD);  // 1/64 Duty (0x0F~0x3F)
    SPIWrite(0xD3, OLED_CMD);
    SPIWrite(0x00, OLED_CMD);  // Shift Mapping RAM Counter (0x00~0x3F)
    SPIWrite(0x40, OLED_CMD);  // Set Mapping RAM Display Start Line (0x00~0x3F)
    SPIWrite(0x8D, OLED_CMD);
    SPIWrite(0x14, OLED_CMD);  // Enable Embedded DC/DC Converter (0x10/0x14)
    SPIWrite(0x20, OLED_CMD);
    SPIWrite(0x02, OLED_CMD);  // Set Page Addressing Mode (0x00/0x01/0x02)
    SPIWrite(0xA1, OLED_CMD);  // Set SEG/Column Mapping (0xA0/0xA1)
    SPIWrite(0xC8, OLED_CMD);  // Set COM/Row Scan Direction : Scan from COM63 to 0
   
    SPIWrite(0x00, OLED_CMD); //---set low column address
    SPIWrite(0x10, OLED_CMD); //---set high column address
    SPIWrite(0xb0, OLED_CMD); //Set Page Start Address for Page Addressing Mode,0-7
    
    SPIWrite(0xDA, OLED_CMD);  
    SPIWrite(0x12, OLED_CMD);  // Set Sequential Configuration
    SPIWrite(0x81, OLED_CMD); 
    //SPIWrite(0xAF, OLED_CMD);
    SPIWrite(0xCF, OLED_CMD);  // Set SEG Output Current
    SPIWrite(0xD9, OLED_CMD);  
    //SPIWrite(0x22, OLED_CMD);
    SPIWrite(0xF1, OLED_CMD);  // Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
    SPIWrite(0xDB, OLED_CMD);  
    //SPIWrite(0x20, OLED_CMD);
    SPIWrite(0x40, OLED_CMD);  // Set VCOM Deselect Level
    SPIWrite(0xA4, OLED_CMD);  // Disable Entire Display On (0xA4/0xA5)
    /***************/
    SPIWrite(0xA6, OLED_CMD);  // Disable Inverse Display On (0xA6/0xA7)  
    /***************/
    SPIWrite(0xAF, OLED_CMD);  // Display On
    OLEDClearScreen();  //Clear Screen
    OLEDSetCharPos(1,1);
    return;
} 

void OLEDPrintAscii(char data0[],u8 row,u8 column)
{
	u8 i,j,rawpage,rawcol;
	rawpage=(row-1)*2;
	rawcol=(column-1)*8;
	for(i=0;data0[i]!='\0';i++)
	{
		//Line feed.
		if(data0[i] == '\n')
		{
			rawpage += 2;
			rawcol = 0;
			if(rawpage > 7)     //4 rows
				rawpage = 0;
			continue;
		}
		//Write character
		OLEDSetPos(rawpage, rawcol);
		for(j = 0;j < 8;j++)
			SPIWrite((u8)Ascii8x16[(u8)data0[i] - 0x20][j],OLED_DATA);
		OLEDSetPos(rawpage + 1, rawcol);
		for(j = 8;j < 16;j++)
			SPIWrite((u8)Ascii8x16[(u8)data0[i] - 0x20][j],OLED_DATA);
		//Move cursor to next position
		rawcol += 8;        //16 cols
		if(rawcol > 127)
		{
			rawpage += 2;
			rawcol = 0;
		}
		if(rawpage > 7)
			rawpage = 0;
	}
}

void OLEDPrintUint16(u16 num, u8 row, u8 column)
{
	u8 n=num/10000;
	char ascii;
	u8 haswan=0,hasthousand=0,hashundred=0;
	//wan
	if(n!=0)
	{
		ascii=n+48;
		OLEDPrintAscii(&ascii, row, column);
		column++;
		haswan=1;
	}
	num-=n*10000;
	n=num/1000;
	//thousand
	if(haswan||n)
	{
		ascii=n+48;
		OLEDPrintAscii(&ascii, row, column);
		column++;
		hasthousand=1;
	}
	num-=n*1000;
	n=num/100;
	//Hundreds
	if(hasthousand||n)
	{
		ascii=n+48;
		OLEDPrintAscii(&ascii, row, column);
		column++;
		hashundred=1;
	}
	num-=n*100;
	n=num/10;
	//Decade
	if(hashundred||n)
	{
		ascii=n+48;
		OLEDPrintAscii(&ascii,row,column);
		column++;
	}
	num-=n*10;
	//The unit
	ascii=num+48;
	OLEDPrintAscii(&ascii,row,column);
}
void OLEDPrintUint8(u8 num, u8 row, u8 column)
{
	u8 n = num / 100;
	u8 ascii[2] = {'\0', '\0'};
	u8 hashundred = 0;

	//Hundreds
	if(n != 0)
	{
		ascii[0] = n + 48;
		OLEDPrintAscii((char*)ascii, row, column);
		column++;
		hashundred = 1;
	}
	num -= n * 100;
	n = num / 10;

	//Decade
	if((hashundred == 1) || (n != 0))
	{
		ascii[0] = n + 48;
		OLEDPrintAscii((char*)ascii, row, column);
		column++;
	}
	num -= n * 10;

	//The unit
	ascii[0] = num + 48;
	OLEDPrintAscii((char*)ascii, row, column);
}
void OLEDClearScreen(void)
{
	unsigned char i,j;
	//asm ORCC #$80; //Disable MI
	for(j = 0;j < 8;j++) 
	{
	   OLEDSetPos(j,0);
	   for(i = 0;i < 128;i++)
		    SPIWrite(0x00,OLED_DATA); 
	}
	//asm ANDCC #$EF; //Enable MI
}

void OLEDSetCharPos(u8 row,u8 column)// row:[1,4] ; column:[1,16]
{
	OLEDSetPos((row - 1) * 2, (column - 1) * 8);
}

void OLEDSetPos(u8 page,u8 column)
{
	SPIWrite(0xB0 + page,OLED_CMD);
	SPIWrite(column & 0x0F,OLED_CMD);
	SPIWrite(0x10 + (column >> 4),OLED_CMD);
}

//menu
void OLEDUpdate(u8 screen,u8 index)
{
	OLEDClearScreen();
	switch(screen)
	{
		case 0:
		{
			OLEDPrintAscii("Hello World!",1,1);
			break;
			/*
			
			
			OLEDPrintAscii("START", 1, 3);
			OLEDPrintAscii("Volt", 1, 10);
			OLEDPrintAscii(":", 1, 14);
			OLEDPrintUint8(g_nShow,1,15);
			OLEDPrintAscii("Data", 2, 3);
			OLEDPrintAscii("PID", 3, 3);
			OLEDPrintAscii("Set",4,3);
			OLEDPrintAscii("*", index + 1 , 1);
			
			break;
			
			*/
		}
	}
}

void NextAction(u8 screen, u8 index)
{
	
}





