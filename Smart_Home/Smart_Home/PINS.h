//This .h file contains the PINS used throughout the project
/* -------------------- LCD -------------------*/

// LCD Control Pins 
#define LCD_Control_Pins_Dir DDRA
#define LCD_Control_Pins_Port PORTA

#define RS 0
#define RW 1
#define EN 2

// LCD PINS and Directory 
#define LCD_Dir DDRA
#define LCD_Port PORTA
#define LCD_D0 0
#define LCD_D1 1
#define LCD_D2 2
#define LCD_D3 3
#define LCD_D4 4
#define LCD_D5 5
#define LCD_D6 6
#define LCD_D7 7


/* -------------------- Keypad -------------------*/

#define Keypad_Output_Write_Port PORTB
#define Keypad_Output_Read_Port PINB
#define Keypad_Output_Port_Dir DDRB

#define Keypad_Input_Write_Port PORTC
#define Keypad_Input_Read_Port PINC
#define Keypad_Input_Port_Dir DDRC


//output pins
#define output_pin_1 PINB4
#define output_pin_2 PINB5
#define output_pin_3 PINB6
#define output_pin_4 PINB7

//input pins
#define input_pin_1 PINC4
#define input_pin_2 PINC5
#define input_pin_3 PINC6
#define input_pin_4 PINC7




/* -------------------- SERVO -------------------*/
//SERVO PINS
#define servoControl PIND5 


/* -------------------- LEDS -------------------*/

//LED PINS
#define LED_1_PIN PINB0
#define LED_2_PIN PINB1
#define LED_3_PIN PINC2
#define LED_4_PIN PINC3
#define LED_5_PIN PIND6
//LED PORTS
#define LED_1_PORT PORTB
#define LED_2_PORT PORTB
#define LED_3_PORT PORTC
#define LED_4_PORT PORTC
#define LED_5_PORT PORTD

/* -------------------- BUZZER -------------------*/

#define BUZZER_PORT PORTD
#define BUZZER_PIN PIND7


/* -------------------- DIMMER -------------------*/

//DIMMER PINS
#define DIMMER_PIN PINB3

/* -------------------- LM35 PINS -------------------*/
#define LM35_PIN PINA3
#define LM35_DIR DDRA	// ADC pin(sensor)

/* -------------------- DC motor PINS -------------------*/
#define AC_PIN1 PIND3
#define AC_PIN2 PIND4
#define AC_PORT PORTD
#define AC_DIR DDRD  // DC motor pin

/* -------------------- Air Conditioner LED-------------------*/
#define AC_LED_DIR DDRB
#define AC_LED_PORT PORTB
#define AC_LED_PIN PINB2

/* -------------------- Interrupt -------------------*/
#define INT0_PIN PIND2
#define INT0_DIR DDRD
