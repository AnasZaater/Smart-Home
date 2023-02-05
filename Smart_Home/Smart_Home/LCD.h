


#ifndef LCD_H_
#define LCD_H_


/* -------------------- LCD Mode -------------------*/
#define LCD_Mode 4


/* -------------------- Default Interface Modes -------------------*/
#define Mode_4_Bit 0x28
#define Mode_8_Bit 0x38

/* -------------------- Commands -------------------*/

#define Clear_Display 0x01
#define Return_Home 0x02
#define Start_New_Line 0xC0

//  Entry Set Mode (Shifting Display and Cursor)
#define Cusror_shifts_left 0x04				// I/D : 0 , S : 0
#define Entire_Display_shifts_left 0x05		// I/D : 0 , S : 1
#define Cusror_shifts_right 0x06			// I/D : 1 , S : 0
#define Entire_Display_shifts_right 0x07	// I/D : 1 , S : 1

// Display ON/OFF Control
#define Display_OFF_Cusror_OFF_Blink_OFF 0x08	// D : 0 , C : 0 , B : 0
#define Display_OFF_Cusror_OFF_Blink_ON 0x09	// D : 0 , C : 0 , B : 1
#define Display_OFF_Cusror_ON_Blink_OFF 0x0A	// D : 0 , C : 1 , B : 0
#define Display_OFF_Cusror_ON_Blink_ON 0x0B		// D : 0 , C : 1 , B : 1
#define Display_ON_Cusror_OFF_Blink_OFF 0x0C	// D : 1 , C : 0 , B : 0
#define Display_ON_Cusror_OFF_Blink_ON 0x0D		// D : 1 , C : 0 , B : 1
#define Display_ON_Cusror_ON_Blink_OFF 0x0E		// D : 1 , C : 1 , B : 0
#define Display_ON_Cusror_ON_Blink_ON 0x0F		// D : 1 , C : 1 , B : 1

// Cursor or Display shift
//Cursor or display shift shifts the cursor position or display to the right or left without writing or reading display data
#define Cursor_moves_left 0x10		// S/C : 0 , R/L : 0 
#define Cursor_moves_right 0x14		// S/C : 0 , R/L : 1 
#define Display_shifts_left 0x18	// S/C : 1 , R/L : 0 
#define Display_shifts_right 0x1C	// S/C : 1 , R/L : 1 

// Function Set
#define Mode_4_Bit_1_Line_5x8_dots 0x20			// DL : 0 , N : 0 , F : 0
#define Mode_4_Bit_1_Line_5x10_dots 0x24		// DL : 0 , N : 0 , F : 1
#define Mode_4_Bit_2_Line_5x8_dots 0x28			// DL : 0 , N : 1 , F : 0
#define Mode_4_Bit_2_Line_5x10_dots 0x2C		// DL : 0 , N : 1 , F : 1
#define Mode_8_Bit_1_Line_5x8_dots 0x30			// DL : 1 , N : 0 , F : 0
#define Mode_8_Bit_1_Line_5x10_dots 0x34		// DL : 1 , N : 0 , F : 1
#define Mode_8_Bit_2_Line_5x8_dots 0x38			// DL : 1 , N : 1 , F : 0
#define Mode_8_Bit_2_Line_5x10_dots 0x3C		// DL : 1 , N : 1 , F : 1


// Cursor Position (each row has a position starting from 0 to 7)
#define Row_1_pos_0 0x80
#define Row_2_pos_0 0xC0



void LCD_Send_CMD (unsigned char data);//Sends a command on LCD
void LCD_Write_Char (unsigned char data);//Writes a character which is passed as an argument
void LCD_Init(); //Initialize LCD connection
void LCD_Write_String(char* text); //Writes a stream of characters
void LCD_Set_Cursor(char row, char pos);//Controls the position of the cursor
void LCD_Clear_Screen();//Clears the screen to write other data on it
void LCD_Write_Integer(unsigned long int data);//Writes integer instead of character
void LCD_Write_Decimal(float data);//Writes floating point data on LCD

#endif /* LCD_H_ */