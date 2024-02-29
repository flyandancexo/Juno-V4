/*###############################################################
# Name: Juno V4 - Serial Communication, ADC and LCD DEV
# Hardware:
=====================================================
Serial Communication Interfaces: 
#UART -- Tx(D1-Green-LED) Rx(D0)
#SPI  -- SCK(B5-Blue-LED) MISO(B4) MOSI(B3) SS(B2)
#I2C  -- SDA(C4) SCL(C5-Red-LED)

ADC: POT: C7
4 buttons: C6 (0--1/2--2/3--3/4)

LED: B1 (Active LOW)
Switch: D2 (Active LOW)
=================================================================
3 Jumpers: 1, Enable LED; 2, Enable Auto-upload; 3, Enable 3.3V
=================================================================
# [Atmega88] - An Advanced MCU Project - 2024 © Flyandance
################################################################*/

//   text    data     bss     dec     hex filename
//   1206      12       0    1218     4c2 Juno_AVR.elf
   
#include "V4DEV.h"

int main(void){
LCD_init_4bitMode();

//ADC Input, 8-bit mode, Vref=VCC, CPU_clock/4
ADMUX= (1<<REFS0)|(1<<ADLAR)|6; //C6 is the input
ADCSRA= (1<<ADEN)|(1<<ADSC)|(1<<ADATE)|2;  
ADCSRB= 0;  //Free running mode

  while(1){
  LCD_writeText( 0, "Button", 6);
  LCD_writeText( 13, "POT", 3);
  
  ADMUX= (1<<REFS0)|(1<<ADLAR)|6; //C6 is the input
  _delay_us(100);//Because ADC doesn't convert instantly, we need some delay
  LCD_writeDec( 0x40, ADCH, 3 );

  ADMUX= (1<<REFS0)|(1<<ADLAR)|7; //C7 is the input
  _delay_us(100);//Because ADC doesn't convert instantly, we need some delay
  LCD_writeDec( 0x40|13, ADCH, 3 );
  
  }//While-END
}//--main 

/*
*/
