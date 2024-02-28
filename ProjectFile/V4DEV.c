/*###############################################################
# Juno V4 Core Library - Implementation File 
# Note:
=================================================================
# An Advanced MCU Project
################################################################*/

#include "V4DEV.h"

//#################################################################################
//### UART code
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void serial_init( void ){
UCSR0A = (1<<U2X0);
UCSR0B = (1<<RXEN0)|(1<<TXEN0);
UCSR0C = (1<<UCSZ01)|(1<<UCSZ00);
}

void serialWrite (uint8_t Sdata){
  while ( (UCSR0A & (1<<UDRE0))==0 );
  UDR0=Sdata;
}

uint8_t serialRead( void ){
  while ( (UCSR0A & (1<<RXC0)) == 0 );
  return UDR0;
}

void serialWriteString( char *text ){
  uint8_t i=0;
  while( text[i] !=0 ){
    serialWrite( text[i] ); 
    i++;
  }
  serialWrite('\n');
}
