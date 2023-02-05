
#include <avr/io.h>
#define F_CPU 16000000UL
#include "EEPROM.h"
#include <string.h>
#include "I2C_Master.h"
#include <util/delay.h>

void EEPROM_Initialization(void)
{
	I2C_Initialization();
}

void EEPROM_writeByte(char EEPROM_Block,char EEPROM_Address,char Data)
{
	//I2C_START_Transmitter_Receiver_Mode(EEPROM_Block,Master_Transmitter_Mode);
	I2C_Start(EEPROM_Block);
	I2C_Write(EEPROM_Address);
	_delay_ms(10);
	I2C_Write(Data);
	_delay_ms(10);
	I2C_Stop();
}

void EEPROM_readByte(char EEPROM_Block,char EEPROM_Address,char *Data)
{
	//I2C_START_Transmitter_Receiver_Mode(EEPROM_Block,Master_Transmitter_Mode);
	I2C_Start(EEPROM_Block);
	I2C_Write(EEPROM_Address);
	//I2C_Repeated_START_Transmitter_Receiver_Mode(EEPROM_Block+1,Master_Receiver_Mode);
	I2C_Repeated_Start(EEPROM_Block+1);
	*Data = I2C_Read_Nack();
	_delay_ms(10);
	I2C_Stop();
}


void EEPROM_writeDataStream(char EEPROM_Block,char EEPROM_Address,char *Data,char DataSize)
{
	char loopingVar;
	//Checking if the write  size is more than page size or not
	if (DataSize > EEPROM_PAGE_SIZE)
	{
		loopingVar = EEPROM_PAGE_SIZE ;//setting the page size as default
	}
	else
	{
		loopingVar = DataSize;
	}
	
	I2C_Start(EEPROM_Block);
	I2C_Write(EEPROM_Address);
	_delay_ms(10);
	
	while(loopingVar)
	{
		I2C_Write(*Data);
		Data++;
		loopingVar--;
	}
	_delay_ms(10);
	I2C_Stop();
}

void EEPROM_readDatastream(char EEPROM_Block,char EEPROM_Address,char *Data,char DataSize)
{
	I2C_Start(EEPROM_Block);
	I2C_Write(EEPROM_Address);
	I2C_Repeated_Start(EEPROM_Block+1);
	
	while(DataSize)
	{
		*Data = I2C_Read_Ack();
		_delay_ms(10);
		Data++;
		DataSize--;
	}
	_delay_ms(10);
	I2C_Stop();
}

