#include "spi.h"

void Spi_Init(Spi_ConfigType* ConfigPtr)
{
    ConfigPtr->SPI_Direction = SPI_Direction_1Line_Rx; 
    ConfigPtr->SPI_Mode = SPI_Mode_Slave; 
    ConfigPtr->SPI_DataSize = SPI_DataSize_8b; 
    ConfigPtr->SPI_CPOL = SPI_CPOL_Low; 
    ConfigPtr->SPI_CPHA = SPI_CPHA_1Edge; 
    ConfigPtr->SPI_NSS = SPI_NSS_Soft; 
    ConfigPtr->SPI_FirstBit = SPI_FirstBit_MSB; 
    ConfigPtr->SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2; 
    ConfigPtr->SPI_CRCPolynomial = 7; 

}

Std_ReturnType Spi_ReadIB (Spi_ChannelType Channel,Spi_DataBufferType* DataBufferPointer)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	switch(Channel){
		case SPI_CHANNEL_SP1:
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
    SPI_Init(SPI1, &Initstruct);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
		GPIO_InitStruct.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_6 | GPIO_Pin_5;
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
		GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOA, &GPIO_InitStruct);
	
		GPIO_InitStruct.GPIO_Pin = GPIO_Pin_4;
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
		GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOA, &GPIO_InitStruct);
		SPI_Cmd(SPI1, ENABLE);
		while(1){
    while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET); 
    *DataBufferPointer = SPI_I2S_ReceiveData(SPI1);
		if(*DataBufferPointer=='\0') break;
		DataBufferPointer++;
		}
		return E_OK;
		break;
		case SPI_CHANNEL_SP2:
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);
    SPI_Init(SPI2, &Initstruct);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
		GPIO_InitStruct.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
		GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOB, &GPIO_InitStruct);
	
		GPIO_InitStruct.GPIO_Pin = GPIO_Pin_12;
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
		GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOB, &GPIO_InitStruct);
		SPI_Cmd(SPI2, ENABLE);
		while(1){
    while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET); 
    *DataBufferPointer = SPI_I2S_ReceiveData(SPI2);
		if(*DataBufferPointer=='\0') break;
		DataBufferPointer++;
		}
		return E_OK;
		break;
	}
}