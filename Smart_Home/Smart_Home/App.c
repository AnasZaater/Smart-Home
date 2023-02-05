#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include  "string.h"
#include "Ascii_num.h"
#include "Bit_Op.h"
#include "PINS.h"
#include "LCD.h"
#include "Keypad.h"
#include "LED_Dimmer_Buzzer_Alarm.h"
#include "UART.h"
#include "AC.h"
#include "Servo.h"
#include "TimerFunc.h"
#include "App.h"
#include "ADC.h"
#include "Interrupt_Start.h"
#include "UART_Apps.h"
#include "EEPROM.h"
#include "EEPROM_Apps.h"
#include "LCD_Apps.h"



ISR(INT0_vect)
{
	unsigned char Keypad_Value = 0;
	char user_counter = 0;
	unsigned char trials = 3;
	char username_arr[4];		// array filled by user interface (ADMIN/USER)
	char password_arr[4];		// array filled by user interface (ADMIN/USER)
	char username_temp_arr[4];	// array taken from EEPROM to compare
	char password_temp_arr[4];	// array taken from EEPROM to compare
	unsigned char looping_counter = 0;
	unsigned char Compare_Var = 0;
	
	LCD_Welcome_Message();
	
	EEPROM_readByte(Counters_Block,Users_LCD_number_BIT,&user_counter);
	_delay_ms(10);
	
	trials = 3;
	while(trials>=1 && trials<=3)
	{
			//-----------------	Writing the username -----------------
			LCD_Write_String("Username : ");
			LCD_Send_CMD(Display_ON_Cusror_ON_Blink_OFF);
			looping_counter = 0;
			while(looping_counter < 4)
			{
				while(!(Keypad_Value >= Ascii_0	&& Keypad_Value <= Ascii_9))
				{
					Keypad_Value = Keypad_Get_Value();
				}
				
				username_arr[looping_counter] = Keypad_Value;
				if(looping_counter == 3)
				{
					LCD_Send_CMD(Display_ON_Cusror_OFF_Blink_OFF);
				}
				LCD_Write_Char(Keypad_Value);
				_delay_ms(300);
				looping_counter++;
				Keypad_Value = 0;
			}
			_delay_ms(500);
			LCD_Clear_Screen();
			looping_counter = 0;
			
			//-----------------	Writing the password -----------------
			
			LCD_Write_String ("Password: ");
			LCD_Send_CMD(Display_ON_Cusror_ON_Blink_OFF);
			
			while(looping_counter < 4)
			{
				while(!(Keypad_Value >= Ascii_0	&& Keypad_Value <= Ascii_9))
				{
					Keypad_Value = Keypad_Get_Value();
				}
				
				password_arr[looping_counter] = Keypad_Value;
				if(looping_counter == 3)
				{
					LCD_Send_CMD(Display_ON_Cusror_OFF_Blink_OFF);
				}
				LCD_Write_Char(Keypad_Value);
				_delay_ms(400);
				LCD_Set_Cursor(0,strlen("Password: ") + looping_counter);
				LCD_Write_Char('*');
				_delay_ms(100);
				looping_counter++;
				Keypad_Value = 0;
			}
			_delay_ms(500);
			LCD_Clear_Screen();
			looping_counter = 0;
		for (looping_counter = 0; looping_counter < user_counter; looping_counter++)
		{			
			for(char i = 0; i<LOGIN_SIZE; i++)
			{
				EEPROM_readByte(LCD_User_Username_Block,(4*looping_counter)+i,&username_temp_arr[i]);
				_delay_ms(10);
				EEPROM_readByte(LCD_User_Password_Block,(4*looping_counter)+i,&password_temp_arr[i]);
				_delay_ms(10);
			}
			
			
			if((Compare_Passwords(username_arr,username_temp_arr,LOGIN_SIZE) == '1') && (Compare_Passwords(password_arr,password_temp_arr,LOGIN_SIZE) == '1'))
			{
				LCD_Write_String("Access Granted");
				_delay_ms(500);
				LCD_Clear_Screen();
				Compare_Var = 1;
				break;
			}
		}

		if(Compare_Var == 0)
		{
			trials--;
			
			LCD_Write_String("Access Denied");
			LCD_Send_CMD(Row_2_pos_0);
			
			LCD_Write_String("Trials Left : ");
			LCD_Write_Char(trials+0x30);
			
			_delay_ms(500);
			LCD_Clear_Screen();
		}
		else
		{
			break;
		}

	}
			
	if(trials == 0)
	{
		Alarm_On ();
	}		
	
	LCD_User_Interfacing();
	_delay_ms(50);
}



void App_Initialization()
{
	LCD_Init();
	Keypad_Init();
	UART_Init(freq_16MHz_baud_9600);
	Servo_Initialization();
	LED_START();
	DIMMER_Init();
	BUZZER_START();
	ADC_Start(ADC_Channel);
	Sensor_ON();
	AC_Initialization();
	Interrupt_Start();
	EEPROM_Initialization();
	
}
	
	
// -------------------------->	App Function < ----------------------------------//

void App()
{
	unsigned char uart_var = 0;
	unsigned char Mode = 0;
	char admin_counter = 0;
	char user_counter = 0;
	unsigned char trials = 3;
	char username_arr[4];		// array filled by user interface (ADMIN/USER)
	char password_arr[4];		// array filled by user interface (ADMIN/USER)	
	char username_temp_arr[4];	// array taken from EEPROM to compare
	char password_temp_arr[4];	// array taken from EEPROM to compare
	unsigned char looping_counter = 0;
	unsigned char Compare_Var = 0;
	
	
	
	Mode = UART_Mode_Choice();
	
	if(Mode == '1')		// Admin Selection
	{
		EEPROM_readByte(Counters_Block,Admins_number_BIT,&admin_counter);
		_delay_ms(10);
		trials = 3;
		while(trials>=1 && trials<=3)
		{
				//----------------	Writing the username -----------------//
				UART_Send_String("Enter Username : ");
				looping_counter = 0;
				while(looping_counter < LOGIN_SIZE)
				{
					uart_var = 0;
					while(!(uart_var >= Ascii_0	&& uart_var <= Ascii_9))
					{
						uart_var = UART_Receive();
						UART_Transmit(uart_var);
					}
					username_arr[looping_counter] = uart_var;
					looping_counter++;
				}
				looping_counter = 0;
				UART_Transmit('\r');
				
				//-----------------	Writing the password -----------------//
				UART_Send_String("Enter Password : ");

				while(looping_counter < LOGIN_SIZE)
				{
					uart_var = 0;
					while(!(uart_var >= Ascii_0	&& uart_var <= Ascii_9))
					{
						uart_var = UART_Receive();
						UART_Transmit(uart_var);
					}
					
					password_arr[looping_counter] = uart_var;
					looping_counter++;
				}
				looping_counter = 0;
				UART_Transmit('\r');	
				
				
			EEPROM_readDatastream(Main_Admin_Block,0,username_temp_arr,LOGIN_SIZE);
			_delay_ms(10);
			EEPROM_readDatastream(Main_Admin_Block,8,password_temp_arr,LOGIN_SIZE);
			_delay_ms(10);
			
			if((Compare_Passwords(username_arr,username_temp_arr,LOGIN_SIZE) == '1') && (Compare_Passwords(password_arr,password_temp_arr,LOGIN_SIZE) == '1'))	// The loggedin admin is the main admin
			{
				UART_Transmit('\r');
				UART_Transmit('\r');
				UART_Send_String("WELCOME BOSS");	// this message is displayed only for the main admin
				UART_Transmit('\r');
				UART_Transmit('\r');
				Compare_Var = 1;
			}
			else
			{
				for (looping_counter = 0; looping_counter < admin_counter; looping_counter++)
				{
					for(char i = 0; i<LOGIN_SIZE; i++)
					{
						EEPROM_readByte(Admin_Username_Block,(4*looping_counter)+i,&username_temp_arr[i]);
						_delay_ms(10);
						EEPROM_readByte(Admin_Password_Block,(4*looping_counter)+i,&password_temp_arr[i]);
						_delay_ms(10);
					}
					if((Compare_Passwords(username_arr,username_temp_arr,LOGIN_SIZE) == '1') && (Compare_Passwords(password_arr,password_temp_arr,LOGIN_SIZE) == '1'))
					{
						UART_Send_String("Access Granted");
						UART_Transmit('\r');
						UART_Transmit('\r');
						UART_Send_String("WELCOME Admin");	
						UART_Transmit('\r');
						UART_Transmit('\r');
						Compare_Var = 1;
						break;
					}
				}	
			}	
			
			if(Compare_Var == 0)
			{
				trials--;
				UART_Send_String("Access Denied");
				UART_Transmit('\r');
				UART_Send_String("Trials Left before initializing Alarm : ");
				UART_Transmit(trials+0x30);
				UART_Transmit('\r');
				UART_Transmit('\r');
				UART_Transmit('\r');
			}
			else
			{
				break;
			}

		}

		if(trials == 0)
		{
			Alarm_On ();
		}

		UART_Admin_Interfacing();
	
	}
	else		// User
	{
		
			EEPROM_readByte(Counters_Block,Users_UART_number_BIT,&user_counter);
			_delay_ms(10);
			trials = 3;
			
			while(trials>=1 && trials<=3)
			{
					//----------------	Writing the username -----------------//
					UART_Send_String("Enter Username : ");
					
					looping_counter = 0;
					
					while(looping_counter < LOGIN_SIZE)
					{
						uart_var = 0;
						while(!(uart_var >= Ascii_0	&& uart_var <= Ascii_9))
						{
							uart_var = UART_Receive();
							UART_Transmit(uart_var);
						}
						
						username_arr[looping_counter] = uart_var;
						looping_counter++;
					}
					looping_counter = 0;
					UART_Transmit('\r');
					
					//-----------------	Writing the password -----------------//
					UART_Send_String("Enter Password : ");

					while(looping_counter < LOGIN_SIZE)
					{
						uart_var = 0;
						while(!(uart_var >= Ascii_0	&& uart_var <= Ascii_9))
						{
							uart_var = UART_Receive();
							UART_Transmit(uart_var);
						}
						
						password_arr[looping_counter] = uart_var;
						looping_counter++;
					}
					looping_counter = 0;
					UART_Transmit('\r');

				UART_Transmit('\r');
				UART_Transmit('\r');
				
				for (looping_counter = 0; looping_counter < user_counter; looping_counter++)
				{
					for(char i = 0; i<LOGIN_SIZE; i++)
					{
						EEPROM_readByte(UART_User_Username_Block,(4*looping_counter)+i,&username_temp_arr[i]);
						_delay_ms(10);
						EEPROM_readByte(UART_User_Password_Block,(4*looping_counter)+i,&password_temp_arr[i]);
						_delay_ms(10);
					}
					
					if((Compare_Passwords(username_arr,username_temp_arr,LOGIN_SIZE) == '1') && (Compare_Passwords(password_arr,password_temp_arr,LOGIN_SIZE) == '1'))
					{
						UART_Send_String("Access Granted");
						UART_Transmit('\r');
						UART_Transmit('\r');
						UART_Send_String("Welcome User");
						UART_Transmit('\r');
						UART_Transmit('\r');
						UART_Transmit('\r');
						Compare_Var = 1;
						break;
					}
				}
				
				looping_counter = 0;
				
				if(Compare_Var == 0)
				{
					trials--;
					UART_Send_String("Access Denied");
					UART_Transmit('\r');
					UART_Send_String("Trials Left before initializing Alarm : ");
					UART_Transmit(trials+0x30);
					UART_Transmit('\r');
					UART_Transmit('\r');
					UART_Transmit('\r');
				}
				else
				{
					break;
				}

			}

			if(trials == 0)
			{
				Alarm_On ();
			}
			
			UART_User_Interfacing();		
	}
}