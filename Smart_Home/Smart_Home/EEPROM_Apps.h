


#ifndef EEPROM_APPS_H_
#define EEPROM_APPS_H_


#define Admins_number_BIT 1
#define Users_UART_number_BIT 2
#define Users_LCD_number_BIT 3

char Compare_Passwords(unsigned char* pass1 , unsigned char* pass2 , unsigned char Pass_Size);
void EEPROM_Save_Main_Admin();
void EEPROM_Write_0_Counters();


#endif /* EEPROM_APPS_H_ */