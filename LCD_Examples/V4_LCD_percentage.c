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
//   1376      12       0    1388     56c Juno_AVR.elf

#include "V4DEV.h"

const PROGMEM uint8_t CustomChar[8][8]={
  { 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10 } // 1/5
, { 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18 } // 2/5
, { 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c } // 3/5
, { 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e } // 4/5
, { 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f } // 5/5
, { 0, 0x4, 0xe, 0x1f, 0x15, 0x4, 0x4, 0 }           //Up Arrow
, { 0x0, 0x8, 0xc, 0xe, 0xf, 0xe, 0xc, 0x8 }         //Right Arrow
, { 0x0, 0x2, 0x6, 0xe, 0x1e, 0xe, 0x6, 0x2 }        //Left Arrow
};  

int main(void){
LCD_init_4bitMode();

for( uint8_t i=0; i<8; i++ ){
  LCD_LoadNewCharFlash( &(CustomChar[i]), i );
}

uint16_t percentage=0; 
uint8_t secondLine[16];

  while(1){
  
    _delay_ms(100);
    if( percentage == 0 ) {
      for( uint8_t i=0; i<16; i++ ){secondLine[i]=' ';} //clear second line
    }
    percentage++; // 16*5=80 100/80=1.25  80*1.25  80*125/100=100
    if( percentage==80 ){ 
      percentage=0; 
    }
    
    //Convert 0-79 percentage to 0-100 (harder and easier than you think)
    uint8_t text[]="Percentage:";
    LCD_writeText(0, &text, sizeof(text)-1);  //We don't want to output null
    LCD_writeDec(sizeof(text)-1, percentage*125/100, 3);
    
    secondLine[percentage/5]=percentage%5; //The magical line of code
    
    LCD_writeText( LCD_line2|0, secondLine, 16); //output secondLine to 2nd line
  
  }//While-END
}//--main 

/*
*/
