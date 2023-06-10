#include "stm32f10x.h"
#include "Dio.h"
#include "delay.h"
#include "multitask.h"

CONFIG_LED(0);
CONFIG_LED(1);
CONFIG_LED(2);
CONFIG_LED(3);
CONFIG_LED(4);
CONFIG_LED(5);
CONFIG_LED(6);
CONFIG_LED(7);

int main(void ){
	config_output();
	DelayInit();
	INIT_LED(0);
	INIT_LED(1);
	INIT_LED(2);
	INIT_LED(3);
	INIT_LED(4);
	INIT_LED(5);
	INIT_LED(6);
	INIT_LED(7);
	Task led0={.function=&blinkLED0,.time=time0,.delay=1000};
	Task led1={.function=&blinkLED1,.time=time1,.delay=2000};
	Task led2={.function=&blinkLED2,.time=time2,.delay=4000};
	Task led3={.function=&blinkLED3,.time=time3,.delay=8000};
	Task led4={.function=&blinkLED4,.time=time4,.delay=16000};
	Task led5={.function=&blinkLED5,.time=time5,.delay=32000};
	Task led6={.function=&blinkLED6,.time=time6,.delay=64000};
	Task led7={.function=&blinkLED7,.time=time7,.delay=128000};
	while(1){
		mutilTask(&led0);
		mutilTask(&led1);
		mutilTask(&led2);
		mutilTask(&led3);
		mutilTask(&led4);
		mutilTask(&led5);
		mutilTask(&led6);
		mutilTask(&led7);
	}
}



		