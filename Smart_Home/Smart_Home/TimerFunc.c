#include <avr/io.h>
#include "TimerFunc.h"
#include "Bit_Op.h"

void Timer(char timerNum,char Mode,char COM,char Prescaler)
{
	if (timerNum == 0)
	{
		
		if (Prescaler == fclkOFF)
		{
			clear_bit(TCCR0,CS00);
			clear_bit(TCCR0,CS01);
			clear_bit(TCCR0,CS02);
		}
		else if (Prescaler == fclk0)
		{
			set_bit(TCCR0,CS00);
			clear_bit(TCCR0,CS01);
			clear_bit(TCCR0,CS02);

		}
		else if (Prescaler == fclk8)
		{
			clear_bit(TCCR0,CS00);
			set_bit(TCCR0,CS01);
			clear_bit(TCCR0,CS02);
		}
		else if (Prescaler == fclk64)
		{
			set_bit(TCCR0,CS00);
			set_bit(TCCR0,CS01);
			clear_bit(TCCR0,CS02);
		}
		else if (Prescaler == fclk256)
		{
			clear_bit(TCCR0,CS00);
			clear_bit(TCCR0,CS01);
			set_bit(TCCR0,CS02);
		}
		else if (Prescaler == fclk1024)
		{
			set_bit(TCCR0,CS00);
			clear_bit(TCCR0,CS01);
			set_bit(TCCR0,CS02);
		}
		
		
		if (Mode == Normal)
		{
			//Enable Normal Mode
			clear_bit(TCCR0,WGM01);
			clear_bit(TCCR0,WGM00);
		}
		
		else if (Mode == PWM_Fast)
		{
			//Enable Fast PWM Mode
			set_bit(TCCR0,WGM01);
			set_bit(TCCR0,WGM00);
		}
		else if (Mode == PWM_Phase_Correct)
		{
			//Enable Phase Correct Mode
			clear_bit(TCCR0,WGM01);
			set_bit(TCCR0,WGM00);
		}
		
		
		if (COM == COM_OFF)
		{
			clear_bit(TCCR0,COM00);
			clear_bit(TCCR0,COM01);
		}
		else if (COM == COM_Toggle) //reserved if not Normal Mode
		{
			clear_bit(TCCR0,COM01);
			set_bit(TCCR0,COM00);
		}
		else if (COM == COM_Clear)
		{
			clear_bit(TCCR0,COM00);
			set_bit(TCCR0,COM01);
		}
		else if (COM == COM_Set)
		{
			set_bit(TCCR0,COM00);
			set_bit(TCCR0,COM01);
		}
	}
	
	else if (timerNum == 1)
	{
		if (Prescaler == fclkOFF)
		{
			clear_bit(TCCR1B,CS10);
			clear_bit(TCCR1B,CS11);
			clear_bit(TCCR1B,CS12);
		}
		else if (Prescaler == fclk0)
		{
			set_bit(TCCR1B,CS10);
			clear_bit(TCCR1B,CS11);
			clear_bit(TCCR1B,CS12);

		}
		else if (Prescaler == fclk8)
		{
			clear_bit(TCCR1B,CS10);
			set_bit(TCCR1B,CS11);
			clear_bit(TCCR1B,CS12);
		}
		else if (Prescaler == fclk64)
		{
			set_bit(TCCR1B,CS10);
			set_bit(TCCR1B,CS11);
			clear_bit(TCCR1B,CS12);
		}
		else if (Prescaler == fclk256)
		{
			clear_bit(TCCR1B,CS10);
			clear_bit(TCCR1B,CS11);
			set_bit(TCCR1B,CS12);
		}
		else if (Prescaler == fclk1024)
		{
			set_bit(TCCR1B,CS10);
			clear_bit(TCCR1B,CS11);
			set_bit(TCCR1B,CS12);
		}
		
		
		if (Mode == Normal)
		{
			//Enable Normal Mode
			clear_bit(TCCR1A,WGM10);
			clear_bit(TCCR1A,WGM11);
			clear_bit(TCCR1B,WGM12);
			clear_bit(TCCR1B,WGM13);
		}
		
		else if (Mode == PWM_Fast)
		{
			//Enable Fast PWM Mode --> ICR1
			clear_bit(TCCR1A,WGM10);
			set_bit(TCCR1A,WGM11);
			set_bit(TCCR1B,WGM12);
			set_bit(TCCR1B,WGM13);
		}
		
		else if (Mode == PWM_Phase_Correct)
		{
			//Enable Phase Correct Mode --> ICR1
			clear_bit(TCCR1A,WGM10);
			set_bit(TCCR1A,WGM11);
			clear_bit(TCCR1B,WGM12);
			set_bit(TCCR1B,WGM13);
		}
		
		
		if (COM == COM_OFF)
		{
			clear_bit(TCCR1A,COM1A0);
			clear_bit(TCCR1A,COM1A1);
		}
		else if (COM == COM_Toggle) //reserved if not Normal Mode
		{
			set_bit(TCCR1A,COM1A0);
			clear_bit(TCCR1A,COM1A1);
		}
		else if (COM == COM_Clear)
		{
			clear_bit(TCCR1A,COM1A0);
			set_bit(TCCR1A,COM1A1);
		}
		else if (COM == COM_Set)
		{
			set_bit(TCCR1A,COM1A0);
			set_bit(TCCR1A,COM1A1);
		}
	}
}