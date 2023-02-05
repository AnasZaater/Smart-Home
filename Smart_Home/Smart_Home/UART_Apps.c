#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "Ascii_num.h"
#include "Bit_Op.h"
#include "PINS.h"
#include "LED_Dimmer_Buzzer_Alarm.h"
#include "UART.h"
#include "UART_Apps.h"
#include "LCD.h"
#include "LCD_Apps.h"
#include "Keypad.h"
#include "EEPROM.h"
#include "EEPROM_Apps.h"
#include "App.h"
#include "Servo.h"

void UART_Welcome_Message()
{
	UART_Send_String ("Welcome to Smart Home System");
	UART_Transmit('\r');
	UART_Transmit('\r');
	_delay_ms(300);
}

unsigned char UART_Mode_Choice()
{
	unsigned char uart_var = 0;
	
	UART_Send_String ("Please choose your Mode (Admin/User) ");
	UART_Transmit('\r');
	UART_Send_String ("1. Admin Mode ");
	UART_Transmit('\r');
	UART_Send_String ("2. User Mode ");
	UART_Transmit('\r');
	UART_Transmit('\r');
	_delay_ms(300);
	
	UART_Send_String ("Your Choice : ");
	while(!(uart_var >= Ascii_0	&& uart_var <= Ascii_9))
	{
		uart_var = UART_Receive();
		UART_Transmit(uart_var);
	}
	
	UART_Transmit('\r');
	UART_Transmit('\r');
	
	while (!((uart_var >= Ascii_1) && (uart_var <= Ascii_2)))
	{
		UART_Send_String ("Please Choose only 1 or 2");
		UART_Transmit('\r');
		UART_Transmit('\r');
		uart_var = 0;
		UART_Send_String("Your choice : ");
		while(!(uart_var >= Ascii_0	&& uart_var <= Ascii_9))
		{
			uart_var = UART_Receive();
			UART_Transmit(uart_var);	
		}
		
		UART_Transmit('\r');
		UART_Transmit('\r');
	}
	
	return uart_var;
}

void UART_Rooms_Leds_Control()
{
	unsigned char room_no_temp = 0;
	unsigned char room_on_off_temp = 0;
	unsigned char uart_var = 0;
	
	UART_Send_String ("1. Room 1 ");
	UART_Transmit('\r');
	UART_Send_String ("2. Room 2 ");
	UART_Transmit('\r');
	UART_Send_String ("3. Room 3 ");
	UART_Transmit('\r');
	UART_Send_String ("4. Room 4 ");
	UART_Transmit('\r');
	UART_Send_String ("5. Room 5 ");
	UART_Transmit('\r');
	UART_Send_String ("6. All rooms ");
	UART_Transmit('\r');
	UART_Transmit('\r');
	UART_Send_String("Your choice : ");
	
	while(!(uart_var >= Ascii_0	&& uart_var <= Ascii_9))
	{
		uart_var = UART_Receive();
		UART_Transmit(uart_var);
		UART_Transmit('\r');
		UART_Transmit('\r');
	}
	room_no_temp = uart_var;
	
	while (!((room_no_temp >= Ascii_1) && (room_no_temp <= Ascii_6)))
	{
		UART_Send_String ("Please Choose only from 1 to 6");
		UART_Transmit('\r');
		UART_Transmit('\r');
		UART_Send_String("Your choice : ");
		
		uart_var = 0;
		while(!(uart_var >= Ascii_0	&& uart_var <= Ascii_9))
		{
			uart_var = UART_Receive();
			UART_Transmit(uart_var);
			UART_Transmit('\r');
			UART_Transmit('\r');
		}
		room_no_temp = uart_var;
	}
	uart_var = 0;
	
	UART_Send_String ("Turn On : 1");
	UART_Transmit('\r');
	UART_Send_String ("Turn Off : 0");
	UART_Transmit('\r');
	UART_Transmit('\r');
	UART_Send_String("Your Choice : ");
	while(!(uart_var >= Ascii_0	&& uart_var <= Ascii_9))
	{
		uart_var = UART_Receive();
		UART_Transmit(uart_var);
		UART_Transmit('\r');
		UART_Transmit('\r');
	}
	room_on_off_temp = uart_var;
	
	while ((room_on_off_temp != Ascii_1) && (room_on_off_temp != Ascii_0))
	{
		UART_Send_String ("Please Choose 1 or 0");
		UART_Transmit('\r');
		UART_Transmit('\r');
		
		uart_var = 0;
		UART_Send_String("Your choice : ");
		while(!(uart_var >= Ascii_0	&& uart_var <= Ascii_9))
		{
			uart_var = UART_Receive();
			UART_Transmit(uart_var);
			UART_Transmit('\r');
			UART_Transmit('\r');
		}
		room_on_off_temp = uart_var;
	}
	uart_var = 0;
	
	if(room_no_temp == Ascii_6)
	{
		if(room_on_off_temp == Ascii_1)
		{
			LED_STAT(ON,Room1);
			LED_STAT(ON,Room2);
			LED_STAT(ON,Room3);
			LED_STAT(ON,Room4);
			LED_STAT(ON,Room5);
			
			UART_Send_String("All Leds are Turned On");
			UART_Transmit('\r');
			UART_Transmit('\r');
			
			
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
			
			UART_Send_String("All Leds are Turned Off");
			UART_Transmit('\r');
			UART_Transmit('\r');
			
			LCD_Write_String("All Leds are ");
			LCD_Send_CMD(Row_2_pos_0);
			LCD_Write_String ("Turned Off");
			_delay_ms(1000);
			LCD_Clear_Screen();
		}
	}
	else
	{
		LED_STAT(room_on_off_temp,room_no_temp);
		LCD_Display_LED (room_no_temp, room_on_off_temp);	
	}
	
	UART_Transmit('\r');
	UART_Transmit('\r');
	UART_Transmit('\r');
}



void UART_Admin_Interfacing()
{
	unsigned char uart_var = 0;
	unsigned char option = 0;
	unsigned char brightness_level = 0;
	unsigned char looping_counter = 0;
	char username_arr[4];		// array filled by user interface (ADMIN/USER)
	char password_arr[4];		// array filled by user interface (ADMIN/USER)
	char username_temp_arr[4];	// array taken from eeprom to compare.
	char password_temp_arr[4];	// array taken from eeprom to compare.
	char username_arr_2[4];		// array taken from eeprom in deleting user part.
	char password_arr_2[4];		// array taken from eeprom in deleting user part.
	unsigned char Compare_Var = 0;
	unsigned char user_type = 0;
	char admin_counter = 0;
	char user_counter = 0;
	char max_number_var = 0;
	
	while (option != Ascii_8)	// Corresponding to Logout
	{
		UART_Send_String ("1. Controlling Lighting (Room 1 to Room 5)");
		UART_Transmit('\r');
		UART_Send_String ("2. Dimming lamp");
		UART_Transmit('\r');
		UART_Send_String ("3. Open the Door");
		UART_Transmit('\r');
		UART_Send_String ("4. Close the Door");
		UART_Transmit('\r');
		UART_Send_String ("5. Add admin to the system");
		UART_Transmit('\r');
		UART_Send_String ("6. Add user to the system");
		UART_Transmit('\r');
		UART_Send_String ("7. Remove a user from the system");
		UART_Transmit('\r');
		UART_Send_String ("8. Log out");	// return to Mode choice function (Admin / User)
		UART_Transmit('\r');
		UART_Transmit('\r');	
		
		UART_Send_String ("Your Choice : ");
		
		uart_var = 0; 
		while(!(uart_var >= Ascii_0	&& uart_var <= Ascii_9))
		{
			uart_var = UART_Receive();
		}	
		UART_Transmit(uart_var);
		UART_Transmit('\r');
		UART_Transmit('\r');
		while (!((uart_var >= Ascii_1) && (uart_var <= Ascii_8)))
		{
			UART_Send_String ("Please Choose only from 1 to 8");
			UART_Transmit('\r');
			UART_Transmit('\r');
			uart_var = 0;
			UART_Send_String("Your choice : ");
			while(!(uart_var >= Ascii_0	&& uart_var <= Ascii_9))
			{
				uart_var = UART_Receive();
				UART_Transmit(uart_var);
			}
			UART_Transmit('\r');
			UART_Transmit('\r');
		}
		option = uart_var;
	
	
		if(option == '1')
		{	
			UART_Rooms_Leds_Control();
		}
		else if(option == '2')
		{
			UART_Transmit('\r');
			UART_Transmit('\r');
			UART_Send_String ("Please Choose one of the following brightness percentages :  ");
			UART_Transmit('\r');
			UART_Transmit('\r');
		
			UART_Send_String ("0. 0% (Turn Off Led)");
			UART_Transmit('\r');
			UART_Send_String ("1. 25% ");
			UART_Transmit('\r');
			UART_Send_String ("2. 50% ");
			UART_Transmit('\r');
			UART_Send_String ("3. 75% ");
			UART_Transmit('\r');
			UART_Send_String ("4. 100%  (Maximum Power)");
			UART_Transmit('\r');
		
			UART_Send_String("Your choice : ");
			uart_var = 0;
			while(!(uart_var >= Ascii_0	&& uart_var <= Ascii_9))
			{
				uart_var = UART_Receive();
				UART_Transmit(uart_var);
				UART_Transmit('\r');
				UART_Transmit('\r');
			}
		
			while (!((uart_var >= Ascii_0) && (uart_var <= Ascii_4)))
			{
				UART_Send_String ("Please Choose only from 0 to 4");
				UART_Transmit('\r');
				UART_Transmit('\r');
				uart_var = 0;
				UART_Send_String("Your choice : ");
				while(!(uart_var >= Ascii_0	&& uart_var <= Ascii_9))
				{
					uart_var = UART_Receive();
					UART_Transmit(uart_var);
					UART_Transmit('\r');
					UART_Transmit('\r');
				}
			}
		
			brightness_level = uart_var;
			uart_var = 0;
			DIMMER_CONTROL(brightness_level); 
					
		}	
		else if(option == '3')
		{
			openDoor();
			UART_Send_String("\r");
			UART_Transmit('\r');
			UART_Send_String("The door is opened");
			UART_Send_String("\r");
			UART_Transmit('\r');
		
			LCD_Write_String("  The door is");
			LCD_Send_CMD(Row_2_pos_0);
			LCD_Write_String("     Opened");
			_delay_ms(500);
			LCD_Clear_Screen();
		}
		else if(option == '4')
		{
			closeDoor();
			UART_Send_String("\r");
			UART_Transmit('\r');
			UART_Send_String("The door is closed");
			UART_Send_String("\r");
			UART_Transmit('\r');
		
			LCD_Write_String("  The door is");
			LCD_Send_CMD(Row_2_pos_0);
			LCD_Write_String("    Closed");
			_delay_ms(500);
			LCD_Clear_Screen();
		}
	
		else if(option == '5')	// Add Admin to the system
		{
				EEPROM_readByte(Counters_Block,Admins_number_BIT,&max_number_var);
				_delay_ms(10);
				
				if(max_number_var < ADMINS_MAX_NO)
				{
					/*-----------------	Writing the username -----------------*/
					UART_Transmit('\r');
					UART_Transmit('\r');
					UART_Send_String("Enter Username : ");

					while(looping_counter < LOGIN_SIZE)
					{
						uart_var = 0;
						while(!(uart_var >= Ascii_0	&& uart_var <= Ascii_9))
						{
							uart_var = UART_Receive();
						}
						
						UART_Transmit(uart_var);
						username_arr[looping_counter] = uart_var;
						looping_counter++;
					}
					looping_counter = 0;
					UART_Transmit('\r');
					
					/*-----------------	Writing the password -----------------*/
					UART_Send_String("Enter Password : ");

					while(looping_counter < LOGIN_SIZE)
					{
						uart_var = 0;
						while(!(uart_var >= Ascii_0	&& uart_var <= Ascii_9))
						{
							uart_var = UART_Receive();
						}
						
						UART_Transmit(uart_var);
						password_arr[looping_counter] = uart_var;
						looping_counter++;
					}
					looping_counter = 0;
					UART_Transmit('\r');
					
					EEPROM_readByte(Counters_Block,Admins_number_BIT,&admin_counter);
					_delay_ms(10);
				
					for(char i = 0; i < LOGIN_SIZE; i++)
					{
						EEPROM_writeByte(Admin_Username_Block, (4*admin_counter)+i, username_arr[i]);
						_delay_ms(10);
						EEPROM_writeByte(Admin_Password_Block, (4*admin_counter)+i, password_arr[i]);
						_delay_ms(10);
					}
					admin_counter++;
					EEPROM_writeByte(Counters_Block,Admins_number_BIT,admin_counter);
					_delay_ms(10);		
				
					UART_Send_String("The admin is added successfully");
					UART_Transmit('\r');
					UART_Transmit('\r');
					
					
					LCD_Set_Cursor(0,1);
					LCD_Write_String("Admin is added");
					LCD_Set_Cursor(1,2);
					LCD_Write_String("successfully");
					
					_delay_ms(500);
					
				}
				else
				{
					UART_Send_String("Sorry, the maximum number for users is 64 users");
					UART_Transmit('\r');
					UART_Send_String("The system can't add more");
					UART_Transmit('\r');
					UART_Transmit('\r');
					_delay_ms(500);	
				}
		}
	
		else if(option == '6')	// Add a user to the system
		{
			UART_Transmit('\r');
			UART_Transmit('\r');
			UART_Send_String("1. Remote User (UART)");
			UART_Transmit('\r');
			UART_Send_String("2. LCD & Keypad User ");
			UART_Transmit('\r');
			UART_Transmit('\r');
			
			UART_Send_String("Your choice : ");
			
			uart_var = 0;
			while(!(uart_var >= Ascii_0	&& uart_var <= Ascii_9))
			{
				uart_var = UART_Receive();
				UART_Transmit(uart_var);
			}
			
			while (!((uart_var >= Ascii_1) && (uart_var <= Ascii_2)))
			{
				UART_Send_String ("Please Choose only 1 or 2");
				UART_Transmit('\r');
				UART_Transmit('\r');
				uart_var = 0;
				UART_Send_String("Your choice : ");
				while(!(uart_var >= Ascii_0	&& uart_var <= Ascii_9))
				{
					uart_var = UART_Receive();
				}
				UART_Transmit(uart_var);
			}
			user_type = uart_var;
			
			
			if(user_type == '1')	// uart_user
			{
				EEPROM_readByte(Counters_Block,Users_UART_number_BIT,&max_number_var);
				_delay_ms(10);
				
				if(max_number_var < USERS_MAX_NO)
				{
					/*-----------------	Writing the username -----------------*/
					UART_Transmit('\r');
					UART_Transmit('\r');
					UART_Send_String("Enter Username : ");

					while(looping_counter < LOGIN_SIZE)
					{
						uart_var = 0;
						while(!(uart_var >= Ascii_0	&& uart_var <= Ascii_9))
						{
							uart_var = UART_Receive();
						}
						
						UART_Transmit(uart_var);
						username_arr[looping_counter] = uart_var;
						looping_counter++;
					}
					looping_counter = 0;
					UART_Transmit('\r');
					
					/*-----------------	Writing the password -----------------*/
					UART_Send_String("Enter Password : ");

					while(looping_counter < LOGIN_SIZE)
					{
						uart_var = 0;
						while(!(uart_var >= Ascii_0	&& uart_var <= Ascii_9))
						{
							uart_var = UART_Receive();
						}
						
						UART_Transmit(uart_var);
						password_arr[looping_counter] = uart_var;
						looping_counter++;
					}
					looping_counter = 0;
					UART_Transmit('\r');
					
					EEPROM_readByte(Counters_Block,Users_UART_number_BIT,&user_counter);
					_delay_ms(10);
					
					for(char i = 0; i < LOGIN_SIZE; i++)
					{
						EEPROM_writeByte(UART_User_Username_Block, (4*user_counter)+i, username_arr[i]);
						_delay_ms(10);
						EEPROM_writeByte(UART_User_Password_Block, (4*user_counter)+i, password_arr[i]);
						_delay_ms(10);
					}
					user_counter++;
					EEPROM_writeByte(Counters_Block,Users_UART_number_BIT,user_counter);
					_delay_ms(10);		
				
					UART_Send_String("The user is added successfully");
					UART_Transmit('\r');
					UART_Transmit('\r');
					
					LCD_Set_Cursor(0,1);
					LCD_Write_String("User is added");
					LCD_Set_Cursor(1,2);
					LCD_Write_String("successfully");
					
					_delay_ms(100);	
				}
				else
				{
					UART_Send_String("Sorry, the maximum number for users is 64 users");
					UART_Transmit('\r');
					UART_Send_String("The system can't add more");
					UART_Transmit('\r');
					UART_Transmit('\r');
					_delay_ms(500);	
				}
			}
			else  // lcd_user
			{
				EEPROM_readByte(Counters_Block,Users_LCD_number_BIT,&max_number_var);
				_delay_ms(10);
				
				if(max_number_var < USERS_MAX_NO)
				{
					/*-----------------	Writing the username -----------------*/
					UART_Transmit('\r');
					UART_Transmit('\r');
					UART_Send_String("Enter Username : ");

					while(looping_counter < LOGIN_SIZE)
					{
						uart_var = 0;
						while(!(uart_var >= Ascii_0	&& uart_var <= Ascii_9))
						{
							uart_var = UART_Receive();
						}
						
						UART_Transmit(uart_var);
						username_arr[looping_counter] = uart_var;
						looping_counter++;
					}
					looping_counter = 0;
					UART_Transmit('\r');
					
					/*-----------------	Writing the password -----------------*/
					UART_Send_String("Enter Password : ");

					while(looping_counter < LOGIN_SIZE)
					{
						uart_var = 0;
						while(!(uart_var >= Ascii_0	&& uart_var <= Ascii_9))
						{
							uart_var = UART_Receive();
						}
						
						UART_Transmit(uart_var);
						password_arr[looping_counter] = uart_var;
						looping_counter++;
					}
					looping_counter = 0;
					UART_Transmit('\r');
					
					EEPROM_readByte(Counters_Block,Users_LCD_number_BIT,&user_counter);
					_delay_ms(10);
					
					for(char i = 0; i < LOGIN_SIZE; i++)
					{
						EEPROM_writeByte(LCD_User_Username_Block, (4*user_counter)+i, username_arr[i]);
						_delay_ms(10);
						EEPROM_writeByte(LCD_User_Password_Block, (4*user_counter)+i, password_arr[i]);
						_delay_ms(10);
					}
					user_counter++;
					EEPROM_writeByte(Counters_Block,Users_LCD_number_BIT,user_counter);
					_delay_ms(10);		
				
					UART_Send_String("The user is added successfully");
					UART_Transmit('\r');
					UART_Transmit('\r');
					_delay_ms(500);
					
				}
				else
				{
					UART_Send_String("Sorry, the maximum number for users is 64 users");
					UART_Transmit('\r');
					UART_Send_String("The system can't add more");
					UART_Transmit('\r');
					UART_Transmit('\r');
					_delay_ms(500);	
				}
			}
		}
		
		else if(option == '7')	// Delete User from the system
		{
			
			UART_Transmit('\r');
			UART_Send_String("1. Delete a remote (UART) User  ");
			UART_Transmit('\r');
			UART_Send_String("2. Delete an LCD & Keypad User  ");
			UART_Transmit('\r');
			UART_Transmit('\r');
			
			UART_Send_String("Your choice : ");
	
			uart_var = 0;
			while(!(uart_var >= Ascii_0	&& uart_var <= Ascii_9))
			{
				uart_var = UART_Receive();
			}
			UART_Transmit(uart_var);
			
			while (!((uart_var >= Ascii_1) && (uart_var <= Ascii_2)))
			{
				UART_Send_String ("Please Choose only 1 or 2");
				UART_Transmit('\r');
				UART_Transmit('\r');
				uart_var = 0;
				UART_Send_String("Your choice : ");
				while(!(uart_var >= Ascii_0	&& uart_var <= Ascii_9))
				{
					uart_var = UART_Receive();
				}
				UART_Transmit(uart_var);
			}
			
			user_type = uart_var;
	
			/*-----------------	Writing the username -----------------*/
			UART_Transmit('\r');
			UART_Transmit('\r');
			UART_Send_String("Enter User's Username to be deleted : ");
			
			looping_counter = 0;
			while(looping_counter < LOGIN_SIZE)
			{
				uart_var = 0;
				while(!(uart_var >= Ascii_0	&& uart_var <= Ascii_9))
				{
					uart_var = UART_Receive();
				}
				
				UART_Transmit(uart_var);
				username_arr[looping_counter] = uart_var;
				looping_counter++;
			}
			looping_counter = 0;
			UART_Transmit('\r');
			
			/*-----------------	Writing the password -----------------*/
			UART_Send_String("Enter User's Password to be deleted : ");

			while(looping_counter < LOGIN_SIZE)
			{
				uart_var = 0;
				while(!(uart_var >= Ascii_0	&& uart_var <= Ascii_9))
				{
					uart_var = UART_Receive();
				}
				
				UART_Transmit(uart_var);
				password_arr[looping_counter] = uart_var;
				looping_counter++;
			}
			looping_counter = 0;
			UART_Transmit('\r');
			
			
			if(user_type == '1')	// Remoted User
			{
				EEPROM_readByte(Counters_Block,Users_UART_number_BIT,&user_counter);
				_delay_ms(10);
				
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
						for(char counter = looping_counter; counter < user_counter-1; counter++)
						{
							for(char i = 0; i<LOGIN_SIZE; i++)
							{
								EEPROM_readByte(UART_User_Username_Block,4*(counter+1)+i,&username_arr_2[i]);
								_delay_ms(10);
								EEPROM_readByte(UART_User_Password_Block,4*(counter+1)+i,&password_arr_2[i]);
								_delay_ms(10);
								
								EEPROM_writeByte(UART_User_Username_Block , 4*(counter)+i , username_arr_2[i]);
								_delay_ms(10);
								EEPROM_writeByte(UART_User_Password_Block , 4*(counter)+i , password_arr_2[i]);
								_delay_ms(10);
							
							}
						}						
						
						UART_Send_String("The user is deleted successfully");
						UART_Transmit('\r');
						
						for(char i = 0; i < LOGIN_SIZE; i++)
						{
							EEPROM_writeByte(UART_User_Username_Block, 4*(user_counter-1)+i, 0xFF);
							_delay_ms(10);
							EEPROM_writeByte(UART_User_Password_Block, 4*(user_counter-1)+i, 0xFF);
							_delay_ms(10);
						}
						
						user_counter--;
						EEPROM_writeByte(Counters_Block,Users_UART_number_BIT,user_counter);
						_delay_ms(10);
						
						Compare_Var = 1;
						break;
					}
				}
				if(Compare_Var == 0)
				{
					UART_Send_String("The entered Username & Password are not found");
					UART_Transmit('\r');
					UART_Send_String("Please Try again");
					UART_Transmit('\r');
					UART_Transmit('\r');
				}
				
			}
			else					// LCD & Keypad User
			{
				EEPROM_readByte(Counters_Block,Users_LCD_number_BIT,&user_counter);	// 3
				_delay_ms(10);
				
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
						
						for(unsigned char counter = looping_counter; counter < (user_counter-1); counter++)
						{			
							for(char i = 0; i<LOGIN_SIZE; i++)
							{
								EEPROM_readByte(LCD_User_Username_Block,4*(counter+1)+i,&username_arr_2[i]);
								_delay_ms(10);
								EEPROM_readByte(LCD_User_Password_Block,4*(counter+1)+i,&password_arr_2[i]);
								_delay_ms(10);
								
								EEPROM_writeByte(LCD_User_Username_Block , 4*(counter)+i , username_arr_2[i]);
								_delay_ms(10);
								EEPROM_writeByte(LCD_User_Password_Block , 4*(counter)+i , password_arr_2[i]);
								_delay_ms(10);
							}
						}
						UART_Send_String("The user is deleted successfully");
						UART_Transmit('\r');
						
						for(char i = 0; i < LOGIN_SIZE; i++)
						{
							EEPROM_writeByte(LCD_User_Username_Block, 4*(user_counter-1)+i, 0xFF);
							_delay_ms(10);
							EEPROM_writeByte(LCD_User_Password_Block, 4*(user_counter-1)+i, 0xFF);
							_delay_ms(10);
						}
						
						user_counter--;
						EEPROM_writeByte(Counters_Block,Users_LCD_number_BIT,user_counter);
						_delay_ms(10);
						
						Compare_Var = 1;
						break;
					}
				}
				if(Compare_Var == 0)
				{
					UART_Transmit('\r');
					UART_Send_String("The entered Username & Password are not found");
					UART_Transmit('\r');
					UART_Send_String("Please Try again");
					UART_Transmit('\r');
					UART_Transmit('\r');
				}
			}
			
		}
		
	}
	UART_Transmit('\r');
	UART_Transmit('\r');
	UART_Transmit('\r');
}


void UART_User_Interfacing()
{
	unsigned char uart_var = 0;
	unsigned char option = 0;
	unsigned char brightness_level = 0;
	while(option != Ascii_4)
	{
		UART_Send_String ("1. Controlling Lighting (Room 1 to Room 5)");
		UART_Transmit('\r');
		UART_Send_String ("2. Dimming lamp");
		UART_Transmit('\r');
		UART_Send_String ("3. Close the Door");
		UART_Transmit('\r');
		UART_Send_String ("4. Log out");
		UART_Transmit('\r');
		UART_Transmit('\r');
		
		
		UART_Send_String ("Your Choice : ");
		
		uart_var = 0;
		while(!(uart_var >= Ascii_0	&& uart_var <= Ascii_9))
		{
			uart_var = UART_Receive();
			UART_Transmit(uart_var);
			UART_Transmit('\r');
			UART_Transmit('\r');
		}
	
		while (!((uart_var >= Ascii_1) && (uart_var <= Ascii_4)))
		{
			UART_Send_String ("Please Choose only from 1 to 4");
			UART_Transmit('\r');
			UART_Transmit('\r');
			uart_var = 0;
			UART_Send_String("Your choice : ");
			while(!(uart_var >= Ascii_0	&& uart_var <= Ascii_9))
			{
				uart_var = UART_Receive();
				UART_Transmit(uart_var);
				UART_Transmit('\r');
				UART_Transmit('\r');
			}
		}
		option = uart_var;
	
	
		if(option == '1')
		{
			UART_Rooms_Leds_Control();
		}
		else if(option == '2')
		{
			UART_Send_String ("Please Choose one of the following brightness percentages :  ");
			UART_Transmit('\r');
			UART_Transmit('\r');
		
			UART_Send_String ("0. 0% (Turn Off Led)");
			UART_Transmit('\r');
			UART_Send_String ("1. 25% ");
			UART_Transmit('\r');
			UART_Send_String ("2. 50% ");
			UART_Transmit('\r');
			UART_Send_String ("3. 75% ");
			UART_Transmit('\r');
			UART_Send_String ("4. 100%  (Maximum Power)");
			UART_Transmit('\r');
		
			UART_Send_String("Your choice : ");
			uart_var = 0;
			while(!(uart_var >= Ascii_0	&& uart_var <= Ascii_9))
			{
				uart_var = UART_Receive();
				UART_Transmit(uart_var);
				UART_Transmit('\r');
				UART_Transmit('\r');
			}
		
			while (!((uart_var >= Ascii_0) && (uart_var <= Ascii_4)))
			{
				UART_Send_String ("Please Choose only from 0 to 4");
				UART_Transmit('\r');
				UART_Transmit('\r');
				uart_var = 0;
				UART_Send_String("Your choice : ");
				while(!(uart_var >= Ascii_0	&& uart_var <= Ascii_9))
				{
					uart_var = UART_Receive();
					UART_Transmit(uart_var);
					UART_Transmit('\r');
					UART_Transmit('\r');
				}
			}
		
			brightness_level = uart_var;
			uart_var = 0;
			DIMMER_CONTROL(brightness_level);	
		}
	
	
		else if(option == '3')
		{
			closeDoor();
			UART_Send_String("The door is closed");
			UART_Send_String("\r");
		
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















