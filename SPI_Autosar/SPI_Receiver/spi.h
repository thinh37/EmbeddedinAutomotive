#ifndef __SPI_H
#define __SPI_H

#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_spi.h"
#include "delay.h"

typedef SPI_InitTypeDef Spi_ConfigType;

typedef uint8_t Spi_DataBufferType;
typedef uint8_t Std_ReturnType;
#define E_OK (Std_ReturnType)0
#define E_NOT_OK (Std_ReturnType)1
extern Spi_ConfigType Initstruct;
typedef enum{
	SPI_CHANNEL_SP1,
	SPI_CHANNEL_SP2
}Spi_ChannelType;

void Spi_Init(Spi_ConfigType* ConfigPtr);
Std_ReturnType Spi_ReadIB (Spi_ChannelType Channel,Spi_DataBufferType* DataBufferPointer);

#endif