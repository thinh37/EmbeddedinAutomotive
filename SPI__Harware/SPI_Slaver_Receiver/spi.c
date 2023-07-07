#include "spi.h"

void SPI_init(void)
{
    // Enable the peripheral clock for SPI1
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
    NVIC_InitTypeDef NVIC_InitStructure;
    SPI_InitTypeDef spiInitStruct;
		GPIO_InitTypeDef GPIO_InitStruct;
    spiInitStruct.SPI_Direction = SPI_Direction_1Line_Rx; 
    spiInitStruct.SPI_Mode = SPI_Mode_Slave; 
    spiInitStruct.SPI_DataSize = SPI_DataSize_8b; 
    spiInitStruct.SPI_CPOL = SPI_CPOL_Low; 
    spiInitStruct.SPI_CPHA = SPI_CPHA_1Edge; 
    spiInitStruct.SPI_NSS = SPI_NSS_Soft; 
    spiInitStruct.SPI_FirstBit = SPI_FirstBit_MSB; 
    spiInitStruct.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2; 
    spiInitStruct.SPI_CRCPolynomial = 7; 
    
    SPI_Init(SPI1, &spiInitStruct);
	
		RCC_APB2PeriphClockCmd(SPI_GPIO_RCC, ENABLE);
	
		GPIO_InitStruct.GPIO_Pin = SPI_PIN_MOSI | SPI_PIN_MISO | SPI_PIN_SCK;
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
		GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(SPI_GPIO, &GPIO_InitStruct);
	
		GPIO_InitStruct.GPIO_Pin = SPI_PIN_SS;
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
		GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(SPI_GPIO, &GPIO_InitStruct);
		SPI_Cmd(SPI1, ENABLE);
		
		NVIC_InitStructure.NVIC_IRQChannel = SPI1_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority =0;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);
		SPI_I2S_ITConfig(SPIx, SPI_I2S_IT_RXNE, ENABLE);	
		SPI_Cmd(SPI1, ENABLE);

}

uint8_t SPI_ReceiveData(void)
{
    return SPI_I2S_ReceiveData(SPI1);  
}