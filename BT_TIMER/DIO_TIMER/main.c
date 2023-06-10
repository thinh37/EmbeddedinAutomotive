#include "stm32f10x.h"
#include "Dio.h"
#include "delay.h"
extern uint32_t Ticks;
extern uint16_t dem;
extern jmp_buf buf;

void blinkled(uint8_t number);
void stopled();
void sangduoi(uint8_t number);
void TIM2_IRQHandler()
{
	if (TIM_GetITStatus(TIM2, TIM_IT_Update))
	{
		
		if (Ticks != 0)
		{
				Ticks--;
				
		}
		if(Dio_ReadChannel(DIO_CHANNEL_PA8)==STD_LOW){
				while(Dio_ReadChannel(DIO_CHANNEL_PA8)==STD_LOW);
				if(dem==2) dem=0;
				else dem++;
		}
		
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	}
}


int main(void ){
	config_output();
	int temp=0;
	temp= setjmp(buf);
	while(1){
	
		if(dem==1) blinkled(5);
		else if(dem==2) sangduoi(3);
		else if(dem==0) stopled();
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
			DelayS(1);
			temp=~temp;
	}
				while(Dio_ReadChannel(DIO_CHANNEL_PA8)==STD_HIGH);
				while(Dio_ReadChannel(DIO_CHANNEL_PA8)==STD_LOW);
				dem=2;
				longjmp(buf,1);
}
void stopled(){
	uint8_t temp=0x00;
			Dio_WriteChannel(DIO_CHANNEL_PA0,setLevel(temp,1<<0));
			Dio_WriteChannel(DIO_CHANNEL_PA1,setLevel(temp,1<<1));
			Dio_WriteChannel(DIO_CHANNEL_PA2,setLevel(temp,1<<2));
			Dio_WriteChannel(DIO_CHANNEL_PA3,setLevel(temp,1<<3));
			Dio_WriteChannel(DIO_CHANNEL_PA4,setLevel(temp,1<<4));
			Dio_WriteChannel(DIO_CHANNEL_PA5,setLevel(temp,1<<5));
			Dio_WriteChannel(DIO_CHANNEL_PA6,setLevel(temp,1<<6));
			Dio_WriteChannel(DIO_CHANNEL_PA7,setLevel(temp,1<<7));
			DelayS(1);
	longjmp(buf,1);
}
void sangduoi(uint8_t number){
	uint8_t i,j;
	uint8_t temp;
	for(i=0;i<number;i++){
		temp=0x1;
		for(j=0;j<8;j++){
			Dio_WriteChannel(DIO_CHANNEL_PA0,setLevel(temp,1<<0));
			Dio_WriteChannel(DIO_CHANNEL_PA1,setLevel(temp,1<<1));
			Dio_WriteChannel(DIO_CHANNEL_PA2,setLevel(temp,1<<2));
			Dio_WriteChannel(DIO_CHANNEL_PA3,setLevel(temp,1<<3));
			Dio_WriteChannel(DIO_CHANNEL_PA4,setLevel(temp,1<<4));
			Dio_WriteChannel(DIO_CHANNEL_PA5,setLevel(temp,1<<5));
			Dio_WriteChannel(DIO_CHANNEL_PA6,setLevel(temp,1<<6));
			Dio_WriteChannel(DIO_CHANNEL_PA7,setLevel(temp,1<<7));
			DelayS(1);
			temp=temp<<1;
		}
	}
				while(Dio_ReadChannel(DIO_CHANNEL_PA8)==STD_HIGH);
				while(Dio_ReadChannel(DIO_CHANNEL_PA8)==STD_LOW);	
				dem=0;
				longjmp(buf,1);
}
