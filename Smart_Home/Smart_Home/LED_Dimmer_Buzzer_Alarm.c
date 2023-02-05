#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "Bit_Op.h"
#include "PINS.h"
#include "LED_Dimmer_Buzzer_Alarm.h"
#include "TimerFunc.h"

/*--------> Buzzer <---------*/
void BUZZER_START()
{
	set_bit(BUZZER_DIR,BUZZER_PIN);
}

/*--------> LEDs <---------*/
void LED_START()
{
	set_bit(LED_1_DIR,LED_1_PIN);
	set_bit(LED_2_DIR,LED_2_PIN);
	set_bit(LED_3_DIR,LED_3_PIN);
	set_bit(LED_4_DIR,LED_4_PIN);
	set_bit(LED_5_DIR,LED_5_PIN);
	
	set_bit(AC_LED_DIR,AC_LED_PIN);
}

void LED_STAT(unsigned char status,unsigned char R_Num)
{
	if (status == ON)
	{
		if (R_Num == Room1)
		{
			set_bit(LED_1_PORT,LED_1_PIN);
		}
		else if (R_Num == Room2)
		{
			set_bit(LED_2_PORT,LED_2_PIN);
		}
		else if (R_Num == Room3)
		{
			set_bit(LED_3_PORT,LED_3_PIN);
		}
		else if (R_Num == Room4)
		{
			set_bit(LED_4_PORT,LED_4_PIN);
		}
		else if (R_Num == Room5)
		{
			set_bit(LED_5_PORT,LED_5_PIN);
		}
	}
	else if (status == OFF)
	{
		if (R_Num == Room1)
		{
			clear_bit(LED_1_PORT,LED_1_PIN);
		}
		else if (R_Num == Room2)
		{
			clear_bit(LED_2_PORT,LED_2_PIN);
		}
		else if (R_Num == Room3)
		{
			clear_bit(LED_3_PORT,LED_3_PIN);
		}
		else if (R_Num == Room4)
		{
			clear_bit(LED_4_PORT,LED_4_PIN);
		}
		else if (R_Num == Room5)
		{
			clear_bit(LED_5_PORT,LED_5_PIN);
		}
	}
	
}

/*--------> Alarm <---------*/
void Alarm_On ()
{
	while(1)
	{
		set_bit(BUZZER_PORT,BUZZER_PIN);
		toggle_bit(LED_1_PORT,LED_1_PIN);
		toggle_bit(LED_2_PORT,LED_2_PIN);
		toggle_bit(LED_3_PORT,LED_3_PIN);
		toggle_bit(LED_4_PORT,LED_4_PIN);
		toggle_bit(LED_5_PORT,LED_5_PIN);
		_delay_ms(LED_BLINK_T);	
	}
		
}


/*--------> Dimmer <---------*/

void DIMMER_Init()
{
	set_bit(DIMMER_DIR,DIMMER_PIN);	
	Timer(0,PWM_Phase_Correct,COM_Clear,fclk8);
}

void DIMMER_CONTROL(unsigned char LEVEL)
{
	
	if (LEVEL == LEVEL0)
	{
		OCR0 = LEVEL0_PERCENT;
	}
	else if (LEVEL == LEVEL1)
	{
		OCR0 = LEVEL1_PERCENT*MAX/maxPercent;
	}
	else if (LEVEL == LEVEL2)
	{
		OCR0 = LEVEL2_PERCENT*MAX/maxPercent;
	}
	else if (LEVEL == LEVEL3)
	{
		OCR0 = LEVEL3_PERCENT*MAX/maxPercent;
	}
	else if (LEVEL == LEVEL4)
	{
		OCR0 = LEVEL4_PERCENT*MAX/maxPercent;
	}
}