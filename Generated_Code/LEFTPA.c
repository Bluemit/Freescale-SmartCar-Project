/* ###################################################################
**     THIS COMPONENT MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename    : LEFTPA.c
**     Project     : ProcessorExpert
**     Processor   : MC56F84786VLK
**     Component   : PulseAccumulator
**     Version     : Component 01.193, Driver 02.06, CPU db: 3.50.001
**     Compiler    : CodeWarrior DSP C Compiler
**     Date/Time   : 2015-01-30, 18:37, # CodeGen: 149
**     Abstract    :
**          Pulse accumulator decodes the primary and secondary external inputs as
**          quadrature encoded signals. Quadrature signals are usually generated by
**          rotary or linear sensors used to monitor movement of motor shafts or
**          mechanical equipment.
**     Settings    :
**             Pulse accumulator       : TMRA1_PACNT
**
**
**         Mode                        : Quadrature
**
**         Initialization:
**              Pulse accumulator      : Enabled
**              Events                 : Enabled
**
**         Timer registers
**              Counter                : TMRA_1_CNTR [E155]
**              Hold                   : TMRA_1_HOLD [E154]
**              Run                    : TMRA_1_CTRL [E156]
**              Prescaler              : TMRA_1_CTRL [E156]
**
**         User handling procedure     : not specified
**
**     Contents    :
**         GetCounterValue  - void LEFTPA_GetCounterValue(LEFTPA_TCounterValue *Value);
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
** @file LEFTPA.c
** @version 02.06
** @brief
**          Pulse accumulator decodes the primary and secondary external inputs as
**          quadrature encoded signals. Quadrature signals are usually generated by
**          rotary or linear sensors used to monitor movement of motor shafts or
**          mechanical equipment.
*/         
/*!
**  @addtogroup LEFTPA_module LEFTPA module documentation
**  @{
*/         

/* MODULE LEFTPA. */

#include "LEFTPA.h"

/*
** ===================================================================
**     Method      :  LEFTPA_GetCounterValue (component PulseAccumulator)
*/
/*!
**     @brief
**         This method returns the content of the pulse accumulator
**         counter.
**     @param
**         Value           - Pointer to returned value. [Note:]
**                           Parameter type depends on the width of the
**                           selected counter (may be 8, 16, 32 or 64
**                           bits long). See the method prototype in the
**                           generated module.
*/
/* ===================================================================*/
void LEFTPA_GetCounterValue(LEFTPA_TCounterValue *Value)
{
  *Value = getReg(TMRA_1_CNTR);        /* Return counter value */
}

/*
** ===================================================================
**     Method      :  LEFTPA_Init (component PulseAccumulator)
**
**     Description :
**         Initializes the associated peripheral(s) and the beans 
**         internal variables. The method is called automatically as a 
**         part of the application initialization code.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
void LEFTPA_Init(void)
{
  /* TMRA_1_CTRL: CM=0,PCS=0,SCS=1,ONCE=0,LENGTH=0,DIR=0,COINIT=0,OUTMODE=0 */
  setReg(TMRA_1_CTRL,0x80);            /* Set up mode */
  /* TMRA_1_SCTRL: TCF=0,TCFIE=0,TOF=0,TOFIE=0,IEF=0,IEFIE=0,IPS=0,INPUT=0,CAPTURE_MODE=0,MSTR=0,EEOF=0,VAL=0,FORCE=0,OPS=0,OEN=0 */
  setReg(TMRA_1_SCTRL,0x00);
  setReg(TMRA_1_CNTR,0x00);            /* Reset counter register */
  setReg(TMRA_1_LOAD,0x00);            /* Reset load register */
  setReg(TMRA_1_COMP1,0xFFFF);         /* Set up compare 1 register */
  setReg(TMRA_1_COMP2,0x00);           /* Set up compare 2 register */
  /* TMRA_1_CSCTRL: DBG_EN=0,FAULT=0,ALT_LOAD=0,ROC=0,TCI=0,UP=0,??=0,TCF2EN=0,TCF1EN=0,TCF2=0,TCF1=0,CL2=0,CL1=0 */
  setReg(TMRA_1_CSCTRL,0x00);
  /* TMRA_1_FILT: ??=0,??=0,??=0,??=0,??=0,FILT_CNT=0,FILT_PER=0 */
  setReg(TMRA_1_FILT,0x00);            /* Set up input filter register */
  setRegBitGroup(TMRA_1_CTRL,CM,0x04); /* Run counter */
}

/* END LEFTPA. */

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