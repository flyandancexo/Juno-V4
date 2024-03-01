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
//   1750      18       6    1774     6ee Juno_AVR.elf
   
#include "V4DEV.h"

int main(void){
V4_initi(); //initializes both LCD, button, POT and more
uint8_t number=123;
int8_t text[]="Juno V4";

  while(1){
  buttonScan(); //scan button and more
  
  //Write text[] to address 0( from top left corner )
  LCD_writeText( 0, text, sizeof(text)-1 ); //-1 because we don't want to write NULL
  
  //address starts after text[], write 9 characters (2 spaces)
  LCD_writeText( sizeof(text)-1, " 2024 LCD", 9 );
  
  //address 0x40 is first character on second line
  //reserves 3 spaces for test variable. It's an 8-bit number from 0-255
  LCD_writeDec( 0x40|0, number, 3 );
  
  //the same variable is written as a hexadecimal, only 2 spaces are needed
  LCD_writeHex( 0x40|4, number, 2 );

  //The potentiometer is defined as adcPOT
  LCD_writeDec( 0x40|7, adcPOT, 3 ); //displays the POT value 0-255
  
  //LCD contrast Value
  LCD_writeHex( 0x40|11, LCD_CO, 2 );
  
  //LCD backlit brightness level
  LCD_writeHex( 0x40|14, LCD_BL, 2 );
  
  //Here is the code to use the buttons
  if(bra){ number--;}
  if(brb){ number++;}
  if(brc){ LCD_CO+=10; if(LCD_CO>130){LCD_CO=0;} } //increase LCD contrast
  if(brd){ LCD_BL+=10; if(LCD_BL>130){LCD_BL=0;} } //increase LCD brightness
  
  }//While-END
}//--main 


/*
*/
