#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "EEPROM.h"
#include "EEPROM_Apps.h"
#include "App.h"


char Compare_Passwords(unsigned char* pass1 , unsigned char* pass2 , unsigned char Pass_Size)
{
	unsigned char i = 0;
	for(i = 0 ; i<Pass_Size; i++)
	{
		if(pass1[i] != pass2[i])
		{
			return '0';
		}
	}
	
	return '1';
}

void EEPROM_Save_Main_Admin()
{
	EEPROM_writeDataStream(Main_Admin_Block,0,"1111",LOGIN_SIZE);
	_delay_ms(200);
	EEPROM_writeDataStream(Main_Admin_Block,8,"1111",LOGIN_SIZE);
	_delay_ms(200);
}


void EEPROM_Write_0_Counters()
{
	char admin_stored_value = 0;
	char User_uart_stored_value = 0;
	char User_lcd_stored_value = 0;
	
	EEPROM_readByte(BLOCK_7,Admins_number_BIT,&admin_stored_value);
	_delay_ms(10);
	EEPROM_readByte(BLOCK_7,Users_UART_number_BIT,&User_uart_stored_value);
	_delay_ms(10);
	EEPROM_readByte(BLOCK_7,Users_LCD_number_BIT,&User_lcd_stored_value);
	_delay_ms(10);
	
	//admin_stored_value = EEPROM_ReadByte(BLOCK_7,Admins_number_BIT);
	//User_uart_stored_value = EEPROM_ReadByte(BLOCK_7,Users_UART_number_BIT);
	//User_lcd_stored_value = EEPROM_ReadByte(BLOCK_7,Users_LCD_number_BIT);
	
	
	if(admin_stored_value == 0xFF)
	{
		EEPROM_writeByte(BLOCK_7,Admins_number_BIT,0);	// Write 0 on Block_7 bit 0
		_delay_ms(200);
		//EEPROM_WriteByte(BLOCK_7,Admins_number_BIT,0);
	}
	
	if(User_uart_stored_value == 0xFF)
	{
		EEPROM_writeByte(BLOCK_7,Users_UART_number_BIT,0);	// Write 0 on Block_7 bit 1
		_delay_ms(200);
		//EEPROM_WriteByte(BLOCK_7,Users_UART_number_BIT,0);
	}
	
	if(User_lcd_stored_value == 0xFF)
	{
		EEPROM_writeByte(BLOCK_7,Users_LCD_number_BIT,0);	// Write 0 on Block_7 bit 1
		_delay_ms(200);
		//EEPROM_WriteByte(BLOCK_7,Users_LCD_number_BIT,0);
	}
	
}

