
#include "stm32f10x.h"

#include "spi.h"

uint8_t receivedData;


void SPI1_IRQHandler(void){
	if (SPI_I2S_GetITStatus(SPIx, SPI_I2S_IT_RXNE) == SET)
  {
    receivedData=SPI_ReceiveData();  
		SPI_I2S_ClearITPendingBit(SPI1,SPI_I2S_IT_RXNE);
  }
}
int main(void)
{
    SPI_init();
    while (1)
		{
    }
}
