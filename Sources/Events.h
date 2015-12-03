/* ###################################################################
**     Filename    : Events.h
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
** @file Events.h
** @version 01.03
** @brief
**         This is user's event module.
**         Put your event handler code here.
*/         
/*!
**  @addtogroup Events_module Events module documentation
**  @{
*/         

#ifndef __Events_H
#define __Events_H
/* MODULE Events */

#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "PE_Timer.h"
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

#include "Type.h"

extern U16 g_nCount1s;
extern U8 g_nFPS,g_nFpsTmp,g_nFPSMax;

void ADC12_InterruptCC(void);

void TMR_OnInterrupt(void);
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


void VS_OnInterrupt(void);
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
void HS_OnInterrupt(void);
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
/*
** ===================================================================
**     Event       :  VideoIn_OnEnd (module Events)
**
**     Component   :  VideoIn [ADC]
**     Description :
**         This event is called after the measurement (which consists
**         of <1 or more conversions>) is/are finished.
**         The event is available only when the <Interrupt
**         service/event> property is enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

/*
** ===================================================================
**     Event       :  ADC12_OnEnd (module Events)
**
**     Component   :  ADC12 [ADC]
**     Description :
**         This event is called after the measurement (which consists
**         of <1 or more conversions>) is/are finished.
**         The event is available only when the <Interrupt
**         service/event> property is enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

/*
** ===================================================================
**     Event       :  VideoIn_OnEnd (module Events)
**
**     Component   :  VideoIn [ADC]
**     Description :
**         This event is called after the measurement (which consists
**         of <1 or more conversions>) is/are finished.
**         The event is available only when the <Interrupt
**         service/event> property is enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

/*
** ===================================================================
**     Event       :  ADC12_OnEnd (module Events)
**
**     Component   :  ADC12 [ADC]
**     Description :
**         This event is called after the measurement (which consists
**         of <1 or more conversions>) is/are finished.
**         The event is available only when the <Interrupt
**         service/event> property is enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

void SCI_OnRxChar(void);
/*
** ===================================================================
**     Event       :  SCI_OnRxChar (module Events)
**
**     Component   :  SCI [AsynchroSerial]
**     Description :
**         This event is called after a correct character is received.
**         The event is available only when the <Interrupt
**         service/event> property is enabled and either the <Receiver>
**         property is enabled or the <SCI output mode> property (if
**         supported) is set to Single-wire mode.
**         Version specific information for Freescale 56800 derivatives
**         DMA mode:
**         If DMA controller is available on the selected CPU and the
**         receiver is configured to use DMA controller then this event
**         is disabled. Only OnFullRxBuf method can be used in DMA mode.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

void VideoIn_OnCalibrationEnd(void);
/*
** ===================================================================
**     Event       :  VideoIn_OnCalibrationEnd (module Events)
**
**     Component   :  VideoIn [ADC]
**     Description :
**         This event is called when the calibration has been finished.
**         User should check if the calibration pass or fail by
**         Calibration status method./nThis event is enabled only if
**         the <Interrupt service/event> property is enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

void DMA_12_OnComplete(void);
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

/* END Events */
#endif /* __Events_H*/

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
