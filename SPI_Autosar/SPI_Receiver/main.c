
#include "stm32f10x.h"
#include "spi.h"


Spi_ConfigType Initstruct;
Spi_DataBufferType receivedData[16]; 

int main(void)
{
		DelayInit();
    Spi_Init(&Initstruct);
    
    while (1)
    {
					Spi_ReadIB(SPI_CHANNEL_SP2,receivedData);
         
    }
}


