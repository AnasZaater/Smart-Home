#include <avr/io.h>
#include <avr/interrupt.h>
#include "Bit_Op.h"
#include "PINS.h"
#include "Interrupt_Start.h"

void Interrupt_Start()
{
	clear_bit(INT0_DIR,INT0_PIN); //pinMode of INT0 pin --> Input
	set_bit(GICR,INT0); //Enable External Interrupt
	
	//Low-level on INT0 PIN generates an interrupt request
	clear_bit(MCUCR,ISC01);
	clear_bit(MCUCR,ISC00);
	sei();
}