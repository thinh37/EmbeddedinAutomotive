#ifndef __DELAY_H
#define __DELAY_H

#include "stm32f10x.h"
#include <setjmp.h>

void TIM2_INT_Init();

void TIM2_INT_disable();
	
void DelayInit();

void Delay10Ms(uint32_t ms);

void DelayS(uint32_t s);

#endif