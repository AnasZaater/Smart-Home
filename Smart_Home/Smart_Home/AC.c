#include <avr/io.h>
#include "ADC.h"
#include "AC.h"
#include "Bit_Op.h"
#include "PINS.h"
#include "LED_Dimmer_Buzzer_Alarm.h"

void AC_Initialization()
{
	set_bit(AC_DIR,AC_PIN1);  // Motor Pin 1
	set_bit(AC_DIR,AC_PIN2);  //  Motor Pin 2
	clear_bit(AC_PORT,AC_PIN2); //rotates clockwise always
}

void AC_Alarm()
{
	set_bit(BUZZER_PORT,BUZZER_PIN); //Starts the Buzzer
	toggle_bit(AC_LED_PORT,AC_LED_PIN);// Toggles the LED indicating an alarm
}


void AC_ON()
{
	int Temperature = 0;
	Temperature = ADC_READ(); //Variable to save temperature value
	
	if (Temperature < T_min) // A/C OFF
	{
		clear_bit(AC_PORT,AC_PIN1);
		clear_bit(BUZZER_PORT,BUZZER_PIN);
		clear_bit(AC_LED_PORT,AC_LED_PIN);
		
	}
	else if (Temperature > T_max && Temperature < T_crit) // A/C ON
	{
		set_bit(AC_PORT,AC_PIN1);
		clear_bit(BUZZER_PORT,BUZZER_PIN);
		clear_bit(AC_LED_PORT,AC_LED_PIN);
		
	}
	else if (Temperature > T_crit) // A/C OFF
	{
		clear_bit(AC_PORT,AC_PIN1);
		AC_Alarm();		// AC led blinks and buzzer ON
	}
}