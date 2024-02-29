/*###############################################################
# Juno V4 Core Library - Implementation File V1.2
# Note:
=================================================================
# An Advanced MCU Project - 2024 © Flyandance
################################################################*/

#include "V4DEV.h"

static uint8_t counter=0;
static uint8_t adcButton; //make adcButton accessible only in this file
uint8_t adcPOT;           //make adcPOT accessible globally

//#################################################################################
//### UART code
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void V4_initi( void ){

//Initialize LCD code 
LCD_init_4bitMode();

//Timer2: CTC 10kHz Interrupt Mode 100us- 25,000us(25ms)
//8000000/8/10000=100 OCR=99
TCCR2A = (1<<WGM21); 
TCCR2B = 2; //Clock/8  (0:Off 1-7:[1,8,32,64,128,256,1024])
OCR2A = 99;

//ADC enable in Free running mode
ADCSRA= (1<<ADEN)|(1<<ADSC)|(1<<ADATE)|2;  
ADCSRB= 0;

DDRB |=(1<<1); // B1 LED for debug and simple status display
PORTB|=(1<<1); // Active LOW, turn it OFF initially
}

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

//#################################################################################
//### Button code
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
but_ti but={ .PS=0, .CS=0 };  //button data initialized, to ensure button logic not triggered by random data.

buttonScan( void ){

//Edge detection, set Button Event
if( but.PS != but.CS ){
	but.PS=but.CS;
  //if all buttons have been released
  if( but.CS == 0 ){ but.released=1; }
  else if( but.CS == 1 ){ but.BS= 1; }  //B1 pressed
  else if( but.CS == 2 ){ but.BS= 2; }  //B2 pressed	
  else if( but.CS == 3 ){ but.BS= 3; }  //B3 pressed
  else if( but.CS == 4 ){ but.BS= 4; }  //B4 pressed		
}

//Button Read is cleared one main loop later
//This implies but.BR is read once every main loop
but.BR=0;   

//After the button has been pressed and then released
if(but.released){
  but.BR = but.BS;
	but.released=0;
}

//10kHz 100us Loop
if( TIFR2 & (1<<OCF2A) ){
  TIFR2 |= (1<<OCF2A);
  
  counter++; 
  //100us * 10 = 1ms 
  if(counter==10){
    counter=0; 
  }
  
  if(counter==0){
    adcPOT=ADCH;  //Read POT
    ADMUX= (1<<REFS0)|(1<<ADLAR)|6; //C6 is the button input
  }
  
  if(counter==1){
    adcButton=ADCH;  //read button
    ADMUX= (1<<REFS0)|(1<<ADLAR)|7; //C7 is the POT input
  }
  
//Save the Current button State, and This can be from any source.
//Since ADC reading already added 5ms delay to the buttons, a button debounce is not needed
	if( adcButton > (255-20))                                   { but.CS=0; }	
	else if( adcButton <20 )                                    { but.CS=1; }
	else if( (adcButton >(127-10) ) && (adcButton <(127+10) ) ) { but.CS=2; }
	else if( (adcButton >(170-10) ) && (adcButton <(170+10) ) ) { but.CS=3; }
	else if( (adcButton >(191-10) ) && (adcButton <(191+10) ) ) { but.CS=4; }
  
}//10k-timer2-loop-END

}//buttonScan-END
