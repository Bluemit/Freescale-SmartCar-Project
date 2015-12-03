/* ###################################################################
**     THIS COMPONENT MODULE IS GENERATED BY THE TOOL. DO NOT MODIFY IT.
**     Filename    : KEY.h
**     Project     : ProcessorExpert
**     Processor   : MC56F84786VLK
**     Component   : MultiBitIO
**     Version     : Component 01.000, Driver 01.01, CPU db: 3.50.001
**     Compiler    : CodeWarrior DSP C Compiler
**     Date/Time   : 2015-01-30, 18:37, # CodeGen: 149
**     Abstract    :
**         This bean "MultiBitIO" implements a multi-bit input/output.
**         It assembles alone pins into 1-8bit software port
**     Settings    :
**         Used pin                    :
**             ----------------------------------------------------
**                   Bit     |   Pin   |   Name
**             ----------------------------------------------------
**                    0      |    70   |   GPIOC14/SDA0/XB_OUT4
**                    1      |    68   |   GPIOE7/PWMA_3A/XB_IN5/PWMB_2A
**                    2      |    66   |   GPIOE5/PWMA_2A/XB_IN3
**                    3      |    65   |   GPIOE4/PWMA_2B/XB_IN2
**             ----------------------------------------------------
**
**         Number of bits/pins         : 4
**         Values range                : 0 to 15
**
**         Initial direction           : Input (direction can be changed)
**         Initial output value        : 0 = 000H
**
**     Contents    :
**         GetVal - byte KEY_GetVal(void);
**         GetBit - bool KEY_GetBit(byte Bit);
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
** @file KEY.h
** @version 01.01
** @brief
**         This bean "MultiBitIO" implements a multi-bit input/output.
**         It assembles alone pins into 1-8bit software port
*/         
/*!
**  @addtogroup KEY_module KEY module documentation
**  @{
*/         

#ifndef __KEY_H
#define __KEY_H

/* MODULE KEY. */

/* Include shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
/* Include inherited components */
#include "Inhr5.h"
#include "Inhr6.h"
#include "Inhr7.h"
#include "Inhr8.h"

#include "Cpu.h"




byte KEY_GetVal(void);
/*
** ===================================================================
**     Method      :  KEY_GetVal (component MultiBitIO)
**     Description :
**         Returns the value of the Input/Output bean. Bean calls
**         ancestor's [GetVal] for each bit and composes value
**         according its order. That is [direction] independent, for
**         details look into ancestor documentation.
**     Parameters  : None
**     Returns     :
**         ---             - Input value
** ===================================================================
*/

bool KEY_GetBit(byte Bit);
/*
** ===================================================================
**     Method      :  KEY_GetBit (component MultiBitIO)
**     Description :
**         Returns the value of the specified bit/pin of the
**         Input/Output bean. For specified bit is called ancestor's
**         [GetVal] method. That is [direction] independent, for
**         details look into ancestor documentation. Pins are addressed
**         form zero, where 0 is equaled to LSB.
**     Parameters  :
**         NAME            - DESCRIPTION
**         Bit             - Bit/pin number to read (0 equal LSB)
**     Returns     :
**         ---             - Bit value. Possible values:
**                           FALSE - logical "0" (Low level)
**                           TRUE - logical "1" (High level)
** ===================================================================
*/

/* END KEY. */

#endif /* #ifndef __KEY_H_ */

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
