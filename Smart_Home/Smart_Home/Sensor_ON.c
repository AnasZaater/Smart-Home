#include <avr/io.h>
#include "Bit_Op.h"
#include "PINS.h"
#include "Sensor_ON.h"

void Sensor_ON()
{
	clear_bit(LM35_DIR,LM35_PIN); // LM35 Input Pin
}
