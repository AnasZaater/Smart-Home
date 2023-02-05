#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "Ascii_num.h"
#include "Bit_Op.h"
#include "PINS.h"
#include "LCD.h"
#include "Keypad.h"
#include "LED_Dimmer_Buzzer_Alarm.h"
#include "UART.h"
#include "UART_Apps.h"
#include "Servo.h"
#include "TimerFunc.h"
#include "App.h"
#include "LCD_Apps.h"
#include "EEPROM.h"
#include "EEPROM_Apps.h"



int main(void)
{
	App_Initialization();	// Initialization of all peripherals in the application (system)	
	EEPROM_Save_Main_Admin();	// Save Admin 
	EEPROM_Write_0_Counters();	// Writing 0 on the bits of counters if the system is operated for the first time
	UART_Welcome_Message();
	
	while (1)
	{
		App();	
	}

}

