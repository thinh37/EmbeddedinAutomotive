#include "stm32f10x.h"
#include "Dio.h"
#include "delay.h"

void blinkled(uint8_t number);
int main(void ){
	config_output();
	DelayInit();
	while(1){
		blinkled(1);
	}
}


void blinkled(uint8_t number){
	uint8_t i;
	uint8_t temp=0x00;
	for(i=0;i<2*number;i++){
			Dio_WriteChannel(DIO_CHANNEL_PA0,setLevel(temp,1<<0));
			Dio_WriteChannel(DIO_CHANNEL_PA1,setLevel(temp,1<<1));
			Dio_WriteChannel(DIO_CHANNEL_PA2,setLevel(temp,1<<2));
			Dio_WriteChannel(DIO_CHANNEL_PA3,setLevel(temp,1<<3));
			Dio_WriteChannel(DIO_CHANNEL_PA4,setLevel(temp,1<<4));
			Dio_WriteChannel(DIO_CHANNEL_PA5,setLevel(temp,1<<5));
			Dio_WriteChannel(DIO_CHANNEL_PA6,setLevel(temp,1<<6));
			Dio_WriteChannel(DIO_CHANNEL_PA7,setLevel(temp,1<<7));
			DelayMs(1000);
			temp=~temp;
	}
}
