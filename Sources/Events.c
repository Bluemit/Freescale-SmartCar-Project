/* ###################################################################
**     Filename    : Events.c
**     Project     : ProcessorExpert
**     Processor   : MC56F84786VLK
**     Component   : Events
**     Version     : Driver 01.03
**     Compiler    : CodeWarrior DSP C Compiler
**     Date/Time   : 2014-10-01, 21:23, # CodeGen: 23
**     Abstract    :
**         This is user's event module.
**         Put your event handler code here.
**     Settings    :
**     Contents    :
**         TMR_OnInterrupt - void TMR_OnInterrupt(void);
**
** ###################################################################*/
/*!
** @file Events.c
** @version 01.03
** @brief
**         This is user's event module.
**         Put your event handler code here.
*/         
/*!
**  @addtogroup Events_module Events module documentation
**  @{
*/         
/* MODULE Events */

#include "Cpu.h"
#include "Events.h"
#include "World.h"

static U16 st_nCount;
U16 g_nCount1s;
//Cam
static u16 st_nCamRow;
U8 g_nFpsTmp,g_nFPS,g_nFPSMax;
u16 g_nTmp;
U8 g_nCol;

/* User includes (#include below this line is not maintained by Processor Expert) */

/*
** ===================================================================
**     Event       :  TMR_OnInterrupt (module Events)
**
**     Component   :  TMR [TimerInt]
**     Description :
**         When a timer interrupt occurs this event is called (only
**         when the component is enabled - <Enable> and the events are
**         enabled - <EnableEvent>). This event is enabled only if a
**         <interrupt service/event> is enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
#pragma interrupt called /* Comment this line if the appropriate 'Interrupt preserve registers' property */
                         /* is set to 'yes' (#pragma interrupt saveall is generated before the ISR)      */
void TMR_OnInterrupt(void)
{
  /* Write your code here ... */
	u16 nTmp;
	st_nCount++;
	if (st_nCount>=1000){//1s
		g_nCount1s++;
		st_nCount=0;
		g_nFPS=g_nFpsTmp;g_nFpsTmp=0;//reset FPS Measure
		if (g_nFPS>g_nFPSMax){
			g_nFPSMax=g_nFPS;
		}
	}
	nTmp=st_nCount%4;
	if (nTmp==0){
		
	}else{
		
	}
}

/*
** ===================================================================
**     Event       :  VS_OnInterrupt (module Events)
**
**     Component   :  VS [ExtInt]
**     Description :
**         This event is called when an active signal edge/level has
**         occurred.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
#pragma interrupt called /* Comment this line if the appropriate 'Interrupt preserve registers' property */
                         /* is set to 'yes' (#pragma interrupt saveall is generated before the ISR)      */
void VS_OnInterrupt(void)
{
  /* place your VS interrupt procedure body here */
	g_nCamFrameIndex++;
	g_nFpsTmp++;
	st_nCamRow=g_nNowRow=0;
}


/*
** ===================================================================
**     Event       :  HS_OnInterrupt (module Events)
**
**     Component   :  HS [ExtInt]
**     Description :
**         This event is called when an active signal edge/level has
**         occurred.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
#pragma interrupt called /* Comment this line if the appropriate 'Interrupt preserve registers' property */
                         /* is set to 'yes' (#pragma interrupt saveall is generated before the ISR)      */
void HS_OnInterrupt(void)
{
  /* place your HS interrupt procedure body here */
	if (st_nCamRow>=IMG_START_ROW && g_nNowRow<IMG_ROWS && (st_nCamRow-IMG_START_ROW)%IMG_STEP==0){
		//g_nCol=0;
		DMA_12_SetDestinationAddress(g_nCamFrameBuffer[g_nNowRow]);
		DMA_12_SetDataSize(IMG_COLS);
		DMA_12_Start();
		ADC12_CTRL1&=~0x4000;//normal
		ADC12_CTRL1|=0x2000;//start AD conversion
	}
	++st_nCamRow;
}


#pragma interrupt alignsp saveall
void ADC12_InterruptCC(void)
{
	ADC12_STAT=0x0800;
	if (g_nCol<IMG_COLS){
		g_nCamFrameBuffer[g_nNowRow][g_nCol++]=ADC12_RSLT0;//>>7;
	}else if (g_nCol==IMG_COLS){
		ADC12_CTRL1|=0x4000;//stop loop
		g_nCol++;g_nNowRow++;
	}
}

/*
** ===================================================================
**     Event       :  DMA_12_OnComplete (module Events)
**
**     Component   :  DMA_12 [DMAChannel]
**     Description :
**         This event occurs after DMA is complete.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
#pragma interrupt called /* Comment this line if the appropriate 'Interrupt preserve registers' property */
                         /* is set to 'yes' (#pragma interrupt saveall is generated before the ISR)      */
void DMA_12_OnComplete(void)
{
  /* Write your code here ... */
	ADC12_CTRL1|=0x4000;//stop loop
	g_nNowRow++;
}

/* END Events */

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
