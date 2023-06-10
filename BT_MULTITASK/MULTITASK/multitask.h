#ifndef __MULTITASK_H
#define __MULTITASK_H

#include "stm32f10x.h"

typedef struct{
	void (*function)();
	uint32_t time;
	uint32_t delay;
}Task;

void mutilTask(Task *task);

#define LED(PIN) DIO_CHANNEL_PA##PIN
#define CONFIG_LED(PIN)																		\
uint32_t time##PIN;																				\
Dio_LevelType stateLed##PIN = STD_LOW;										\
void blinkLED##PIN(){																			\
	if(stateLed##PIN== STD_LOW) stateLed##PIN= STD_HIGH;		\
	else stateLed##PIN= STD_LOW;														\
	Dio_WriteChannel(LED(PIN),stateLed##PIN);	}
#define INIT_LED(PIN) 	time##PIN=MiliSecond();


#endif