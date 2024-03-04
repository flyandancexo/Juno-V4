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
//   1868       6       6    1880     758 Juno_AVR.elf
   
#include "V4DEV.h"

const PROGMEM uint8_t CustomChar[4][8]={
 { 0x1f, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x1f }  //Rectangle
, { 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f } //Full
, {  0xe, 0x4, 0x15, 0x1b, 0xe, 0x4, 0x4, 0x0 }      //DownArrow
, {  0x4, 0x16, 0x15, 0x18, 0x18, 0x15, 0x16, 0x4 }  //Data
};  

/*
  {  0x0, 0x0, 0xe, 0x11, 0x11, 0x11, 0xe, 0x0 }    //Zero
, {  0x0, 0x0, 0xe, 0x1f, 0x1f, 0x1f, 0xe, 0x0 }    //One
*/

void binaryDecoder( uint16_t data );

int main(void){
V4_initi();

LCD_LoadNewCharFlash( &(CustomChar[0]), 0 );
LCD_LoadNewCharFlash( &(CustomChar[1]), 1 );
LCD_LoadNewCharFlash( &(CustomChar[2]), 2 );
LCD_LoadNewCharFlash( &(CustomChar[3]), 3 );

LCD_writeCC  (9, 2);
LCD_writeText(5, "BINx", 4);
uint16_t ranVar;
uint8_t bit=0;
  while(1){

  _delay_ms(200);
  ranVar=(1<<bit);
  bit++;
  if(bit==16){ bit=0; }
  LCD_writeHex(0, ranVar, 4);
  LCD_writeDec(11, ranVar, 5);
  binaryDecoder(ranVar);

  }//While-END
}//--main 

void binaryDecoder( uint16_t data ){
  for( uint8_t i=0; i<16; i++ ){
    LCD_COM((LCD_setADD|0x40)+i);   //write to first line
    if( data& (1<<(15-i)) ){ LCD_RAM( 1 );}
    else { LCD_RAM( 0 );}
  }
}
