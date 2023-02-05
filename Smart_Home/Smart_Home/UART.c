#define F_CPU 1000000UL
#include <avr/io.h>
#include "Bit_Op.h"
#include "PINS.h"
#include "UART.h"



void UART_Bit_Stops()
{
	#if Bit_Stops == 1
		clear_bit(UCSRC,USBS);	// Clearing this bit means 1-bit stops
	#elif Bit_Stops == 2
		set_bit(UCSRC,USBS);	// Setting this bit means 2-bit stops
	#endif
}

void UART_Mode_Select()
{
	#if Mode_Select == 0
	clear_bit(UCSRB,UMSEL);	// Asynchronous operation	
	#elif Bit_Stops == 1
	set_bit(UCSRB,UMSEL);	// Synchronous operation	
	#endif
}

void UART_Init (unsigned int baud)
{
	UBRRH = (unsigned char) (baud>>8);		// to write on the upper register
	UBRRL = (unsigned char) (baud);			// to write on the lower register
	
	UART_Mode_Select();		// Determining Synchronous/Asynchronous operation
	
	set_bit(UCSRB,TXEN);	// Enable Transmitter
	set_bit(UCSRB,RXEN);	// Enable Receiver
	set_bit(UCSRC,URSEL);	// Setting this bit means that UCSRC setting will be updated otherwise, UBRRH setting will be updated
	
	UART_Bit_Stops();		// Determining 1 / 2 bits stops
	
	// character size 8-bit
	set_bit(UCSRC,UCSZ0);	
	set_bit(UCSRC,UCSZ1);	
}

void UART_Transmit(unsigned char data)
{
	// If UDRE is one, the buffer is empty, and therefore ready to be written.
	while(!(UCSRA & (1<<UDRE)))		// stuck in a loop when UDRE is not one (the data is not ready to be transmitted)
	{
	}
	UDR = data;		// USART Data Register (UDR) stores the data to be transmitted 
}


unsigned char UART_Receive()
{
	// USART Receive Complete (RXC) flag is one when there are unread data in the receive buffer
	while(!(UCSRA & (1<<RXC)))		// stuck in a loop when RXC is not one (the receive buffer is empty. that is, does not contain any unread data)
	{
		AC_ON();
	}
	
	return UDR;		// returning the data stored in the USART Data Register (UDR)
}


void UART_Send_String (char* text)
{
	unsigned char j=0;
	while(text[j]!= '\0')	// Looping on the elements of array till the NULL character
	{
		UART_Transmit(text[j]);
		j++;
	}	
}










