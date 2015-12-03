/* ###################################################################
**     THIS COMPONENT MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename    : TMR.c
**     Project     : ProcessorExpert
**     Processor   : MC56F84786VLK
**     Component   : TimerInt
**     Version     : Component 02.161, Driver 02.06, CPU db: 3.50.001
**     Compiler    : CodeWarrior DSP C Compiler
**     Date/Time   : 2015-01-30, 18:37, # CodeGen: 149
**     Abstract    :
**         This component "TimerInt" implements a periodic interrupt.
**         When the component and its events are enabled, the "OnInterrupt"
**         event is called periodically with the period that you specify.
**         TimerInt supports also changing the period in runtime.
**         The source of periodic interrupt can be timer compare or reload
**         register or timer-overflow interrupt (of free running counter).
**     Settings    :
**         Timer name                  : TMRA0 (16-bit)
**         Compare name                : TMRA0_Compare
**         Counter shared              : No
**
**         High speed mode
**             Prescaler               : divide-by-2
**             Clock                   : 50000000 Hz
**           Initial period/frequency
**             Xtal ticks              : 8000
**             microseconds            : 1000
**             milliseconds            : 1
**             seconds (real)          : 0.001
**             Hz                      : 1000
**             kHz                     : 1
**
**         Runtime setting             : none
**
**         Initialization:
**              Timer                  : Enabled
**              Events                 : Enabled
**
**         Timer registers
**              Counter                : TMRA_0_CNTR [E145]
**              Mode                   : TMRA_0_CTRL [E146]
**              Run                    : TMRA_0_CTRL [E146]
**              Prescaler              : TMRA_0_CTRL [E146]
**
**         Compare registers
**              Compare                : TMRA_0_COMP1 [E140]
**
**         Flip-flop registers
**              Mode                   : TMRA_0_SCTRL [E147]
**     Contents    :
**         No public methods
**
**     Copyright : 1997 - 2014 Freescale Semiconductor, Inc. 
**     All Rights Reserved.
**     
**     Redistribution and use in source and binary forms, with or without modification,
**     are permitted provided that the following conditions are met:
**     
**     o Redistributions of source code must retain the above copyright notice, this list
**       of conditions and the following disclaimer.
**     
**     o Redistributions in binary form must reproduce the above copyright notice, this
**       list of conditions and the following disclaimer in the documentation and/or
**       other materials provided with the distribution.
**     
**     o Neither the name of Freescale Semiconductor, Inc. nor the names of its
**       contributors may be used to endorse or promote products derived from this
**       software without specific prior written permission.
**     
**     THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
**     ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
**     WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
**     DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
**     ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
**     (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
**     LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
**     ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
**     (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
**     SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**     
**     http: www.freescale.com
**     mail: support@freescale.com
** ###################################################################*/
/*!
** @file TMR.c
** @version 02.06
** @brief
**         This component "TimerInt" implements a periodic interrupt.
**         When the component and its events are enabled, the "OnInterrupt"
**         event is called periodically with the period that you specify.
**         TimerInt supports also changing the period in runtime.
**         The source of periodic interrupt can be timer compare or reload
**         register or timer-overflow interrupt (of free running counter).
*/         
/*!
**  @addtogroup TMR_module TMR module documentation
**  @{
*/         

/* MODULE TMR. */

#include "Events.h"
#include "TMR.h"



/* Internal method prototypes */
static void SetCV(word Val);
static void SetPV(byte Val);

/*
** ===================================================================
**     Method      :  SetCV (component TimerInt)
**
**     Description :
**         Sets compare or preload register value. The method is called 
**         automatically as a part of several internal methods.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
static void SetCV(word Val)
{
  EnterCritical();                     /* Disable global interrupts */
  setReg(TMRA_0_CMPLD1,Val);           /* Store given value to the compare preload 1 register */
  setReg(TMRA_0_CMPLD2,Val);           /* Store given value to the compare preload 2 register */
  ExitCritical();                      /* Enable global interrupts */
}

/*
** ===================================================================
**     Method      :  SetPV (component TimerInt)
**
**     Description :
**         Sets prescaler value. The method is called automatically as a 
**         part of several internal methods.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
static void SetPV(byte Val)
{
  setRegBitGroup(TMRA_0_CTRL,PCS,Val); /* Store given value to the prescaler */
  setReg(TMRA_0_CNTR,0);               /* Reset counter */
}

/*
** ===================================================================
**     Method      :  TMR_Init (component TimerInt)
**
**     Description :
**         Initializes the associated peripheral(s) and the beans 
**         internal variables. The method is called automatically as a 
**         part of the application initialization code.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
void TMR_Init(void)
{
  /* TMRA_0_CTRL: CM=0,PCS=0,SCS=0,ONCE=0,LENGTH=1,DIR=0,COINIT=0,OUTMODE=4 */
  setReg(TMRA_0_CTRL,0x24);            /* Stop timer, use alternating compare registers */
  /* TMRA_0_SCTRL: TCF=0,TCFIE=1,TOF=0,TOFIE=0,IEF=0,IEFIE=0,IPS=0,INPUT=0,CAPTURE_MODE=0,MSTR=0,EEOF=0,VAL=0,FORCE=0,OPS=0,OEN=0 */
  setReg(TMRA_0_SCTRL,0x4000);         /* Enable compare interrupt */
  setReg(TMRA_0_CNTR,0x00);            /* Reset counter register */
  setReg(TMRA_0_LOAD,0x00);            /* Reset load register */
  setReg(TMRA_0_COMP1,0xC34F);         /* Set up compare 1 register */
  setReg(TMRA_0_COMP2,0xC34F);         /* Set up compare 2 register */
  /* TMRA_0_CSCTRL: DBG_EN=0,FAULT=0,ALT_LOAD=0,ROC=0,TCI=0,UP=0,??=0,TCF2EN=0,TCF1EN=0,TCF2=0,TCF1=0,CL2=1,CL1=2 */
  setReg(TMRA_0_CSCTRL,0x06);          /* Compare load control */
  SetCV((word)0xC34F);                 /* Store appropriate value to the compare register according to the selected high speed CPU mode */
  SetPV((byte)0x09);                   /* Set prescaler register according to the selected high speed CPU mode */
  setRegBitGroup(TMRA_0_CTRL,CM,0x01); /* Run counter */
}

/*
** ===================================================================
**     Method      :  TMR_Interrupt (component TimerInt)
**
**     Description :
**         The method services the interrupt of the selected peripheral(s)
**         and eventually invokes the beans event(s).
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
#pragma interrupt alignsp saveall
void TMR_Interrupt(void)
{
  clrRegBit(TMRA_0_SCTRL,TCF);         /* Reset interrupt request flag */
  TMR_OnInterrupt();                   /* Invoke user event */
}

/* END TMR. */

/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.3 [05.09]
**     for the Freescale 56800 series of microcontrollers.
**
** ###################################################################
*/
