#include "delay.h"

TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
NVIC_InitTypeDef NVIC_InitStruct;
uint32_t Ticks;
uint16_t dem = 0;
jmp_buf buf;

void TIM2_INT_Init()
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	
	TIM_TimeBaseInitStruct.TIM_Prescaler = 3600;
	TIM_TimeBaseInitStruct.TIM_Period = 200;
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStruct);
	
	
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
	
	TIM_Cmd(TIM2, ENABLE);
	
	
	NVIC_InitStruct.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0x00;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0x00;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStruct);
}

void TIM2_INT_disable(){
	NVIC_InitStruct.NVIC_IRQChannelCmd = DISABLE;
	NVIC_Init(&NVIC_InitStruct);
}

void DelayInit(){
	TIM2_INT_Init();
}

void Delay10Ms(uint32_t ms)
{
	Ticks = ms;
	int temp=dem;
	while (Ticks){
		if(temp!=dem) {
			TIM2_INT_disable();
			longjmp(buf,1);
		}
	}
}
void DelayS(uint32_t s)
{
	DelayInit();
	while (s--)
	{
		Delay10Ms(100);
	}
	TIM2_INT_disable();
}


	

