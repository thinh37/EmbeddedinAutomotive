

#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_spi.h"
#include "delay.h"


#define SPIx_RCC				RCC_APB2Periph_SPI1
#define SPIx						SPI1
#define SPI_GPIO_RCC		RCC_APB2Periph_GPIOA
#define SPI_GPIO				GPIOA
#define SPI_PIN_MOSI		GPIO_Pin_7
#define SPI_PIN_MISO		GPIO_Pin_6
#define SPI_PIN_SCK			GPIO_Pin_5
#define SPI_PIN_SS			GPIO_Pin_4

#include "stm32f10x.h"
uint8_t sendData = 'a';
void SPI1_Init(void);
void SPI1_IRQHandler(void){
	if (SPI_I2S_GetITStatus(SPIx, SPI_I2S_IT_TXE) == SET)
  {
		SPI_I2S_SendData(SPI1, sendData++);
		if(sendData == 'z') sendData='a';
		for(int i=0;i<10000000;i++);
		SPI_I2S_ClearITPendingBit(SPI1,SPI_I2S_IT_TXE);
  }
}
int main(void)
{
    SPI1_Init();
		while(1){		
		}
}
