


#ifndef EEPROM_APPS_H_
#define EEPROM_APPS_H_

#define Main_Admin_pass_no 0x31
#define Admins_number_BIT 1
#define Users_UART_number_BIT 2
#define Users_LCD_number_BIT 3

char Compare_Passwords(unsigned char* pass1 , unsigned char* pass2 , unsigned char Pass_Size); //Function that compares pass1 array
																							  // with pass2 array elements to check
																							   
void EEPROM_Save_Main_Admin(); //Function saves the main admin password and username in a specifc block within EEPROM
void EEPROM_Write_0_Counters(); //nullifies the counters used to store the number of UART users, (LCD&Keypad users), and admins


#endif /* EEPROM_APPS_H_ */