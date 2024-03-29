# Juno V4 - A Ultimate AVR MCU Development Board
### LCD ADC Communication SPI UART I2C - new Bootloader AVR109 Butterfly CH340g

Juno V4 doesn't look much from the surface, but it's been crafted with extra-ordinary attention to details with expertly draw copper traces that ensure communications via those channels are stable and bug free. The main thing that V4 does is communication via the 3 hardware serial interface: SPI, UART and I2C.

![JunoV4](https://github.com/flyandancexo/Juno-V4/assets/66555404/3377e90b-008e-496b-9c92-183e70125ebf)

The LCD is ordinary, but it's connected in an extra-ordinary way and is powered by extra-ordinary driver. This enables the exploration of the MCU with ease and fun. The LCD is also a type of half parallel, half serial, and half duplex interface that just by coding it, can improve one's low-level and high-level programming skill. The V4 LCD supports both read and write, and the control of LCD contrast and brightness by software. A very light weight and high quality library has been created for it.

4 ADC buttons, A potentiometer and a physical switch are included as a way of navigating the board, and as a way to demonstrate high quality and high accurate voltage readings via Analog to Digital Converter. There are also a big RGB LED and a tiny debug LED and one reset button. Another simple and high quality button and ADC library has been provided for interfacing these hardware stress free.

The infamous CH340g is actually a seriously solid serial chip that connects the MCU to a host computer. A world's fastest bootloader has also been developed for this board, and it has been preloaded on the chip. New code can either be uploaded via the USB port or a 6-pin ICSP header. Finally, the design of the board is of a minimalist and the size of a credit card, yet, it has everything needed to develop advanced MCU application, and more.

![Juno_V4_K](https://github.com/flyandancexo/Juno-V4/assets/66555404/f0530bd6-88cd-44ca-8142-d39c79ed8ff0)

## Juno V4 - LCD Hardware and LCD Software Features: 
- 4-bit mode - 9 I/O pins from MCU
- Support Read and Write LCD operations
- Fastest LCD operation using busy polling instead of a delay timer
- LCD Contrast and LCD backlit brightness are controlled by software
- High quality and light weight code that supports write text, decimal, hexadecimal, and more
- 8 custom characters creation either from SRAM or Flash
- 7 simple examples to demonstrate how easy it's to control a LCD
- More Advanced examples are provided plus a simple LCD UI
- This is the best LCD library in the point of view of a good development board and for the above features

### LCD Functions Overview:

```
//###########################################
// Juno V4 Functions Overview: 
//###########################################

V4_initi();          //V4 initialization: LCD, ADC and button
LCD_init_4bitMode(); //LCD initialization, no ADC and button
buttonScan();        //Scan 2 ADC channels and polling for button event
LCD_CO=110;          //LCD contrast 1-110;
LCD_BL=20;           //LCD brightness level 0-255;

//LCD command and data 
void LCD_COM( uint8_t comm);      //Write Command
void LCD_RAM( uint8_t data );     //Write to SRAM

//Write custom character and text to address (valid address 0-0x80) (0x0-0x15) (0x40)
void LCD_writeCC ( uint8_t add, uint8_t cc );
void LCD_writeTextFlash( uint8_t add, char *text, uint8_t len );
void LCD_writeText( uint8_t add, char *text, uint8_t length );

//write Hex and Dec number
void LCD_writeHex( uint8_t add, uint16_t hex, uint8_t length ); //Max:0xFFFF
void LCD_writeDec( uint8_t add, uint16_t num, uint8_t length ); //Max:65535

//Create up to 8 new characters - (Valid address 0-7)
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

  LCD_writeText( LCD_line1|0, "Hello", 5);
  LCD_writeText( LCD_line1|5, " World", 6); //world + space == 6 char
  LCD_writeText( LCD_line2|0, "Juno V4 2024 FD!!", 16);
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

  LCD_writeText( LCD_line1|0, "X2 Write Numbers", 16);
  LCD_writeText( LCD_line2|0, "H:0x", 4);
  LCD_writeHex( LCD_line2|4, 0xABCD, 4 ); //Max:0xFFFF
  
  LCD_writeText( LCD_line2|9, "#:", 2);
  LCD_writeDec( LCD_line2|11, 12345, 5 );  //Max:65535
  
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
  
  LCD_writeText( LCD_line1|0, "X3 Custom Chars!", 16);

  LCD_COM( LCD_setADD|LCD_line2|0 ); //set LCD RAM Address to second line + 0
  for( uint8_t i=0; i<8; i++ ){
    LCD_RAM(i);                   //Write 8 custom characters to second line
  }

  LCD_COM( LCD_setADD|LCD_line2|15 ); //set LCD RAM Address to second line + 15
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
  
  LCD_writeText( LCD_line1|0, "X4 CChars <- RAM", 16);

  LCD_COM( LCD_setADD|LCD_line2|0 ); //set LCD RAM Address to second line + 0
  for( uint8_t i=0; i<8; i++ ){
    LCD_RAM(i);                   //Write 8 custom characters to second line
  }

  LCD_COM( LCD_setADD|LCD_line2|15 ); //set LCD RAM Address to second line + 15
  LCD_RAM(CC_BIG_ARROW);           //Write CC_BIG_ARROW to last space on 2nd line
}//--main 
```
![X4](https://github.com/flyandancexo/Juno-V4/assets/66555404/cf0ddad9-b248-4455-bc73-195e8ad5df6c)



### LCD Example 5: To put Everything together
```
//   text    data     bss     dec     hex filename
//   1262      26       0    1288     508 Juno_AVR.elf

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
  

  _delay_ms(1000);
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
```
![X5](https://github.com/flyandancexo/Juno-V4/assets/66555404/f14cc855-500b-46ac-9e3e-5d220c1e10b5)




### LCD Example 6: Percentage Bar
```
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
```
![X6](https://github.com/flyandancexo/Juno-V4/assets/66555404/49567047-679d-4ec1-8711-7ab12a0323de)


### LCD Example 7: LCD Software controlled Contrast
```
//   text    data     bss     dec     hex filename
//   1404      14       0    1418     58a Juno_AVR.elf
   
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

uint16_t LCD_contrast=0; 
uint8_t secondLine[16];

  while(1){
  
    _delay_ms(100);
    if( LCD_contrast == 0 ) {
      for( uint8_t i=0; i<16; i++ ){secondLine[i]=' ';} //clear second line
    }
    LCD_contrast++; // 16*5=80 100/80=1.25   80*125/100=100
    if( LCD_contrast==80 ){
      LCD_contrast=0; 
    }
    
    //Convert 0-79 to 0-110 ( 110/80=1.375  80*137/100=109 )
    LCD_Contrast(LCD_contrast*137/100); //0-110
    
    uint8_t text[]="LCD Contrast:";
    LCD_writeText(0, &text, sizeof(text)-1);
    LCD_writeDec(sizeof(text)-1, LCD_contrast*125/100, 3);
    
    secondLine[LCD_contrast/5]=LCD_contrast%5; //Magical Line
    LCD_writeText( LCD_line2|0, secondLine, 16); //Output
  
  }//While-END
}//--main 
```
![X7](https://github.com/flyandancexo/Juno-V4/assets/66555404/0dbf6f17-4777-4c1d-ab6d-14c146b3afb2)


## Juno ADC:

The decision to use 2 ADC channels as inputs from 4 buttons and 1 potentiometer is because C6 and C7 can only be used as ADC pins, and these 2 simple hardware can be used to explore ADC in a lower level, and finally they can also be very useful input for development. Getting accurate ADC readings, especially with multiple inputs can be hard, but it's actually extremely easy. The trick is to add a delay after the selected channel has been changed. 

Note: the library does reading back from these 2 channels fine already. To plays with ADC on your own, don't use V4_initi(); Use LCD_init_4bitMode() instead. 

### ADC Example 1: Read 2 ADC Channels at the same time
```
//   text    data     bss     dec     hex filename
//   1206      12       0    1218     4c2 Juno_AVR.elf
   
#include "V4DEV.h"

int main(void){
LCD_init_4bitMode();

//ADC Input, 8-bit mode, Vref=VCC, CPU_clock/4
ADMUX= (1<<REFS0)|(1<<ADLAR)|6; //C6 is the input
ADCSRA= (1<<ADEN)|(1<<ADSC)|(1<<ADATE)|2;  
ADCSRB= 0;  //Free running mode

  while(1){
  LCD_writeText( 0, "Button", 6);
  LCD_writeText( 13, "POT", 3);
  
  // All release   = 5v            [adc value= 255]
  // first button  = 0v            [adc value= 0]
  // second button = 5*1/2=2.5v    [adc value= 255*1/2=127.5]
  // third button  = 5*2/3=3.3v    [adc value= 255*2/3=170]
  // fourth button = 5*3/4=3.7v    [adc value= 255*3/4=191]
  ADMUX= (1<<REFS0)|(1<<ADLAR)|6; //C6 is the input
  _delay_us(100);//Because ADC doesn't convert instantly, we need some delay
  LCD_writeDec( 0x40, ADCH, 3 );

  //POT 0-255
  ADMUX= (1<<REFS0)|(1<<ADLAR)|7; //C7 is the input
  _delay_us(100);//Because ADC doesn't convert instantly, we need some delay
  LCD_writeDec( 0x40|13, ADCH, 3 );
  
  }//While-END
}//--main 
```
![X8-adc](https://github.com/flyandancexo/Juno-V4/assets/66555404/9029f29a-6864-4d5e-ae6b-4cfdc7383a51)



### ADC Example 2: Using the potentiometer as a navigator
```
//   text    data     bss     dec     hex filename
//   1234      26       0    1260     4ec Juno_AVR.elf
   
#include "V4DEV.h"

int main(void){
LCD_init_4bitMode();
uint8_t LCDCustomChar[8]={ 0x0, 0x4, 0xe, 0x1f, 0x0, 0xe, 0xe, 0x0 };//Big Up Arrow
#define BIG_UPARROW 0

LCD_LoadNewChar (LCDCustomChar, BIG_UPARROW);

//ADC Input, 8-bit mode, Vref=VCC, CPU_clock/4
ADMUX= (1<<REFS0)|(1<<ADLAR)|7; //C7 is the input
ADCSRA= (1<<ADEN)|(1<<ADSC)|(1<<ADATE)|2;  
ADCSRB= 0;  //Free running mode

  LCD_writeText( 0, "LCD Arrow Naviga", 16);
  
  while(1){

  LCD_COM( 0x80|0x40|(ADCH/16) ); // 256/16=16
  LCD_RAM( BIG_UPARROW );
  
  //Write space above and below the arrow position 
  LCD_COM( (0x80|0x40|(ADCH/16))+1 );
  LCD_RAM( ' ' );
  LCD_COM( (0x80|0x40|(ADCH/16))-1 );
  LCD_RAM( ' ' );  
  
  }//While-END
}//--main 
```
![X9-adc_arrow](https://github.com/flyandancexo/Juno-V4/assets/66555404/2e7038a1-a363-4fec-b47e-c781b54e1136)



### ADC Example 3: ADC button Library + ADC potentiometer
```
//   text    data     bss     dec     hex filename
//   1610      26       6    1642     66a Juno_AVR.elf
   
#include "V4DEV.h"

int main(void){
V4_initi();
uint8_t test=123;
  while(1){
  buttonScan();
  LCD_writeText( 0, "Potentiometr", 12 );
  LCD_writeDec( 13, adcPOT, 3 );
  
  LCD_writeText( 0x40, "ADC Button->", 12 );
  LCD_writeDec( 0x40|13, test, 3 );
  
  if(bra){ test++;}
  if(brb){ test--;}
  if(brc){ test=88;}
  if(brd){ test=111;}
  
  }//While-END
}//--main 
```
![X10-adc_button_pot](https://github.com/flyandancexo/Juno-V4/assets/66555404/1a6be02b-55bb-45ba-9caf-744fcb16c95a)



## Juno Bootloader (FDxboot):

A world's fastest bootloader has been developed for V4 that is very loosely based on AVR109, and different variants of bootloaders have been compiled for the same board. New code can be uploaded to board using the following command lines.

Note: The bootloader is still in beta phase, but its upload speed is the fastest already. EEPROM is not supported yet, and it's a 1k-size bootloader. 

```
//Bootloader at 1Mbps (default pre-loaded bootloader)
avrdude.exe -c avr109 -p m88 -b 1000000 -P COM3 -U flash:w:"hexFile.hex":i -v

//Bootloader at 500kbps (In cause 1Mbps is not stable enough)
avrdude.exe -c avr109 -p m88 -b 500000 -P COM3 -U flash:w:"hexFile.hex":i -v
```

or use my IDE-less batch file on windows, 

![V4_upload](https://github.com/flyandancexo/Juno-V4/assets/66555404/fd8f66a3-996a-4c4b-98b5-d1d166f6b9b7)

or anything else of your choice.

To support the creation of more quality project, do donate whatever amount that you are comfortable with.

[![paypal](https://www.paypalobjects.com/en_US/i/btn/btn_donateCC_LG.gif)](https://paypal.me/flyandance?country.x=US&locale.x=en_US)

