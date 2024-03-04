/*###############################################################
# Juno V4 Core Library - Declaration File V1.2
# Note:
=================================================================
# An Advanced MCU Project - 2024 © Flyandance
################################################################*/

#define F_CPU 16000000UL  // 8 MHz
#include <util/delay.h>

#include <inttypes.h>
#include <avr/io.h>

#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <avr/eeprom.h> 

#include "v4LCD.h"

#ifndef JUNOV4_h
#define JUNOV4_h

//#################################################################################
//### Variables
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>

//Juno Button 2.0 Defines
#define bra (but.BR==1)  //press and release
#define brb (but.BR==2)
#define brc (but.BR==3)
#define brd (but.BR==4)

typedef struct button {
		uint8_t released: 1;   //set for press and release logic
		uint8_t CS: 4;  //Current State (can be 8-bit)
		uint8_t PS: 4;  //Previous State(can be 8-bit)
		uint8_t BS: 4;  //BS is for internal logic (up to 15 button logics)
		uint8_t BR: 4;  //BR is for external logic (or up to 5 buttons w/ 3 triggers each)
}but_ti;
extern but_ti but;
void buttonScan( void );

extern uint8_t adcPOT;

//#################################################################################
//### Serial
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void serial_init( void );
void serialWrite (uint8_t Sdata);
uint8_t serialRead( void ); 
void serialWriteString (char *text);

//#################################################################################
//### Miscellaneous code
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void V4_initi( void );  //Enable timer2 for ADC and button

#endif //JUNOV4_h
