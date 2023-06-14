#include "stm32f10x.h"
#include "Dio.h"
#include "delay.h"

Dio_LevelType SCK_State = STD_LOW;
Dio_LevelType SS_State = STD_HIGH;
char dataTrans = 'A';
char dataTransmit = 'A';
char dataRecei;
char dataReceive;
#define SCK DIO_CHANNEL_PA0
#define MOSI DIO_CHANNEL_PA1
#define MISO DIO_CHANNEL_PA2
#define SS DIO_CHANNEL_PA3
void TIM2_IRQHandler()
{
	if (TIM_GetITStatus(TIM2, TIM_IT_Update))
	{
		if(SS_State == STD_HIGH) SCK_State=STD_LOW;
		else if(SCK_State== STD_HIGH) SCK_State = STD_LOW;
		else SCK_State = STD_HIGH;
		Dio_WriteChannel(SCK,SCK_State);
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	}
}
void Spi_Init(){
	Dio_WriteChannel(SCK,STD_LOW);
	Dio_WriteChannel(MOSI,STD_LOW);
	Dio_WriteChannel(SS,STD_HIGH);
}
void Spi_Master(){
	char temp=0x00;
	Dio_WriteChannel(SS,STD_LOW);
	SS_State = STD_LOW;
	while(SCK_State == STD_LOW);
	for(int i=0;i<8;){
		if(SCK_State==STD_HIGH){
			temp=dataTrans & (char)0x80;
			if(temp == (char)0x80){
				Dio_WriteChannel(MOSI,STD_HIGH);
			}
			else{
				Dio_WriteChannel(MOSI,STD_LOW);
			}
			dataTrans = dataTrans << 1;
			dataRecei = dataRecei <<1;
			while(SCK_State == STD_HIGH){
				dataRecei = dataRecei | Dio_ReadChannel(MISO);
			}
		}
		else{
			i++;
			while(SCK_State == STD_LOW);
		}
	}
	Dio_WriteChannel(SS,STD_HIGH);
	SS_State = STD_HIGH;
}
void delay(uint32_t time){
	for(int i=0;i<time;i++);
}
int main(void ){
	config_output();
	Spi_Init();
	TIM2_INT_Init();
	while(1){
		Spi_Master();
		delay(10000000);
		
		if(dataTransmit== 'Z')  dataTransmit = 'A';
		else dataTransmit++;
    dataTrans=dataTransmit;
		dataReceive=dataRecei;
	}
}



		
