
#ifndef UART_APPS_H_
#define UART_APPS_H_

void UART_Display_LED (unsigned char room, unsigned char status);
void UART_Welcome_Message();
unsigned char UART_Mode_Choice();
void LCD_Display_LED (unsigned char room, unsigned char status);
void UART_Rooms_Leds_Control();
void UART_Admin_Interfacing();
void UART_User_Interfacing();

#endif /* UART_APPS_H_ */