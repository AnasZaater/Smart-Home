/*
 * EEPROM.h
 *
 * Created: 29/01/2023 6:58:24 PM
 *  Author: Lenovo
 */ 


#ifndef EEPROM_H_
#define EEPROM_H_

#define EEPROM_SlAVE_ADDRESS_BASE 0x50	//01010xxx

#define EEPROM_BLOCK_0 0
#define EEPROM_BLOCK_1 1
#define EEPROM_BLOCK_2 2
#define EEPROM_BLOCK_3 3
#define EEPROM_BLOCK_4 4
#define EEPROM_BLOCK_5 5
#define EEPROM_BLOCK_6 6
#define EEPROM_BLOCK_7 7


#define BLOCK_0 (EEPROM_SlAVE_ADDRESS_BASE|EEPROM_BLOCK_0)<<1
#define BLOCK_1 (EEPROM_SlAVE_ADDRESS_BASE|EEPROM_BLOCK_1)<<1
#define BLOCK_2 (EEPROM_SlAVE_ADDRESS_BASE|EEPROM_BLOCK_2)<<1
#define BLOCK_3 (EEPROM_SlAVE_ADDRESS_BASE|EEPROM_BLOCK_3)<<1
#define BLOCK_4 (EEPROM_SlAVE_ADDRESS_BASE|EEPROM_BLOCK_4)<<1
#define BLOCK_5 (EEPROM_SlAVE_ADDRESS_BASE|EEPROM_BLOCK_5)<<1
#define BLOCK_6 (EEPROM_SlAVE_ADDRESS_BASE|EEPROM_BLOCK_6)<<1
#define BLOCK_7 (EEPROM_SlAVE_ADDRESS_BASE|EEPROM_BLOCK_7)<<1


#define EEPROM_PAGE_SIZE 16


/*---------- EEPROM Blocks Functions----------*/
#define Main_Admin_Block BLOCK_0
#define Admin_Username_Block BLOCK_1
#define Admin_Password_Block BLOCK_2
#define UART_User_Username_Block BLOCK_3
#define UART_User_Password_Block BLOCK_4
#define LCD_User_Username_Block BLOCK_5
#define LCD_User_Password_Block BLOCK_6
#define Counters_Block BLOCK_7


#define ADMINS_MAX_NO 64
#define USERS_MAX_NO 64


void EEPROM_Initialization();	//Initializing I2C communication with 100KHz
void EEPROM_writeByte(char EEPROM_Block,char EEPROM_Address,char Data); //writing a data byte in a specific eeprom block
void EEPROM_readByte(char EEPROM_Block,char EEPROM_Address,char *Data); // reading a data byte from a specific eeprom block
void EEPROM_readDatastream(char EEPROM_Block,char EEPROM_Address,char *Data,char DataSize); // reading a stream of data bytes from a specific eeprom block

#endif /* EEPROM_H_ */