#include "stm32f10x.h"
#include "spi.h"
Spi_ConfigType Initstruct;
int main(void)
{
		uint8_t *sendData = (uint8_t*)"Quach Minh Thinh";
		DelayInit();
    Spi_Init(&Initstruct);
		while(1){
			Spi_WriteIB(SPI_CHANNEL_SP2,sendData);
		}
	}
