
#include "stm32f10x.h"

#include "spi.h"

uint8_t receivedData;

void SPI1_Init(void);
void SPI1_IRQHandler(void){
	if (SPI_I2S_GetITStatus(SPIx, SPI_I2S_IT_RXNE) == SET)
  {
    receivedData=SPI_I2S_ReceiveData(SPI1);  
		SPI_I2S_ClearITPendingBit(SPI1,SPI_I2S_IT_RXNE);
  }
}
int main(void)
{
    SPI1_Init();
    while (1)
		{
    }
}
