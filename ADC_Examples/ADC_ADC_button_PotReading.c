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
//   1610      26       6    1642     66a Juno_AVR.elf
   
#include "V4DEV.h"

int main(void){
V4_initi();
uint8_t test=123;
  while(1){
  buttonScan();
  LCD_writeText( 0, "Potentiometr", 12 );
  LCD_writeDec( 13, adcPOT, 3 );
  
  LCD_writeText( 0x40, "ADC Button->", 12 );
  LCD_writeDec( 0x40|13, test, 3 );
  
  if(bra){ test++;}
  if(brb){ test--;}
  if(brc){ test=88;}
  if(brd){ test=111;}
  
  }//While-END
}//--main 

/*


//ADC Input, 8-bit mode, Vref=VCC, CPU_clock/4
ADMUX= (1<<REFS0)|(1<<ADLAR)|7; //C7 is the input
ADCSRA= (1<<ADEN)|(1<<ADSC)|(1<<ADATE)|2;  
ADCSRB= 0;  //Free running mode

  LCD_writeText( 0, "LCD Arrow Naviga", 16);
  
  
  LCD_COM( 0x80|0x40|(ADCH/16) ); // 256/16=16
  LCD_RAM( BIG_UPARROW );
  
  //Write space above and below the arrow position 
  LCD_COM( (0x80|0x40|(ADCH/16))+1 );
  LCD_RAM( ' ' );
  LCD_COM( (0x80|0x40|(ADCH/16))-1 );
  LCD_RAM( ' ' );  
  
*/
