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

//  text    data     bss     dec     hex filename
//  1286      26       0    1312     520 Juno_AVR.elf

#include "V4DEV.h"

//Create a custom character in SRAM
uint8_t CustomChar1[8]={0x0, 0xa, 0xa, 0xa, 0x0, 0x11, 0xe, 0x0}; //Smile
uint8_t CustomChar2[8]={0, 0x4, 0xe, 0x1f, 0x15, 0x4, 0x4, 0};    //Arrow
#define CC_SMILE_FACE 0
#define CC_UP_ARROW 1

int main(void){
LCD_init_4bitMode();

//Load 8 Custom Characters from SRAM to LCD
LCD_LoadNewChar( &CustomChar1[0], CC_SMILE_FACE);
LCD_LoadNewChar( &CustomChar2[0], CC_UP_ARROW);

LCD_COM( LCD_setADD|LCD_line1|0 ); //set LCD RAM Address to second line + 0
LCD_RAM( CC_SMILE_FACE );
LCD_writeText( LCD_line1|1, "Time:  ", 7 ); //7 characters (2-space)

uint8_t thr=0, tmin=0, tsec=0;
uint8_t arrowLOC=0;
uint8_t ccTOG=0;
  
  while(1){
  
  // 0123456789ABCEDF
  // &Time: 12:12:12
  // ^

  LCD_writeDec(7, thr, 2);
  LCD_writeText(9, ":", 1);
  
  LCD_writeDec(10, tmin, 2);
  LCD_writeText(12, ":", 1);
  
  LCD_writeDec(13, tsec, 2);
  
  LCD_COM( LCD_setADD|LCD_line2|arrowLOC );
  if( ccTOG ){ LCD_RAM(CC_UP_ARROW); }
  else { LCD_RAM(CC_SMILE_FACE); }
  

  _delay_ms(100);
  tsec++;
  if(tsec == 60 ){ tsec=0; tmin++; }
  if(tmin == 60 ){ tmin=0; thr++;}
  if(thr  == 12 ){ thr=0; }
  
  arrowLOC++; 
  if( arrowLOC == 16 ){ 
    arrowLOC=0; 
    ccTOG^=1; 
    
    //These 2 lines of code clear second line (write space char to second line)
    //Write time is about 16*40us=640us, and is faster than 1.64ms using clear or home
    LCD_COM( LCD_setADD|LCD_line2|0 );
    for( uint8_t i=0; i<16; i++ ){ LCD_RAM(' '); }
  }
  }//While-END
}//--main 



/*

*/
