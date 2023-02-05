
#include <avr/io.h>
#include <math.h>	// a library which pow function in included
#define SCL_CLK 10000	// selected clock

//SCL frequency =  (CPU CLK frequency)/(16+2(TWBR)*4^TWPS )
// f/sf =16+2(TWBR)*4^TWPS
//f/sf-16 =2(TWBR)*4^TWPS
//(f/sf-16)/4^TWPS*2 = TWBR
/* Define bit rate */
#define BITRATE(TWSR)	((F_CPU/SCL_CLK)-16)/(2*pow(4,(TWSR&((1<<TWPS0)|(1<<TWPS1)))))	//=&0x03


#define START 0x08
#define Repeated_START 0x10

/* ------------------< Master Mode >------------------ */
// Master Transmitter Mode
#define Master_Transmitter_Mode '1'

// Master Receiver Mode
#define Master_Receiver_Mode '0'

/* ------------------< Address Acknowledgement >------------------ */

// Master Transmitter Mode
#define SLA_W_transmitted_ACK_received 0x18
#define SLA_W_transmitted_NACK_received 0x20

// Master Receiver Mode
#define SLA_R_transmitted_ACK_received 0x40
#define SLA_R_transmitted_NACK_received 0x48


/* ------------------< Data Acknowledgement >------------------ */

// Master Transmitter Mode
#define Data_transmitted_ACK_received 0x28
#define Data_transmitted_NACK_received 0x30


// Master Receiver Mode
#define Data_received_ACK_returned 0x50
#define Data_received_NACK_returned 0x58


void I2C_Initialization();

char I2C_START_Transmitter_Receiver_Mode(char address , char Master_Mode);
char I2C_Repeated_START_Transmitter_Receiver_Mode(char address , char Master_Mode);

char I2C_Write(char data);
char I2C_Read_Ack();
char I2C_Read_Nack();
void I2C_Stop();

char I2C_Start(char address);
char I2C_Repeated_Start(char read_address);