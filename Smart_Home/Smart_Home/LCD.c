#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "Bit_Op.h"
#include "PINS.h"
#include "LCD.h"



void LCD_Send_CMD (unsigned char data)
{
	#if LCD_Mode == 4
	LCD_Port =  ((LCD_Port & (0x0F)) | (data & (0xF0)));	// sending upper nibble
	clear_bit(LCD_Control_Pins_Port,RS);
	clear_bit(LCD_Control_Pins_Port,RW);
	set_bit(LCD_Control_Pins_Port,EN);
	_delay_us(1);
	clear_bit(LCD_Control_Pins_Port,EN);
	_delay_us(200);
	LCD_Port = ((LCD_Port & (0x0F)) | (data<<4));			// sending lower nibble
	set_bit(LCD_Control_Pins_Port,EN);
	_delay_us(1);
	clear_bit(LCD_Control_Pins_Port,EN);
	_delay_ms(2);
	
	#elif LCD_Mode == 8
	LCD_Port = data;
	clear_bit(LCD_Control_Pins_Port,RS);
	clear_bit(LCD_Control_Pins_Port,RW);
	set_bit(LCD_Control_Pins_Port,EN);
	_delay_ms(2);
	clear_bit(LCD_Control_Pins_Port,EN);
	
	#endif
}

void LCD_Init()
{
	// Enabling Control Pins
	set_bit(LCD_Control_Pins_Dir,RS);	
	set_bit(LCD_Control_Pins_Dir,RW);	
	set_bit(LCD_Control_Pins_Dir,EN);
	
	clear_bit(LCD_Control_Pins_Port,RS);
	clear_bit(LCD_Control_Pins_Port,RW);
	clear_bit(LCD_Control_Pins_Port,EN);
	
	#if LCD_Mode == 4
	set_bit(LCD_Dir,LCD_D4);
	set_bit(LCD_Dir,LCD_D5);
	set_bit(LCD_Dir,LCD_D6);
	set_bit(LCD_Dir,LCD_D7);
	
	clear_bit(LCD_Port,LCD_D4);
	clear_bit(LCD_Port,LCD_D5);
	clear_bit(LCD_Port,LCD_D6);
	clear_bit(LCD_Port,LCD_D7);
	
	LCD_Send_CMD(Return_Home); // Return Home
	_delay_ms(1);
	LCD_Send_CMD(Mode_4_Bit_2_Line_5x8_dots); // 4 bit mode
	_delay_ms(1);
	LCD_Send_CMD(Clear_Display); // Clear display
	_delay_ms(1);
	LCD_Send_CMD(Display_ON_Cusror_OFF_Blink_OFF); // Display ON/OFF Control
	_delay_ms(1);
	LCD_Send_CMD(Cusror_shifts_right);	// Entry set mode (cursor moves to the right)
	_delay_ms(1);
	
	#elif LCD_Mode == 8
	set_bit(LCD_Dir,LCD_D0);
	set_bit(LCD_Dir,LCD_D1);
	set_bit(LCD_Dir,LCD_D2);
	set_bit(LCD_Dir,LCD_D3);
	set_bit(LCD_Dir,LCD_D4);
	set_bit(LCD_Dir,LCD_D5);
	set_bit(LCD_Dir,LCD_D6);
	set_bit(LCD_Dir,LCD_D7);
	
	clear_bit(LCD_Port,LCD_D0);
	clear_bit(LCD_Port,LCD_D1);
	clear_bit(LCD_Port,LCD_D2);
	clear_bit(LCD_Port,LCD_D3);
	clear_bit(LCD_Port,LCD_D4);
	clear_bit(LCD_Port,LCD_D5);
	clear_bit(LCD_Port,LCD_D6);
	clear_bit(LCD_Port,LCD_D7);
	
	LCD_Send_CMD(Return_Home); // Return Home
	_delay_ms(1);
	LCD_Send_CMD(Mode_8_Bit_2_Line_5x8_dots); // 4 bit mode
	_delay_ms(1);
	LCD_Send_CMD(Clear_Display); // Clear display
	_delay_ms(1);
	LCD_Send_CMD(Display_ON_Cusror_OFF_Blink_OFF); // Display ON/OFF Control
	_delay_ms(1);
	LCD_Send_CMD(Cusror_shifts_right);	// Entry set mode (cursor moves to the right)
	_delay_ms(1);
	#endif
}

void LCD_Write_Char (unsigned char data)
{
	#if LCD_Mode == 4
	LCD_Port =  ( (LCD_Port & (0x0F)) | (data & (0xF0)) );	// sending upper nibble
	set_bit(LCD_Control_Pins_Port,RS);
	clear_bit(LCD_Control_Pins_Port,RW);
	set_bit(LCD_Control_Pins_Port,EN);
	_delay_us(1);
	clear_bit(LCD_Control_Pins_Port,EN);
	_delay_us(200);
	LCD_Port = ((LCD_Port & (0x0F)) | (data<<4));				// sending lower nibble
	set_bit(LCD_Control_Pins_Port,EN);
	_delay_us(1);
	clear_bit(LCD_Control_Pins_Port,EN);
	_delay_ms(2);
	
	#elif LCD_Mode == 8
	LCD_Port = data;
	set_bit(LCD_Control_Pins_Port,RS);
	clear_bit(LCD_Control_Pins_Port,RW);
	set_bit(LCD_Control_Pins_Port,EN);
	_delay_ms(2);
	clear_bit(LCD_Control_Pins_Port,EN);
	#endif
}


void LCD_Write_String (char* text)
{
	unsigned char j=0;
	while(text[j] != '\0')	// Looping on the elements of array till the NULL character
	{	
		LCD_Write_Char(text[j]);
		_delay_ms(50);
		j++;
	}
}

void LCD_Set_Cursor(char row, char pos)
{
	char address = 0;
	if (row < 2 && pos<16)
	{
		address = (row * 0x40) + pos;
		address |= (1<<7);
		LCD_Send_CMD(address);
	}
}

void LCD_Clear_Screen()
{
	LCD_Send_CMD(Clear_Display);
}

void LCD_Write_Integer(unsigned long int data)
{
	int num = 0, multiplier = 1, i = 0;
	if(!data)
	{
		LCD_Write_Char('0');
	}
	else if(data < 0)
	{
		LCD_Write_Char('-');
		data *= -1;
	}
	while(data)
	{
		num = (num*10) + (data%10);
		
		if(!num)
		multiplier *= 10;
		
		data /= 10;
	}
	while(num != i)
	{
		LCD_Write_Char(num%10 + 48);
		num /= 10;
		
		if(!num && multiplier >= 10)
		{
			i = 1;
			num = multiplier;
		}
	}
}

void LCD_Write_Decimal(float data)
{
	unsigned long int num = 0;
	num = data;
	LCD_Write_Integer(num);
	LCD_Write_Char('.');
	data -= num;
	for(unsigned int i = 0; i < 3; i++)
	{
		data *= 10;
		num = data;
		LCD_Write_Char(num + 48);
		data -= num;
	}
}