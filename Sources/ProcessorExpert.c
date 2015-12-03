/* ###################################################################
**     Filename    : ProcessorExpert.c
**     Project     : ProcessorExpert
**     Processor   : MC56F84786VLK
**     Version     : Driver 01.16
**     Compiler    : CodeWarrior DSP C Compiler
**     Date/Time   : 2014-10-01, 10:49, # CodeGen: 0
**     Abstract    :
**         Main module.
**         This module contains user's application code.
**     Settings    :
**     Contents    :
**         No public methods
**
** ###################################################################*/
/*!
** @file ProcessorExpert.c
** @version 01.16
** @brief
**         Main module.
**         This module contains user's application code.
*/         
/*!
**  @addtogroup ProcessorExpert_module ProcessorExpert module documentation
**  @{
*/         
/* MODULE ProcessorExpert */


/* Including needed modules to compile this module/procedure */
#include "Cpu.h"
#include "Events.h"
#include "LED1.h"
#include "LED2.h"
#include "SWITCH.h"
#include "Inhr1.h"
#include "Inhr2.h"
#include "Inhr3.h"
#include "Inhr4.h"
#include "KEY.h"
#include "Inhr5.h"
#include "Inhr6.h"
#include "Inhr7.h"
#include "Inhr8.h"
#include "SCI.h"
#include "HMI_OLED.h"
#include "TMR.h"
#include "LEFTPA.h"
#include "RIGHTPA.h"
#include "DRV_MEN.h"
#include "SERVO1.h"
#include "HS.h"
#include "VS.h"
#include "DMA_12.h"
#include "SERVO2.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"

#include "World.h"

void main(void)
{
  /* Write your local variable definition here */
  u8 ch,row,col,u8Tmp;u16 u16Tmp;
  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  __DI();
  DRV_PWM_Init();
  ADC12_Init();
  OLEDInit();OLEDUpdate(0,0);
  CamInitSystem();
  __EI(0);
  //COP_CTRL&=~(0x2);//cop disable or close watch dog
  /*** End of Processor Expert internal initialization.                    ***/
  /* Write your code here */
  //Cpu_Delay100US(10000);
  DRV_MEN_PutVal(1);
//  DRV_PWM_SetRatio16(0,10000);
//  DRV_PWM_SetRatio16(1,10000);
//  SERVO1_SetDutyUS(1500);
//  SERVO2_SetDutyUS(2000);
  
  for(;;) {

	  OLEDUpdate(0,0);
	  Cpu_Delay100US(1000);
/*  
	  //LEFTPA_GetCounterValue(&u16Tmp);
	  RIGHTPA_GetCounterValue(&u16Tmp);
//	  OLEDUpdate(0,0);
	  if (SWITCH_GetBit(0)) LED1_PutVal(0);
	  else LED1_PutVal(1);
	  //if (!SCI_RecvChar(&ch)&&ch==0xFF) SCI_SendChar(0xBB);
	  for(row=IMG_ROWS-1;row<IMG_ROWS;row--){
		  for(col=IMG_COLS-1;col<IMG_COLS;col--){
			  u8Tmp=g_nCamFrameBuffer[row][col];
			  HMI_SCI_SendChar(insert_in(u8Tmp,0,0xfd));
		  }
		  HMI_SCI_SendChar(0xfe);
	  }
	  HMI_SCI_SendChar(0xff);
	  switch (~KEY_GetVal()&0xF){
	  	  case 0x1:
	  		  LED1_PutVal(0);LED2_PutVal(0);
	  		  break;
	  	  case 0x2:
	  		  LED1_PutVal(1);LED2_PutVal(1);
	  		  break;
	  	  case 0x4:
	  		  LED1_PutVal(0);LED2_PutVal(1);
	  		  break;
	  	  case 0x8:
	  		  LED1_PutVal(1);LED2_PutVal(0);
	  		  break;
	  }
	  
*/	  
	  
  }
}
void HMI_SCI_SendChar(u8 ch){
	while (!(QSCI2_STAT&0x8000)){ /* Is the transmitter empty? */
	}
  
    
	QSCI2_DATA=ch;
}


/* END ProcessorExpert */
/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.2 [05.06]
**     for the Freescale 56800 series of microcontrollers.
**
** ###################################################################
*/
