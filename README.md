# Juno V4 - A Ultimate AVR MCU Development Board
### LCD ADC Communication SPI UART I2C - new Bootloader AVR109 Butterfly CH340g

Juno V4 doesn't look much from the surface with ordinary components, but it's created with extra-ordinary attention to details with expertly draw copper traces that ensure communication via those channels are stable and bug free. The main thing that V4 does is communication via the 3 hardware serial interface: SPI, UART and I2C; The LCD is also a type of half parallel and half serial interface that with the bits exchanged, magic happens. The LCD is powered by extra-ordinary software controlled contrast and backlit brightness level, and a very light weight and high quality library. 

![JunoV4](https://github.com/flyandancexo/Juno-V4/assets/66555404/3377e90b-008e-496b-9c92-183e70125ebf)

### LCD Functions:

```
//Low Level functions
void LCD_COM( uint8_t comm);      //Write Command
void LCD_RAM( uint8_t data );     //Write to SRAM
uint8_t LCD_Read( void );         //Read Data
uint8_t LCD_Busy( void );         //LCD is busy now (0x80 == busy)
#define LCD_Wait() while ( LCD_Busy()&0x80 )  //Macro to wait 40us-1.64ms

//Initialization and LCD control
void LCD_init_4bitMode( void );  //4-bit, 2-line, 5x8, Address++, Display-ON
void LCD_Contrast( uint8_t );
void LCD_Backlight( uint8_t );

//Write text to address
void LCD_writeText( uint8_t add, char *text, uint8_t length );

//Hex and Dec number write 
void LCD_writeHex( uint8_t add, uint16_t hex, uint8_t length ); //Max:0xFFFF
void LCD_writeDec( uint8_t add, uint16_t num, uint8_t length ); //Max:65535

//Create up to 8 new characters
void LCD_LoadNewChar( uint8_t *Newchar, uint8_t add );      //From SRAM
void LCD_LoadNewCharFlash( uint8_t *Newchar, uint8_t add ); //From Flash
```


### LCD Example 1 - Write text to LCD:
```
//  text    data     bss     dec     hex filename
//  1120      32       0    1152     480 Juno_AVR.elf
   
#include "V4DEV.h"
int main(void){
  LCD_init_4bitMode();

  LCD_writeText( firstline|0, "Hello", 5);
  LCD_writeText( firstline|5, " World", 6); //world + space == 6 char
  LCD_writeText( secondline|0, "Juno V4 2024 FD!!", 16);
}//--main 
```
![LCDeA](https://github.com/flyandancexo/Juno-V4/assets/66555404/2564e1cf-26f2-42cd-9e1d-02ee8c0a552f)



### LCD Example 2: Write Decimal and Hexadecimal to LCD
```
//   text    data     bss     dec     hex filename
//   1140      26       0    1166     48e Juno_AVR.elf

#include "V4DEV.h"
int main(void){
  LCD_init_4bitMode();

  LCD_writeText( firstline|0, "X2 Write Numbers", 16);
  LCD_writeText( secondline|0, "H:0x", 4);
  LCD_writeHex( secondline|4, 0xABCD, 4 ); //Max:0xFFFF
  
  LCD_writeText( secondline|9, "#:", 2);
  LCD_writeDec( secondline|11, 12345, 5 );  //Max:65535
  
}//--main 
```
![X2](https://github.com/flyandancexo/Juno-V4/assets/66555404/46746731-ed82-4e64-a998-24320f7851b8)



### LCD Example 3: Create Custom Characters from Flash Memory
```
//   text    data     bss     dec     hex filename
//   1222      18       0    1240     4d8 Juno_AVR.elf

#include "V4DEV.h"

//Create up to 8 characters in Flash: Their addresses are from 0-7
const PROGMEM uint8_t CustomChar[8][8]={
  { 0x1f, 0x1e, 0x1c, 0x18, 0x10, 0x0, 0x0, 0x0 }    //angle arrow left
, { 0, 0x4, 0xe, 0x1f, 0x15, 0x4, 0x4, 0 }           //Up Arrow
, { 0x0, 0x4, 0xe, 0x1f, 0x0, 0xe, 0xe, 0x0 }        //Big Up Arrow
, { 0x0, 0xa, 0x15, 0x15, 0x11, 0xa, 0x4, 0x0 }      //Heart
, { 0x0, 0xa, 0x15, 0xa, 0xa, 0x15, 0xa, 0x0 }       //sprinkle
, { 0x0, 0x4, 0xa, 0x11, 0x11, 0xa, 0x4, 0x0 }       //Diamond
, { 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f } //Full
, { 0x1f, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x1f } //Rectangle
//, { 0x1f, 0xf, 0x7, 0x3, 0x1, 0x0, 0x0, 0x0 }      //angle arrow right
};  

#define CC_BIG_ARROW 2

int main(void){
  LCD_init_4bitMode();
  
  //Load 8 Custom Characters from Flash to LCD
  for( uint8_t i=0; i<8; i++ ){
    LCD_LoadNewCharFlash( &(CustomChar[i]), i);
  }
  
  LCD_writeText( firstline|0, "X3 Custom Chars!", 16);

  LCD_COM( setADD|secondline|0 ); //set LCD RAM Address to second line + 0
  for( uint8_t i=0; i<8; i++ ){
    LCD_RAM(i);                   //Write 8 custom characters to second line
  }

  LCD_COM( setADD|secondline|15 ); //set LCD RAM Address to second line + 15
  LCD_RAM(CC_BIG_ARROW);           //Write CC_BIG_ARROW to last space on 2nd line
}//--main 
```
![X3](https://github.com/flyandancexo/Juno-V4/assets/66555404/b86c99cb-9c4e-4a06-ae33-f32080ff456f)



### LCD Example  4: Create Custom Characters from SRAM Memory
```
//   text    data     bss     dec     hex filename
//   1158      82       0    1240     4d8 Juno_AVR.elf

#include "V4DEV.h"

//Create up to 8 characters in SRAM: Their addresses are from 0-7
uint8_t CustomChar[8][8]={
  { 0x1f, 0x1e, 0x1c, 0x18, 0x10, 0x0, 0x0, 0x0 }    //angle arrow left
, { 0, 0x4, 0xe, 0x1f, 0x15, 0x4, 0x4, 0 }           //Up Arrow
, { 0x0, 0x4, 0xe, 0x1f, 0x0, 0xe, 0xe, 0x0 }        //Big Up Arrow
, { 0x0, 0xa, 0x15, 0x15, 0x11, 0xa, 0x4, 0x0 }      //Heart
, { 0x0, 0xa, 0x15, 0xa, 0xa, 0x15, 0xa, 0x0 }       //sprinkle
, { 0x0, 0x4, 0xa, 0x11, 0x11, 0xa, 0x4, 0x0 }       //Diamond
, { 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f } //Full
, { 0x1f, 0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x1f } //Rectangle
//, { 0x1f, 0xf, 0x7, 0x3, 0x1, 0x0, 0x0, 0x0 }      //angle arrow right
};
#define CC_BIG_ARROW 2

int main(void){
  LCD_init_4bitMode();
  
  //Load 8 Custom Characters from SRAM to LCD
  for( uint8_t i=0; i<8; i++ ){
    LCD_LoadNewChar( &(CustomChar[i]), i);
  }
  
  LCD_writeText( firstline|0, "X4 CChars <- RAM", 16);

  LCD_COM( setADD|secondline|0 ); //set LCD RAM Address to second line + 0
  for( uint8_t i=0; i<8; i++ ){
    LCD_RAM(i);                   //Write 8 custom characters to second line
  }

  LCD_COM( setADD|secondline|15 ); //set LCD RAM Address to second line + 15
  LCD_RAM(CC_BIG_ARROW);           //Write CC_BIG_ARROW to last space on 2nd line
}//--main 
```
![X4](https://github.com/flyandancexo/Juno-V4/assets/66555404/cf0ddad9-b248-4455-bc73-195e8ad5df6c)



### LCD Example :
```
```
//add photo x5




ADC:

Bootloader:  

To support the creation of more quality project, do donate whatever amount that you are comfortable with.

[![paypal](https://www.paypalobjects.com/en_US/i/btn/btn_donateCC_LG.gif)](https://paypal.me/flyandance?country.x=US&locale.x=en_US)

