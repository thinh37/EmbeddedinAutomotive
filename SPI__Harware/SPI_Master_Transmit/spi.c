#include "spi.h"

void SPI1_Init(void)
{
    // Enable the peripheral clock for SPI1
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
    
    SPI_InitTypeDef spiInitStruct;
	GPIO_InitTypeDef GPIO_InitStruct;
	NVIC_InitTypeDef NVIC_InitStructure;
    spiInitStruct.SPI_Direction = SPI_Direction_1Line_Tx; // Transmit only
    spiInitStruct.SPI_Mode = SPI_Mode_Master; // Configure as master
    spiInitStruct.SPI_DataSize = SPI_DataSize_8b; // 8-bit data frame
    spiInitStruct.SPI_CPOL = SPI_CPOL_Low; // Clock polarity: idle state is LOW
    spiInitStruct.SPI_CPHA = SPI_CPHA_1Edge; // Data captured on first clock edge
    spiInitStruct.SPI_NSS = SPI_NSS_Soft; // Software slave management
    spiInitStruct.SPI_FirstBit = SPI_FirstBit_MSB; // MSB transmitted first
    spiInitStruct.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2; // 8MHz SPI clock frequency
    spiInitStruct.SPI_CRCPolynomial = 7; // CRC polynomial is not used
    
    SPI_Init(SPI1, &spiInitStruct);
    
    
	
	RCC_APB2PeriphClockCmd(SPI_GPIO_RCC, ENABLE);
	// GPIO pins for MOSI, MISO, and SCK
	GPIO_InitStruct.GPIO_Pin = SPI_PIN_MOSI | SPI_PIN_MISO | SPI_PIN_SCK;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(SPI_GPIO, &GPIO_InitStruct);
	// GPIO pin for SS
	GPIO_InitStruct.GPIO_Pin = SPI_PIN_SS;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(SPI_GPIO, &GPIO_InitStruct);
	
	NVIC_InitStructure.NVIC_IRQChannel = SPI1_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority =2;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);
		SPI_I2S_ITConfig(SPIx, SPI_I2S_IT_TXE, ENABLE);
		
		SPI_Cmd(SPI1, ENABLE);
}