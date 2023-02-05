#include <avr/io.h>
#include "Bit_Op.h"
#include "PINS.h"
#include "Servo.h"
#include "TimerFunc.h"

void Servo_Initialization()
{
	set_bit(Servo_DIR,servoControl);
	Timer(1,PWM_Fast,COM_Clear,fclk8);
	ICR1 = 39999;	//FPWM = 50 Hz
	TCNT1 = 0;		//Begin the timer count from "0"
	OCR1A = Deg0;	// Setting the door as closed in the beginning of the system 
}

void openDoor()
{
	OCR1A = Deg90; // Rotates Servo by 90 deg position
}
void closeDoor()
{
	OCR1A = Deg0; // Rotates Servo to 0 deg position
}
