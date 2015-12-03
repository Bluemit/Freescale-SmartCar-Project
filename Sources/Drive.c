/*
 * Drv.c
 *
 *  Created on: Jul 7, 2014
 *      Author: ZZH
 */
#include "World.h"
#include "Events.h"
#include "IO_Map.h"

void DRV_PWM_SetRatio16(u8 channel,s16 ratio)//-32768~32767, 0 is 50%
{
	switch (channel){
	case 0:
		if (ratio>0){
			if (ratio<32767-MOTOR0_DEAD_ZONE_GO) ratio=ratio+MOTOR0_DEAD_ZONE_GO;
			else ratio=32767;
		}else if (ratio<0){
			if (ratio>-32768+MOTOR0_DEAD_ZONE_BACK) ratio=ratio-MOTOR0_DEAD_ZONE_BACK;
			else ratio=-32768;
		}
		PWMA_SM0VAL3=((u32)(PWMA_SM0VAL1+1)*(ratio+32768))>>16;// Calculate new value according to the given ratio
		PWMA_MCTRL|=0x1;         // Load counter and modulo registers into buffers
		break;
	case 1:
		if (ratio>0){
			if (ratio<32767-MOTOR1_DEAD_ZONE_GO) ratio=(ratio+MOTOR1_DEAD_ZONE_GO);//*108/100;
			else ratio=32767;
		}else if (ratio<0){
			if (ratio>-32768+MOTOR1_DEAD_ZONE_BACK) ratio=(ratio-MOTOR1_DEAD_ZONE_BACK);//*108/100;
			else ratio=-32768;
		}
		PWMA_SM1VAL3=((u32)(PWMA_SM1VAL1+1)*(ratio+32768))>>16;
		PWMA_MCTRL|=0x2;         //sub1 reload
		break;
	}
}
void DRV_PWM_Init(void){
	SIM_PCE0|=0x1<<2;//open IPBus for GPIOE, must be ahead of GPIO register configuration!
	GPIOE_PER|=0x0F;//open gpioe1&gpioe0 & gpioe3&gpioe2
	SIM_PCE3|=0x3<<6;//open IPBus for PWMA Channel0&1!
	clrSetReg16Bits(PWMA_DTSRCSEL, 0x00AA, 0x0055);//SM0SEL23 & SM0SEL45 uses deadtime logic(sub~0&1), both inverted((0xA,0x5),uninverted use (0xC,0x0))
	PWMA_SM0CTRL2=0xD840;//use IPBus for clock!
	// PWMA_SM0CTRL2: DBGEN=1,WAITEN=1,INDEP=0,PWM23_INIT=1,PWM45_INIT=1,PWMX_INIT=0,INIT_SEL=0,FRCEN=0,FORCE=1,FORCE_SEL=0,RELOAD_SEL=0,CLK_SEL=0
	PWMA_SM1CTRL2=0xD840;
	PWMA_SM0DISMAP0=0x00;//all fault 0-3A/B/X don't(0) cause disabled output
	PWMA_SM1DISMAP0=0x00;
	//PWMA_SM0OCTRL=0x00;//All not invert & when fault output logic 0
	//PWMA_SM1OCTRL=0x00;
	//PWMA_SM0FRCTRL=0x00;//All fraction method is disabled
	//PWMA_SM1FRCTRL=0x00;
	PWMA_SM0DTCNT0=0x00;// Deadtime for PWM_A is 0
	PWMA_SM1DTCNT0=0x00;
	PWMA_SM0DTCNT1=0x00;// Deadtime for PWM_B is 0
	PWMA_SM1DTCNT1=0x00;
	PWMA_SM0INIT=0x00;// PWMA_SM0INIT: INIT=0
	PWMA_SM1INIT=0x00;
	PWMA_SM0VAL2=0x00;// PWMA_SM0VAL2: VAL2=0
	PWMA_SM1VAL2=0x00;
	PWMA_SM0VAL3=0x09C4;// PWMA_SM0VAL3: VAL3=0x09C4; 25us or 50% at first
	PWMA_SM1VAL3=0x09C4;
	/*PWMA_SM0VAL4=0x09C4;        
	PWMA_SM0VAL5=0x1387;*/
	PWMA_SM0VAL1=0x1387;// PWMA_SM0VAL1: VAL1=0x1387; 0x1387/100MHz=50us
	PWMA_SM1VAL1=0x1387;
	//PWMA_SM0CTRL&=~0x70;// Set prescaler register according to the selected high speed CPU mode
	//PWMA_SM1CTRL&=~0x70
	PWMA_MCTRL|=0x0303;// PWMA_MCTRL: LDOK|=3(reload) & RUN|=3(run) & IPOL=00b; submodule is PWMA_0X & PWMA_1X    
	//PWMA_MASK&=~0x0330;//not mask PWMA/B_0/1x
	PWMA_OUTEN|=0x0330;//output enable PWMA/B_0/1x
	//PWMA_SM0STS|=0x1000;//clear reload Flag
}
