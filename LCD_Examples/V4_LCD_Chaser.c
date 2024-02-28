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
//   1232       0       0    1232     4d0 Juno_AVR.elf
   
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

#define CCRA 6
#define CCLA 7

int main(void){
LCD_init_4bitMode();

for( uint8_t i=0; i<8; i++ ){
  LCD_LoadNewCharFlash( &(CustomChar[i]), i );
}

uint8_t LCD_ChaserA=0;
uint8_t LCD_ChaserB=15; 

  while(1){
  
    _delay_ms(100);
    LCD_ChaserA++;
    LCD_ChaserB--;
    if( LCD_ChaserB == 0 ){
      LCD_ChaserA=0;
      LCD_ChaserB=15; 
      LCD_COM(0x01);  //Clear LCD
    }
    
    LCD_COM(0x80|0x40|LCD_ChaserA); //set address second line + LCD_ChaserA
    LCD_RAM( CCRA ); //Write right arrow

    LCD_COM(0x80|0x0|LCD_ChaserB); //set address first line + LCD_ChaserB
    LCD_RAM( CCLA ); //Write right arrow
    
  }//While-END
}//--main 


/*
*/
