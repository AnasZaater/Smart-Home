#ifndef AC_H_
#define AC_H_

// The Temperature Sensor (LM35) sensitivity is 10 millivolts/degree centigrade
// ADC maximum voltage is 5v and the maximum resolution is 1024

#define T_min 43	 // corresponding to 21 degrees
#define T_max 56	 // corresponding to 28 degrees
#define T_crit 82	 // corresponding to 40 degrees


void AC_Initialization();
void AC_Alarm();
void AC_ON();

#endif /* AC_H_ */