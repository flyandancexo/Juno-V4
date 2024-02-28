/*###############################################################
# Juno V4 Core Library - Declaration File 
# Note:
=================================================================
# An Advanced MCU Project
################################################################*/

#define F_CPU 8000000UL  // 8 MHz
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
//### Serial
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void serial_init( void );
void serialWrite (uint8_t Sdata);
uint8_t serialRead( void ); 
void serialWriteString (char *text);

//#################################################################################
//### Miscellaneous code
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
	
#endif //JUNOV4_h
