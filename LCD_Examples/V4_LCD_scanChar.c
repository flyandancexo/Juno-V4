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
//   1230       0       0    1230     4ce Juno_AVR.elf

#include "V4DEV.h"

const PROGMEM uint8_t CustomChar[8][8]={
  { 0x1f, 0x1e, 0x1c, 0x18, 0x10, 0x0, 0x0, 0x0 }    //angle arrow left
, { 0, 0x4, 0xe, 0x1f, 0x15, 0x4, 0x4, 0 }           //Up Arrow
, { 0x0, 0x4, 0xe, 0x1f, 0x0, 0xe, 0xe, 0x0 }        //Big Up Arrow
, { 0x0, 0xa, 0x15, 0x15, 0x11, 0xa, 0x4, 0x0 }      //Heart
, { 0x0, 0xa, 0x15, 0xa, 0xa, 0x15, 0xa, 0x0 }       //sprinkle
, { 0x0, 0x4, 0xa, 0x11, 0x11, 0xa, 0x4, 0x0 }       //Diamond
, { 0x1f, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x1f } //Rectangle
, { 0x1f, 0xf, 0x7, 0x3, 0x1, 0x0, 0x0, 0x0 }        //angle arrow right
};  

int main(void){
LCD_init_4bitMode();

for( uint8_t i=0; i<8; i++ ){
  LCD_LoadNewCharFlash( &(CustomChar[i]), i );
}

uint8_t cc=0;

  while(1){
    for( uint8_t i=0; i<32; i++ ){
      cc++;
      _delay_ms(50);
      if(i<15) LCD_COM(LCD_setADD|0|i);   //write to first line
      else LCD_COM(LCD_setADD|0x40|i-16); //write to second line
      LCD_RAM(cc);
    }
    
  }//While-END
}//--main 

/*
*/
