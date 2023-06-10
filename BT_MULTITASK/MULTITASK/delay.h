#ifndef __DELAY_H
#define __DELAY_H

#include "stm32f10x.h"

void TIM2_INT_Init();

void DelayInit();

void DelayMs(uint32_t ms);

void DelayS(uint32_t s);
	
uint32_t MiliSecond();



#endif