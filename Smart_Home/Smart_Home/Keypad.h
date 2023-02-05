

#ifndef KEYPAD_H_
#define KEYPAD_H_

#define NOT_PRESSED 0xFF




void Keypad_Init(void);//Initialize the pins used for keypad
unsigned char Keypad_Get_Value();//Stores the values written by pressing the buttons on keypad

#endif /* KEYPAD_H_ */