
#define Bit_Stops 2
#define Mode_Select 0


#define freq_16MHz_baud_9600 103
#define freq_1MHz_baud_9600 6
#define freq_1MHz_baud_4800 12


void UART_Bit_Stops();
void UART_Mode_Select();
void UART_Init (unsigned int baud);
void UART_Transmit(unsigned char data);
void UART_Send_String (char* text);
unsigned char UART_Receive();
