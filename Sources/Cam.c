/*
 * AFE.c
 *
 *  Created on: Jul 4, 2014
 *      Author: Administrator
 */
#include "VS.h"
#include "HS.h"
#include "Cam.h"
#include "IO_Map.h"

U8 g_nCamFrameIndex,g_nNowRow;
U8 g_nCamFrameBuffer[IMG_ROWS][IMG_COLS];

void CamInitSystem(void)
{
	// events
	VS_Enable();
	HS_Enable();
	
}

void ADC12_Init(void)
{
  volatile word i;
  //Vector.c:  JSR  ADC12_InterruptCC               /* Interrupt no. 30 (Unused) - ivINT_ADC12_CC0  */
  SIM_PCE0|=0x1<<6|0x1<<5;//open IPBus for GPIOA& GPIOB, must be ahead of GPIO register config.!
  GPIOA_PER|=0x1<<0;//open gpioA0/ANA0
  GPIOB_PER|=0x1<<3;//open gpioB3/ANB3
  //SIM_PCE0&=~(0x1<<6|0x1<<5);//close IPBus for GPIOA& GPIOB, if no need to configure GPIO reg.!here we use A1&A0's Interrupt,so keep open!
  SIM_PCE2|=0x1<<7;//open IPBus for Cyclic ADC or ADC12
  INTC_IPR2|=0b11<<10;//ADC_CC0 priority 2
  /* ADC12_CTRL1: DMAEN0=1,STOP0=1,START0=0,SYNC0=0,EOSIE0=0,ZCIE=0,LLMTIE=0,HLMTIE=0,CHNCFG_L=0,??=0,SMODE=0 */
  ADC12_CTRL1=0xC000U;         /* Set control register 1 */
  /* ADC12_CTRL3: ??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,DMASRC=1,SCNT1=0,SCNT0=0 */
  ADC12_CTRL3=0x40U;           /* Set control register 3 */
  /* ADC12_CAL: SEL_VREFH_B=0,SEL_VREFLO_B=0,SEL_VREFH_A=0,SEL_VREFLO_A=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,SEL_DAC_B=0,SEL_DAC_A=0 */
  ADC12_CAL=0x00U;             /* Set calibration register */
  /* ADC12_PWR: ASB=0,??=0,??=0,??=0,PSTS1=0,PSTS0=0,PUDELAY=0x0D,APD=0,??=0,PD1=0,PD0=0 */
  ADC12_PWR=0xD0U;             /* Enable device */
  /* ADC12_OFFST0: ??=0,OFFSET=0,??=0,??=0,??=0 */
  ADC12_OFFST0=0x00U;          /* Set offset reg. 0 */
  /* ADC12_OFFST1: ??=0,OFFSET=0,??=0,??=0,??=0 */
  ADC12_OFFST1=0x00U;          /* Set offset reg. 1 */
  /* ADC12_HILIM0: ??=0,HLMT=0x0FFF,??=0,??=0,??=0 */
  ADC12_HILIM0=0x7FF8U;        /* Set high limit reg. 0 */
  /* ADC12_HILIM1: ??=0,HLMT=0x0FFF,??=0,??=0,??=0 */
  ADC12_HILIM1=0x7FF8U;        /* Set high limit reg. 1 */
  /* ADC12_LOLIM0: ??=0,LLMT=0,??=0,??=0,??=0 */
  ADC12_LOLIM0=0x00U;          /* Set low limit reg. 0 */
  /* ADC12_LOLIM1: ??=0,LLMT=0,??=0,??=0,??=0 */
  ADC12_LOLIM1=0x00U;          /* Set low limit reg. 1 */
  /* ADC12_ZXSTAT: ZCS=0xFFFF */
  ADC12_ZXSTAT=0xFFFF;         /* Clear zero crossing status flags */
  /* ADC12_LOLIMSTAT: LLS=0xFFFF */
  ADC12_LOLIMSTAT=0xFFFF;      /* Clear high and low limit status */
  /* ADC12_STAT: CIP0=0,CIP1=0,??=0,EOSI1=0,EOSI0=1,ZCI=0,LLMTI=0,HLMTI=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0 */
  ADC12_STAT=0x0800;           /* Clear EOSI flag */
  /* ADC12_SDIS: DS=0xFFFE */
  ADC12_SDIS=0xFFFEU;          /* Enable/disable of samples */
  /* ADC12_ZXCTRL1: ZCE7=0,ZCE6=0,ZCE5=0,ZCE4=0,ZCE3=0,ZCE2=0,ZCE1=0,ZCE0=0 */
  ADC12_ZXCTRL1=0x00U;         /* Set zero crossing control reg. */
  /* ADC12_ZXCTRL2: ZCE15=0,ZCE14=0,ZCE13=0,ZCE12=0,ZCE11=0,ZCE10=0,ZCE9=0,ZCE8=0 */
  ADC12_ZXCTRL2=0x00U;         /* Set zero crossing control reg. */
  /* ADC12_CTRL2: DMAEN1=0,STOP1=0,START1=0,SYNC1=0,EOSIE1=0,CHNCFG_H=0,SIMULT=1,DIV0=19 means PLL400/20=20M, here use 50M*/
  ADC12_CTRL2=0x47U;           /* Set prescaler */
  /* ADC12_PWR2: ??=0,??=0,DIV1=0,??=0,??=0,??=0,??=0,SPEEDB=0,SPEEDA=3 */
  ADC12_PWR2=0x03U;          
  for (i=0U;i<0x64U;i++) {}            /* Recovery time of voltage reference */
  while (ADC12_PWR&((ADC12_PWR_PSTS0_MASK|ADC12_PWR_PSTS1_MASK))) {} /* Wait for device powered up */
  ADC12_CLIST1=0x00;//select ANA0
  ADC12_CTRL1&=~0x7;//clear SMODE
  ADC12_CTRL1|=0b010;//loop sequential
  ADC12_CTRL1|=0x4000;//stop loop
}

void DMA_Init(void)
{
	//Notice Address must uses Byte address, which means (unsigned long)(unsigned char*)&u16Tmp
	//a special usage:want high 8bit of a 16bit(MCU) register, use (unsigned long)((unsigned char*)&u8Tmp+1)
	//c basic knowledge:array_2 means &array_2[0][0], differ from &array_2(differ in +1)
	//Block length means bytes(per transfer 1 byte) needed to be transferred
	//Single transfer means only one trigger will consumes all BCR while cyle-steal need every trigger to consume them all
	//BCR=0 means complete!and this register needs user's restall!
}
