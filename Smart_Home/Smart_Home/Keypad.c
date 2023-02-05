#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "Bit_Op.h"
#include "PINS.h"
#include "Keypad.h"

char arr[4][4] = {{'7','8','9','/'},{'4','5','6','*'},{'1','2','3','-'},{'C','0','=','+'}};

void Keypad_Init(void)
{	
	clear_bit(Keypad_Input_Port_Dir,input_pin_1);
	clear_bit(Keypad_Input_Port_Dir,input_pin_2);
	clear_bit(Keypad_Input_Port_Dir,input_pin_3);
	clear_bit(Keypad_Input_Port_Dir,input_pin_4);
	
	set_bit(Keypad_Input_Write_Port,input_pin_1);
	set_bit(Keypad_Input_Write_Port,input_pin_2);
	set_bit(Keypad_Input_Write_Port,input_pin_3);
	set_bit(Keypad_Input_Write_Port,input_pin_4);
	
	
	set_bit(Keypad_Output_Port_Dir,output_pin_1);
	set_bit(Keypad_Output_Port_Dir,output_pin_2);
	set_bit(Keypad_Output_Port_Dir,output_pin_3);
	set_bit(Keypad_Output_Port_Dir,output_pin_4);
	
	set_bit(Keypad_Output_Write_Port,output_pin_1);
	set_bit(Keypad_Output_Write_Port,output_pin_2);
	set_bit(Keypad_Output_Write_Port,output_pin_3);
	set_bit(Keypad_Output_Write_Port,output_pin_4);
	
}

unsigned char Keypad_Get_Value()
{
	unsigned char Value = 0;
	
	for(unsigned char i = output_pin_1; i <= output_pin_4; i++)
	{
		clear_bit(Keypad_Output_Write_Port, i);
		for(unsigned char j = input_pin_1; j <= input_pin_4; j++)
		{
			if(!(read_bit(Keypad_Input_Read_Port, j)))
			{
				Value = arr[j-input_pin_1][i-output_pin_1];
				while(!(read_bit(Keypad_Input_Read_Port, j)));
			}
		}
		set_bit(Keypad_Output_Write_Port, i);
	}
	return Value;
}

