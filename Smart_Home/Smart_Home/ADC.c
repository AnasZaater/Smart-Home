#define F_CPU 16000000UL
#include <util/delay.h>
#include <avr/io.h>
#include "ADC.h"
#include "Bit_Op.h"

void ADC_Start(int ADC_Channel_Num)
{
	set_bit(ADCSRA,ADEN); // ENABLE ADC
    set_bit(ADMUX,REFS0); // AVCC WITH EXTERNAL CAPACITOR AT AREF PIN
	ADMUX |= ADC_Channel_Num; // set required pin
	set_bit(ADCSRA,ADPS2); // pre-scaling division
}

int ADC_READ()
{
	set_bit(ADCSRA,ADSC); // START CONVERSION
	while(!(ADCSRA &(1<<ADIF))){ } // NO OPERATION WHILE CONVERSTION
	_delay_us(10);
    return ((int)ADCL+(int)ADCH*256); // type  cast of each register from char to integer and calculating
}
