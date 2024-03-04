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
//   1998      26       6    2030     7ee Juno_AVR.elf
   
#include "V4DEV.h"

const PROGMEM uint8_t CustomChar[32][8]={
  { 0x1f, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x1f } //Rectangle
, { 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f } //Full
, { 0, 0x4, 0xe, 0x1f, 0x15, 0x4, 0x4, 0 }           //Up Arrow
, { 0x0, 0x4, 0x4, 0x15, 0x1f, 0xe, 0x4, 0x0 }       //Down Arrow
, { 0x0, 0x4, 0xe, 0x1f, 0x0, 0xe, 0xa, 0x0 }        //Big Up Arrow
, { 0x0, 0xa, 0xe, 0x0, 0x1f, 0xe, 0x4, 0x0 }        //Big Down Arrow
, { 0xe, 0x4, 0x15, 0x1b, 0xe, 0x4, 0x4, 0x0 }       //DownArrowXXX
, { 0x0, 0xa, 0x15, 0x15, 0x11, 0xa, 0x4, 0x0 }      //Heart

, { 0x0, 0x0, 0xe, 0x11, 0x11, 0x11, 0xe, 0x0 }    //Zero
, { 0x0, 0x0, 0xe, 0x1f, 0x1f, 0x1f, 0xe, 0x0 }    //One
, { 0x0, 0x4, 0xa, 0x11, 0x11, 0xa, 0x4, 0x0 }     //Diamond
, { 0x0, 0x11, 0x4, 0xa, 0xa, 0x4, 0x11, 0x0 }     //sprinkle
, { 0x1f, 0xf, 0x7, 0x3, 0x1, 0x0, 0x0, 0x0 }      //angle arrow right
, { 0x1f, 0x1e, 0x1c, 0x18, 0x10, 0x0, 0x0, 0x0 }  //angle arrow left
, { 0x4, 0x16, 0x15, 0x18, 0x18, 0x15, 0x16, 0x4 } //Prompt XXX
, { 0x0, 0x0, 0xa, 0xa, 0x0, 0x11, 0xe, 0x0 }      //Smile Face

, { 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10 } // 1/5
, { 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18 } // 2/5
, { 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c } // 3/5
, { 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e } // 4/5
, { 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f } // 5/5
, { 0x0, 0xe, 0x11, 0x11, 0xa, 0x1b, 0x0, 0x0 }      //Ohm
, { 0xe, 0x15, 0x15, 0x0, 0x1b, 0xa, 0x4, 0x0 }      //mV
, { 0x3, 0x19, 0x14, 0x14, 0x14, 0x14, 0x19, 0x3 }   //Data

, { 0x4, 0xe, 0xe, 0xe, 0x1f, 0x0, 0x4, 0x0 }        //Alarm
, { 0x4, 0x2, 0x19, 0x1, 0x1, 0x19, 0x2, 0x4 }       //Smile Sideways
, { 0x1, 0x3, 0x5, 0x9, 0x5, 0x3, 0x1, 0x0 }         // <-Arrow
, { 0x8, 0xc, 0xa, 0x9, 0xa, 0xc, 0x8, 0x0 }         // Arrow->
, { 0x1e, 0x1c, 0x18, 0x18, 0x18, 0x18, 0x1c, 0x1e } // [ 
, { 0xf, 0x7, 0x3, 0x3, 0x3, 0x3, 0x7, 0xf }         // ]
, { 0x1e, 0x11, 0x16, 0x14, 0x14, 0x16, 0x11, 0x1e } // [x
, { 0xf, 0x11, 0xd, 0x5, 0x5, 0xd, 0x11, 0xf }       // ]x
};  

#define NOPOS 4 //number of positions
#define POSdiv (256/NOPOS+1)
int main(void){
V4_initi();

uint8_t CC=0;
LCD_writeText(0x40, "01234567", 8);
LCD_writeText(0x9, "CC LCDx", 7);
LCD_writeText(0x49, "FD 2024", 7);

  while(1){

  buttonScan();
  //CC=adcPOT/POSdiv;
  
  for( uint8_t i=0; i<8; i++ ){
    LCD_LoadNewCharFlash( &(CustomChar[i+8*CC]), i );
    LCD_COM((LCD_setADD)|i); 
    LCD_RAM( i );
  }
  
  CC++;
  if(CC==4){CC=0;}
  _delay_ms(1000);
 
  }//While-END
}//--main 
