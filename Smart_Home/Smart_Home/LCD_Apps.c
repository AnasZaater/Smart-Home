#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
#include "Ascii_num.h"
#include "Bit_Op.h"
#include "PINS.h"
#include "LCD.h"
#include "Keypad.h"
#include "LCD_Apps.h"
#include "LED_Dimmer_Buzzer_Alarm.h"
#include "Servo.h"

unsigned char username[4];
unsigned char pass[4];

void LCD_Display_LED (unsigned char room, unsigned char status)
{
	switch(room)
	{
		case '1':
		switch(status)
		{
			case '1':
			LCD_Write_String("Room 1 Led");
			LCD_Send_CMD(Row_2_pos_0);
			LCD_Write_String ("is Turned on");
			break;
			case '0':
			LCD_Write_String("Room 1 Led");
			LCD_Send_CMD(Row_2_pos_0);
			LCD_Write_String ("is Turned Off");
			break;
		}
		break;
		
		case '2':
		switch(status)
		{
			case '1':
			LCD_Write_String("Room 2 Led");
			LCD_Send_CMD(Row_2_pos_0);
			LCD_Write_String ("is Turned on");
			break;
			case '0':
			LCD_Write_String("Room 2 Led");
			LCD_Send_CMD(Row_2_pos_0);
			LCD_Write_String ("is Turned Off");
			break;
		}
		break;
		
		case '3':
		switch(status)
		{
			case '1':
			LCD_Write_String("Room 3 Led");
			LCD_Send_CMD(Row_2_pos_0);
			LCD_Write_String ("is Turned on");
			break;
			case '0':
			LCD_Write_String("Room 3 Led");
			LCD_Send_CMD(Row_2_pos_0);
			LCD_Write_String ("is Turned Off");
			break;
		}
		break;
		
		case '4':
		switch(status)
		{
			case '1':
			LCD_Write_String("Room 4 Led");
			LCD_Send_CMD(Row_2_pos_0);
			LCD_Write_String ("is Turned on");
			break;
			case '0':
			LCD_Write_String("Room 4 Led");
			LCD_Send_CMD(Row_2_pos_0);
			LCD_Write_String ("is Turned Off");
			break;
		}
		break;
		
		case '5':
		switch(status)
		{
			case '1':
			LCD_Write_String("Room 5 Led");
			LCD_Send_CMD(Row_2_pos_0);
			LCD_Write_String ("is Turned on");
			break;
			case '0':
			LCD_Write_String("Room 5 Led");
			LCD_Send_CMD(Row_2_pos_0);
			LCD_Write_String ("is Turned Off");
			break;
		}
		break;
	}
	_delay_ms(1000);
	LCD_Clear_Screen();
}

void LCD_Welcome_Message()
{
	LCD_Write_String ("Welcome to Smart");
	LCD_Send_CMD(Row_2_pos_0);		// Get to the second line
	LCD_Write_String ("Home System");
	_delay_ms(1000);
	LCD_Clear_Screen();
}



	
void LCD_Rooms_Leds_Control()
{
	unsigned char Keypad_Value = 0;	
	unsigned char room_no_temp = 0;
	unsigned char room_on_off_temp = 0;
	
	LCD_Write_String ("Choose a room ");
	_delay_ms(1000);
	LCD_Clear_Screen();
	
	LCD_Write_String ("1. Room 1");
	LCD_Send_CMD(Row_2_pos_0);		// Get to the second line
	LCD_Write_String ("2. Room 2");
	_delay_ms(500);
	LCD_Clear_Screen();
	
	
	LCD_Write_String ("3. Room 3");
	LCD_Send_CMD(Row_2_pos_0);		// Get to the second line
	LCD_Write_String ("4. Room 4");
	_delay_ms(500);
	LCD_Clear_Screen();
	
	
	LCD_Write_String ("5. Room 5");
	LCD_Send_CMD(Row_2_pos_0);		// Get to the second line
	LCD_Write_String ("6. All Rooms");
	_delay_ms(500);
	LCD_Clear_Screen();
	
	LCD_Write_String ("Your Choice : ");
	LCD_Send_CMD(Display_ON_Cusror_ON_Blink_ON);
	
	while(!(Keypad_Value >= Ascii_0	&& Keypad_Value <= Ascii_9))
	{
		Keypad_Value = Keypad_Get_Value();
	}
	
	LCD_Write_Char(Keypad_Value);
	_delay_ms(500);
	LCD_Clear_Screen();
	room_no_temp = Keypad_Value;
	
	while (!((room_no_temp >= Ascii_1) && (room_no_temp <= Ascii_6)))
	{
		LCD_Write_String ("Please Choose");
		LCD_Send_CMD(Row_2_pos_0);
		LCD_Write_String ("from 1 to 6");	
		_delay_ms(1000);
		LCD_Clear_Screen();
		
		Keypad_Value = 0;
		while(!(Keypad_Value >= Ascii_0	&& Keypad_Value <= Ascii_9))
		{
			Keypad_Value = Keypad_Get_Value();
		}
		
		LCD_Write_Char(Keypad_Value);
		_delay_ms(500);
		LCD_Clear_Screen();
		room_no_temp = Keypad_Value;
	}
	
	LCD_Send_CMD(Display_ON_Cusror_OFF_Blink_OFF);
	
	LCD_Write_String ("Turn ON : 1");
	LCD_Send_CMD(Row_2_pos_0);
	LCD_Write_String ("Turn OFF : 0");
	_delay_ms(2000);
	LCD_Clear_Screen();
	
	Keypad_Value = 0;
	while(!(Keypad_Value >= Ascii_0	&& Keypad_Value <= Ascii_9))
	{
		Keypad_Value = Keypad_Get_Value();
	}
	LCD_Write_Char(Keypad_Value);
	_delay_ms(1000);
	LCD_Clear_Screen();
	room_on_off_temp = Keypad_Value;
	
	while ((room_on_off_temp != Ascii_0) && (room_on_off_temp != Ascii_1))
	{
		LCD_Write_String ("Please Choose");
		LCD_Send_CMD(Row_2_pos_0);
		LCD_Set_Cursor(1,3);
		LCD_Write_String ("1 or 0");
		_delay_ms(1000);
		LCD_Clear_Screen();
		
		Keypad_Value = 0;
		while(!(Keypad_Value >= Ascii_0	&& Keypad_Value <= Ascii_9))
		{
			Keypad_Value = Keypad_Get_Value();
		}
		
		LCD_Write_Char(Keypad_Value);
		_delay_ms(500);
		LCD_Clear_Screen();
		room_on_off_temp = Keypad_Value;
	}
	Keypad_Value = 0;
	
	if(room_no_temp == Ascii_6)
	{
		if(room_on_off_temp == Ascii_1)
		{
			LED_STAT(ON,Room1);
			LED_STAT(ON,Room2);
			LED_STAT(ON,Room3);
			LED_STAT(ON,Room4);
			LED_STAT(ON,Room5);
			
			LCD_Write_String("All Leds are ");
			LCD_Send_CMD(Row_2_pos_0);
			LCD_Write_String ("Turned On");
			_delay_ms(1000);
			LCD_Clear_Screen();
		}
		else
		{
			LED_STAT(OFF,Room1);
			LED_STAT(OFF,Room2);
			LED_STAT(OFF,Room3);
			LED_STAT(OFF,Room4);
			LED_STAT(OFF,Room5);
			
			LCD_Write_String("All Leds are ");
			LCD_Send_CMD(Row_2_pos_0);
			LCD_Write_String ("Turned OFF");
			_delay_ms(1000);
			LCD_Clear_Screen();
		}
	}
	else
	{
		LED_STAT(room_on_off_temp,room_no_temp);
		LCD_Display_LED (room_no_temp, room_on_off_temp);
	}
}


void LCD_User_Menu()
{
	LCD_Write_String("1.Control Leds");
	LCD_Send_CMD(Row_2_pos_0);
	LCD_Write_String ("2.Dimming Lamp");
	_delay_ms(500);
	LCD_Clear_Screen();
	
	LCD_Write_String("3.Close the Door");
	LCD_Send_CMD(Row_2_pos_0);
	LCD_Write_String ("4.Logout");
	_delay_ms(500);
	LCD_Clear_Screen();
}



void LCD_User_Interfacing()
{
	unsigned char Keypad_Value = 0;
	unsigned char option = 0;
	unsigned char brightness_level = 0;
	
	while(option != Ascii_4)
	{
		LCD_User_Menu();
		
		LCD_Write_String ("Your Choice : ");
		LCD_Send_CMD(Display_ON_Cusror_ON_Blink_ON);
		
		Keypad_Value = 0;
		while(!(Keypad_Value >= Ascii_0	&& Keypad_Value <= Ascii_9))
		{
			Keypad_Value = Keypad_Get_Value();
			AC_ON();
		}
		
		LCD_Write_Char(Keypad_Value);
		_delay_ms(500);
		LCD_Clear_Screen();
		
		while (!((Keypad_Value >= Ascii_1) && (Keypad_Value <= Ascii_4)))
		{
			
			LCD_Send_CMD(Display_ON_Cusror_ON_Blink_OFF);
			LCD_Write_String ("Please Choose");
			LCD_Send_CMD(Row_2_pos_0);
			LCD_Write_String ("from 1 to 4");
			_delay_ms(1000);
			LCD_Clear_Screen();
			
			LCD_User_Menu();
			LCD_Write_String ("Your Choice : ");
			LCD_Send_CMD(Display_ON_Cusror_ON_Blink_ON);
			
			Keypad_Value = 0;
			while(!(Keypad_Value >= Ascii_0	&& Keypad_Value <= Ascii_9))
			{
				Keypad_Value = Keypad_Get_Value();
				AC_ON();
			}
			
			LCD_Write_Char(Keypad_Value);
			_delay_ms(500);
			LCD_Clear_Screen();
		}
		
		LCD_Send_CMD(Display_ON_Cusror_OFF_Blink_OFF);
		option = Keypad_Value;
		Keypad_Value = 0;
		
		
		if(option == '1')
		{
			LCD_Rooms_Leds_Control();
		}
		else if(option == '2')
		{
			LCD_Write_String ("The Brightness");
			LCD_Send_CMD(Row_2_pos_0);
			LCD_Write_String ("percentages are");
			_delay_ms(500);
			LCD_Clear_Screen();
			
			LCD_Write_String ("0. 0 % (OFF)");
			LCD_Send_CMD(Row_2_pos_0);
			LCD_Write_String ("1. 25 % ");
			_delay_ms(500);
			LCD_Clear_Screen();
			
			LCD_Write_String ("2. 50 % ");
			LCD_Send_CMD(Row_2_pos_0);
			LCD_Write_String ("3. 75 % ");
			_delay_ms(500);
			LCD_Clear_Screen();
			
			LCD_Write_String ("4. 100 % ");
			LCD_Send_CMD(Row_2_pos_0);
			LCD_Write_String ("(Maximum Power)");
			_delay_ms(500);
			LCD_Clear_Screen();
			
			
			LCD_Write_String ("Your Choice : ");
			LCD_Send_CMD(Display_ON_Cusror_ON_Blink_ON);
			
			while(!(Keypad_Value >= Ascii_0	&& Keypad_Value <= Ascii_9))
			{
				Keypad_Value = Keypad_Get_Value();
				AC_ON();
			}
			
			LCD_Write_Char(Keypad_Value);
			_delay_ms(500);
			LCD_Clear_Screen();
			
			while (!((Keypad_Value >= Ascii_0) && (Keypad_Value <= Ascii_4)))
			{
				LCD_Send_CMD(Display_ON_Cusror_ON_Blink_OFF);
				LCD_Write_String ("Please Choose");
				LCD_Send_CMD(Row_2_pos_0);
				LCD_Write_String ("from 0 to 4");
				_delay_ms(1000);
				LCD_Clear_Screen();
				
				LCD_User_Menu();
				LCD_Write_String ("Your Choice : ");
				LCD_Send_CMD(Display_ON_Cusror_ON_Blink_ON);
				
				Keypad_Value = 0;
				while(!(Keypad_Value >= Ascii_0	&& Keypad_Value <= Ascii_9))
				{
					Keypad_Value = Keypad_Get_Value();
					AC_ON();
				}
				
				LCD_Write_Char(Keypad_Value);
				_delay_ms(500);
				LCD_Clear_Screen();
			}
			
			LCD_Send_CMD(Display_ON_Cusror_OFF_Blink_OFF);
			brightness_level = Keypad_Value;
			Keypad_Value = 0;
			
			DIMMER_CONTROL(brightness_level);
		}
		
		
		else if(option == '3')
		{
			closeDoor();
			
			LCD_Write_String("  The door is");
			LCD_Send_CMD(Row_2_pos_0);
			LCD_Write_String("    Closed");
			_delay_ms(1000);
			LCD_Clear_Screen();
		}
		
		else
		{
			
		}
		
	}
}