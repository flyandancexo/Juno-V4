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
uint8_t LCD_HexWrite( uint8_t add, uint16_t hex, uint8_t length );
uint8_t LCD_DecWrite( uint8_t add, uint16_t num, uint8_t length );

//Create up to 8 new characters
void LCD_LoadNewChar( uint8_t *Newchar, uint8_t add );      //From SRAM
void LCD_LoadNewCharFlash( uint8_t *Newchar, uint8_t add ); //From Flash
```

### LCD Example A:
```
//  text    data     bss     dec     hex filename
//  1120      32       0    1152     480 Juno_AVR.elf
   
#include "V4DEV.h"
int main(void){
  LCD_init_4bitMode();

  LCD_writeText( firstline|0, "Hello", 5);
  LCD_writeText( firstline|5, " World", 6); //world + space == 6 
  LCD_writeText( secondline|0, "Juno V4 2024 FD!!", 16);
}//--main 
```
![LCDeA](https://github.com/flyandancexo/Juno-V4/assets/66555404/2564e1cf-26f2-42cd-9e1d-02ee8c0a552f)

```
```

```
```

```
```

ADC:

Bootloader:  

To support the creation of more quality project, do donate whatever amount that you are comfortable with.

[![paypal](https://www.paypalobjects.com/en_US/i/btn/btn_donateCC_LG.gif)](https://paypal.me/flyandance?country.x=US&locale.x=en_US)

