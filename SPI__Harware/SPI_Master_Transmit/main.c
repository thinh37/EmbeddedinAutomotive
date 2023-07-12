

#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_spi.h"
#include "delay.h"
#include "spi.h"

#define SPIx_RCC				RCC_APB2Periph_SPI1
#define SPIx						SPI1
#define SPI_GPIO_RCC		RCC_APB2Periph_GPIOA
#define SPI_GPIO				GPIOA
#define SPI_PIN_MOSI		GPIO_Pin_7
#define SPI_PIN_MISO		GPIO_Pin_6
#define SPI_PIN_SCK			GPIO_Pin_5
#define SPI_PIN_SS			GPIO_Pin_4

uint8_t sendData = 'a';
void SPI1_IRQHandler(void){
	if (SPI_I2S_GetITStatus(SPIx, SPI_I2S_IT_TXE) == SET)
  {
		SPI_TransmitData(sendData);
		if(sendData == 'z') sendData='a';
	  	else sendData++;
		DelayS(1);
		SPI_I2S_ClearITPendingBit(SPI1,SPI_I2S_IT_TXE);
  }
}
int main(void)
{
    SPI_init();
		while(1){		
		}
}
