/*
 * Cam.h
 *
 *  Created on: Jul 4, 2014
 *      Author: Administrator
 */

#ifndef CAM_H_
#define CAM_H_

#define IMG_ROWS (66) //max 96
#define IMG_COLS (130) //max 176
#define IMG_STEP 4	//for convenient

#define	IMG_START_ROW 19  //min clear row, 17 for P
#define	IMG_END 283//for 525lines, 304 for P
#define	IMG_USED_BEGIN 2 //1-1+2,+2 for col-2
#define	IMG_USED_END 169 //172-1-2,-2 for col+2
#define IMG_MAX_SLOPE 167 //(IMG_USED_END-IMG_USED_BEGIN)
#define	IMG_USED_PIXEL 172 //(IMG_MAX_SLOPE+5)
#define ROW_MAX 288
#define	COL_MAX 372	//just tell the parameter of the camera

#include "Type.h"

extern U8 g_nCamFrameIndex,g_nNowRow;
extern U8 g_nCamFrameBuffer[IMG_ROWS][IMG_COLS];

void CamInitSystem(void);
void ADC12_Init(void);
void DMA_Init(void);

#endif /* CAM_H_ */
