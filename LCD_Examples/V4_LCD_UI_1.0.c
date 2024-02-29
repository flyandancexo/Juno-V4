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
//   2010      82       6    2098     832 Juno_AVR.elf
   
#include "V4DEV.h"

#define NOPOS 6 //number of positions
#define POSdiv (256/NOPOS+1)

int main(void){
V4_initi();

uint8_t LCDCustomChar[8]={ 0x0, 0x4, 0xe, 0x1f, 0x0, 0xe, 0xe, 0x0 };//Big Up Arrow
#define BIG_UPARROW 0
LCD_LoadNewChar (LCDCustomChar, BIG_UPARROW);

uint8_t menu=0;
char subMenu[6][10]={
"Brightnes ",
"Contrast  ",
"Var ACE   ",
"Var Beth  ",
"Var Carol ",
"Var Dick  "
};
uint8_t var[4]={11, 22, 33, 44};
uint8_t Apos=0;
  while(1){
  buttonScan();
  
  Apos=adcPOT/POSdiv;
  LCD_COM( (0x80|0x40)+10+Apos );
  LCD_RAM( BIG_UPARROW );
  
  //Write space above and below the arrow position 
  LCD_COM( (0x80|0x40)+9+Apos );
  LCD_RAM( ' ' );
  LCD_COM( (0x80|0x40)+11+Apos );
  LCD_RAM( ' ' );  
  
  LCD_writeText( 0, "V>", 2 );
  LCD_writeText( 10, "BCABCD", 16 );
  LCD_writeText( 0x40, subMenu[Apos], 10 );
  
  switch (Apos){
    case 0:
      LCD_writeDec( 3, LCD_BL, 3 );
      if(bra){ LCD_BL-=10;}
      if(brb){ LCD_BL+=10;}
    break;
    
    case 1:
      LCD_writeDec( 3, LCD_CO, 3 );
      if(bra){ LCD_CO-=5;}
      if(brb){ LCD_CO+=5;}
      if(LCD_CO>130) {LCD_CO=0;}
    break;
    
    case 2:
    case 3:
    case 4:
    case 5:
      LCD_writeDec( 3, var[Apos-2], 3 );
      LCD_writeDec( 3, var[Apos-2], 3 );
      if(bra){ var[Apos-2]-=1;}
      if(brb){ var[Apos-2]+=1;}
    break;
  }

  }//While-END
}//--main 

/*
// 0123456789ABCEDF
// FD LCD UI BCABCD
// Brightness
// Contrast  
// Var A:
// Var B:
// Var C:
// Var D:
// 0123456789ABCEDF
*/
