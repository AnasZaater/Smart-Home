/*
 * MC_Selector.h
 *
 * Created: 6/15/2021 12:50:46 AM
 *  Author: ahmed
 */ 


#ifndef MC_SELECTOR_H_
#define MC_SELECTOR_H_

/*Micro-controllers*/
#define ATMEGA32        0
#define ATMEGA328P      1

/*Micro-controller Selector*/
#define MC              ATMEGA32

/*Micro-controller Options*/
#if MC == ATMEGA32
#include "MCU_ATMEGA32.h"
#elif MC == ATMEGA328P
#include "MCU_ATM328P.h"
#endif



#endif /* MC_SELECTOR_H_ */