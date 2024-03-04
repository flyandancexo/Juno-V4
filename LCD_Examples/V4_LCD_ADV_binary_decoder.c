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
//   1844      14       6    1864     748 Juno_AVR.elf
   
#include "V4DEV.h"

const PROGMEM uint8_t CustomChar[4][8]={
  {  0x0, 0x0, 0xe, 0x11, 0x11, 0x11, 0xe, 0x0 }    //Zero
, {  0x0, 0x0, 0xe, 0x1f, 0x1f, 0x1f, 0xe, 0x0 }    //One
, {  0xe, 0x4, 0x15, 0x1b, 0xe, 0x4, 0x4, 0x0 }     //DownArrow
, {  0x4, 0x16, 0x15, 0x18, 0x18, 0x15, 0x16, 0x4 } //Data
};  

void binaryDecoder( uint8_t data );

int main(void){
V4_initi();

LCD_LoadNewCharFlash( &(CustomChar[0]), 0 );
LCD_LoadNewCharFlash( &(CustomChar[1]), 1 );
LCD_LoadNewCharFlash( &(CustomChar[2]), 2 );
LCD_LoadNewCharFlash( &(CustomChar[3]), 3 );

uint8_t data=0;
LCD_writeCC  (0, 2);
LCD_writeText(1, "Data", 4);
LCD_writeCC  (5, 2);
LCD_writeCC  (0x40, 3);

LCD_writeText(8, "76543210", 8);
  while(1){

  _delay_ms(500);
  binaryDecoder(data);
  LCD_writeDec(0x41, data, 3);
  data++;

  }//While-END
}//--main 

void binaryDecoder( uint8_t data ){
  for( uint8_t i=0; i<8; i++ ){
    LCD_COM((LCD_setADD|0x40)+8+i);   //write to first line
    if( data& (1<<(7-i)) ){ LCD_RAM( 1 );}
    else { LCD_RAM( 0 );}
  }
}
