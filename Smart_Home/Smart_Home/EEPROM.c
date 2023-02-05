
#include <avr/io.h>
#define F_CPU 16000000UL
#include "EEPROM.h"
#include <string.h>
#include "I2C_Master.h"
#include <util/delay.h>

void EEPROM_Initialization(void) //Initialize EEPROM --> starting I2C communication
{
	I2C_Initialization();
}

void EEPROM_writeByte(char EEPROM_Block,char EEPROM_Address,char Data) //Writes a byte in an EEPROM block
{
	I2C_Start(EEPROM_Block);
	I2C_Write(EEPROM_Address);
	_delay_ms(10);
	I2C_Write(Data);
	_delay_ms(10);
	I2C_Stop();
}

void EEPROM_readByte(char EEPROM_Block,char EEPROM_Address,char *Data) //Reads a byte in an EEPROM
{
	I2C_Start(EEPROM_Block);
	I2C_Write(EEPROM_Address);
	I2C_Repeated_Start(EEPROM_Block+1);
	*Data = I2C_Read_Nack();
	_delay_ms(10);
	I2C_Stop();
}

void EEPROM_readDatastream(char EEPROM_Block,char EEPROM_Address,char *Data,char DataSize) //Reads an array of data in EEPROM and stores it in an array
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

