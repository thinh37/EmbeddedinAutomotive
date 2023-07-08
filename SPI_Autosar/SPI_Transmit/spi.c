#include "spi.h"

void Spi_Init(Spi_ConfigType* ConfigPtr)
{
    // Enable the peripheral clock for SPI1
    ConfigPtr->SPI_Direction = SPI_Direction_1Line_Tx; // Transmit only
    ConfigPtr->SPI_Mode = SPI_Mode_Master; // Configure as master
    ConfigPtr->SPI_DataSize = SPI_DataSize_8b; // 8-bit data frame
    ConfigPtr->SPI_CPOL = SPI_CPOL_Low; // Clock polarity: idle state is LOW
    ConfigPtr->SPI_CPHA = SPI_CPHA_1Edge; // Data captured on first clock edge
    ConfigPtr->SPI_NSS = SPI_NSS_Soft; // Software slave management
    ConfigPtr->SPI_FirstBit = SPI_FirstBit_MSB; // MSB transmitted first
    ConfigPtr->SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2; 
    ConfigPtr->SPI_CRCPolynomial = 7; // CRC polynomial is not used
}

Std_ReturnType Spi_WriteIB (Spi_ChannelType Channel,Spi_DataBufferType* DataBufferPtr)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	switch(Channel){
		case SPI_CHANNEL_SP1:
				RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
				SPI_Init(SPI1, &Initstruct);
				RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
			// GPIO pins for MOSI, MISO, and SCK
			GPIO_InitStruct.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_6 | GPIO_Pin_5;
			GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
			GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
			GPIO_Init(GPIOA, &GPIO_InitStruct);
			// GPIO pin for SS
			GPIO_InitStruct.GPIO_Pin = GPIO_Pin_4;
			GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
			GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
			GPIO_Init(GPIOA, &GPIO_InitStruct);
			SPI_Cmd(SPI1, ENABLE);
			GPIO_SetBits(GPIOA,GPIO_Pin_4);
			DelayMs(8000);
			GPIO_ResetBits(GPIOA,GPIO_Pin_4);
			if(DataBufferPtr=='\0') return E_NOT_OK;
			while(1){
			while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET); // Wait until transmit buffer is empty
			SPI_I2S_SendData(SPI1, *DataBufferPtr); // Write data to be transmitted into the SPI data register
			while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET); // Wait until SPI is not busy anymore
			if(*DataBufferPtr=='\0') break;
			else DataBufferPtr++;
			DelayMs(1000);
			}
			return E_OK;
		break;
		case SPI_CHANNEL_SP2:
			RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);
				SPI_Init(SPI2, &Initstruct);
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
			// GPIO pins for MOSI, MISO, and SCK
			GPIO_InitStruct.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
			GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
			GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
			GPIO_Init(GPIOB, &GPIO_InitStruct);
			// GPIO pin for SS
			GPIO_InitStruct.GPIO_Pin = GPIO_Pin_12;
			GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
			GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
			GPIO_Init(GPIOB, &GPIO_InitStruct);
			SPI_Cmd(SPI2, ENABLE);
			GPIO_SetBits(GPIOB,GPIO_Pin_12);
			DelayMs(8000);
			GPIO_ResetBits(GPIOB,GPIO_Pin_12);
			if(DataBufferPtr=='\0') return E_NOT_OK;
			while(1){
			while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET); // Wait until transmit buffer is empty
			SPI_I2S_SendData(SPI2, *DataBufferPtr); // Write data to be transmitted into the SPI data register
			while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_BSY) == SET); // Wait until SPI is not busy anymore
			if(*DataBufferPtr=='\0') break;
			else DataBufferPtr++;
			DelayMs(1000);
			}
			return E_OK;
		break;
	}
}
