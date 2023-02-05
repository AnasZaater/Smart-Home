#define Servo_DIR DDRD
#define Deg0 2999
#define	Deg90 5250
void pwmStart(); //Starts the PWM mode in Timer peripheral
void Servo_Initialization(); //Starts the servo and setting the pin to output
void openDoor(); //Setting the OCR0 value to Deg90
void closeDoor(); //Setting the OCR0 value to Deg0