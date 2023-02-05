/*
SLA+W : en el master by-write 3la el bus
SLA+R: en el master by-check en rl bus lessa masko

*/

#define F_CPU 16000000UL
#include <avr/io.h>
#include <math.h>	// a library which pow function in included
#include <util/delay.h>
#include "Bit_Op.h"
#include "I2C_Master.h"
#include <avr/eeprom.h>

void I2C_Initialization()
{
	TWBR = BITRATE(TWSR=0x00);	// Get bit rate register value by formula
}

char I2C_Start(char address)
{
	char status;
	TWCR=(1<<TWSTA)|(1<<TWEN)|(1<<TWINT);	/* Enable TWI, generate START					*/
	while(!(TWCR&(1<<TWINT)));				/* Wait until TWI finish its current job		*/
	status=TWSR&0xF8;						/* Read TWI status register						*/
	if(status!=0x08)						/* Check weather START transmitted or not?		*/
	return 0;								/* Return 0 to indicate start condition fail	*/
	TWDR= address;							/* Write SLA+W in TWI data register				*/
	TWCR=(1<<TWEN)|(1<<TWINT);				/* Enable TWI & clear interrupt flag			*/
	while(!(TWCR&(1<<TWINT)));				/* Wait until TWI finish its current job		*/
	status=TWSR&0xF8;						/* Read TWI status register */
	if(status==0x18)						/* Check for SLA+W transmitted &ack received	*/
	return 1;								/* Return 1 to indicate ack received			*/
	if(status==0x20)						/* Check for SLA+W transmitted &nack received	*/
	return 2;								/* Return 2 to indicate nack received			*/
	else
	return 3;								/* Else return 3 to indicate SLA+W failed		*/
}

char I2C_Repeated_Start(char read_address)
{
	char status;							/* Declare variable								*/
	TWCR=(1<<TWSTA)|(1<<TWEN)|(1<<TWINT);	/* Enable TWI, generate start					*/
	while(!(TWCR&(1<<TWINT)));				/* Wait until TWI finish its current job		*/
	status=TWSR&0xF8;						/* Read TWI status register						*/
	if(status!=0x10)						/* Check for repeated start transmitted			*/
	return 0;								/* Return 0 for repeated start condition fail	*/
	TWDR=read_address;						/* Write SLA+R in TWI data register				*/
	TWCR=(1<<TWEN)|(1<<TWINT);				/* Enable TWI and clear interrupt flag			*/
	while(!(TWCR&(1<<TWINT)));				/* Wait until TWI finish its current job		*/
	status=TWSR&0xF8;						/* Read TWI status register						*/
	if(status==0x40)						/* Check for SLA+R transmitted &ack received	*/
	return 1;								/* Return 1 to indicate ack received			*/
	if(status==0x48)						/* Check for SLA+R transmitted &nack received	*/
	return 2;								/* Return 2 to indicate nack received			*/
	else
	return 3;								/* Else return 3 to indicate SLA+W failed		*/
}


char I2C_Write(char data)	/* I2C write function */
{
	char status;				/* Declare variable */
	TWDR=data;					/* Copy data in TWI data register */
	TWCR=(1<<TWEN)|(1<<TWINT);	/* Enable TWI and clear interrupt flag */
	while(!(TWCR&(1<<TWINT)));	/* Wait until TWI finish its current job */
	status=TWSR&0xF8;			/* Read TWI status register */
	if(status==0x28)			/* Check for data transmitted &ack received */
	return 0;					/* Return 0 to indicate ack received */
	if(status==0x30)			/* Check for data transmitted &nack received */
	return 1;					/* Return 1 to indicate nack received */
	else
	return 2;					/* Else return 2 for data transmission failure */
}



/*
I2C_Read_Ack function()
This function read data available on
 the SDA line and returns its 
acknowledgment to the slave device
 about data read successful and
 also tells slave to transmit another data.*/

char I2C_Read_Ack()
{
	TWCR=(1<<TWEN)|(1<<TWINT)|(1<<TWEA);	/* Enable TWI, generation of ack */
	while(!(TWCR&(1<<TWINT)));				/* Wait until TWI finish its current job */
	return TWDR;							/* Return received data */
}

/*  I2C_Read_Nack function()
	This function read last needed data byte 
	available on the SDA line but does
	not returns an acknowledgment of it. It 
	used to indicate slave that master don’t 
	want next data and want to stop communication.	*/

char I2C_Read_Nack()		
{
	// Enable TWI and clear interrupt flag 
	set_bit(TWCR,TWEN);
	set_bit(TWCR,TWINT);
	while(!(TWCR & (1<<TWINT)))		// Wait until TWI finish its current job 
	{
	}
	return TWDR;				// Return received data 
}

void I2C_Stop()								/* I2C stop function */
{
	TWCR=(1<<TWSTO)|(1<<TWINT)|(1<<TWEN);	/* Enable TWI, generate stop */
	while(TWCR&(1<<TWSTO));					/* Wait until stop condition execution */
}



char I2C_START_Transmitter_Receiver_Mode(char address , char Master_Mode)
{
	char status = 0;
	set_bit(TWCR,TWSTA);	// TWI START Condition Bit, setting it to one means that this device is the master.
	set_bit(TWCR,TWEN);		// TWI Enable Bit, When TWEN is written to one, the TWI takes control over the I/O pins connected to the SCL and SDA pins.
	set_bit(TWCR,TWINT);	// TWI Interrupt Flag, The TWINT Flag must be cleared by software by writing a logic one to it.
	
	
	while(!(TWCR & (1<<TWINT)))		// Stuck in a loop until the TWI Interrupt Flag is raised
	{
	}
	
	status = TWSR & 0xF8;					// Read the most significant 5 bits (TWS7:TWS3) of TWI status register (TWSR)
	
	if(status != START)						// Check whether START transmitted or not.
	{
		return 0;							// Return 0 to indicate start condition failed
	}
	
	TWDR = address;								// Write Slave's Address in TWI data register (TWDR)
	TWCR = (1<<TWEN)|(1<<TWINT);				// Enable TWI & Clear Interrupt Flag
	
	while(!(TWCR & (1<<TWINT)))		// Stuck in a loop until the TWI Interrupt Flag is raised
	{
	}
	
	status = TWSR & 0xF8;						// Read the most significant 5 bits (TWS7:TWS3) of TWI status register (TWSR)
	
	if (Master_Mode == Master_Transmitter_Mode)
	{
		if(status == SLA_W_transmitted_ACK_received)		// Check for SLA+W transmitted & ACK received
		{
			return 1;								// Return 1 to indicate ACK received
		}
		else if(status == SLA_W_transmitted_NACK_received)		// Check for SLA+W transmitted & NACK received
		{
			return 2;								// Return 2 to indicate NACK received
		}
		else
		{
			return 3;								// Return 3 for arbitration lost in slave address or data byte (e.g.0x38)
		}
	}
	
	else if (Master_Mode == Master_Receiver_Mode)
	{
		if(status == SLA_R_transmitted_ACK_received)		// Check for SLA+W transmitted & ACK received
		{
			return 1;								// Return 1 to indicate ACK received
		}
		else if(status == SLA_R_transmitted_NACK_received)		// Check for SLA+W transmitted & NACK received
		{
			return 2;								// Return 2 to indicate NACK received
		}
		else
		{
			return 3;								// Return 3 for arbitration lost in slave address or data byte (e.g.0x38)
		}
	}
}


char I2C_Repeated_START_Transmitter_Receiver_Mode(char address , char Master_Mode)
{
	char status;
	set_bit(TWCR,TWSTA);	// TWI START Condition Bit, setting it to one means that this device is the master.
	set_bit(TWCR,TWEN);		// TWI Enable Bit, When TWEN is written to one, the TWI takes control over the I/O pins connected to the SCL and SDA pins.
	set_bit(TWCR,TWINT);	// TWI Interrupt Flag, The TWINT Flag must be cleared by software by writing a logic one to it.
	
	while(!(TWCR & (1<<TWINT)))		// Stuck in a loop until the TWI Interrupt Flag is raised
	{
	}
	
	status = TWSR & 0xF8;					// Read the most significant 5 bits (TWS7:TWS3) of TWI status register (TWSR)
	
	if(status != Repeated_START)						// Check whether Repeated START transmitted or not.
	{
		return 0;							// Return 0 to indicate start condition failed
	}
	
	TWDR = address;								// Write Slave's Address in TWI data register (TWDR)
	TWCR = (1<<TWEN)|(1<<TWINT);				// Enable TWI & Clear Interrupt Flag
	while( ! (TWCR & (1<<TWINT)) )		// Stuck in a loop until the TWI Interrupt Flag is raised
	{
	}
	
	status = TWSR & 0xF8;						// Read the most significant 5 bits (TWS7:TWS3) of TWI status register (TWSR)
	
	if (Master_Mode == Master_Transmitter_Mode)
	{
		if(status == SLA_W_transmitted_ACK_received)		// Check for SLA+W transmitted & ACK received
		{
			return 1;								// Return 1 to indicate ACK received
		}
		else if(status == SLA_W_transmitted_NACK_received)		// Check for SLA+W transmitted & NACK received
		{
			return 2;								// Return 2 to indicate NACK received
		}
		else
		{
			return 3;								// Return 3 for arbitration lost in slave address or data byte (e.g.0x38)
		}
	}
	
	else if (Master_Mode == Master_Receiver_Mode)
	{
		if(status == SLA_R_transmitted_ACK_received)		// Check for SLA+W transmitted & ACK received
		{
			return 1;								// Return 1 to indicate ACK received
		}
		else if(status == SLA_R_transmitted_NACK_received)		// Check for SLA+W transmitted & NACK received
		{
			return 2;								// Return 2 to indicate NACK received
		}
		else
		{
			return 3;								// Return 3 for arbitration lost in slave address or data byte (e.g.0x38)
		}
	}
}

