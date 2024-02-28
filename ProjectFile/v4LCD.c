/*###############################################################
# Advanced 2x16 LCD Code - Implementation File 
# Note: 4-bit LCD driver with Write and Read Enable

Most LCD operations take 40us, except clear display and return home which take 1.63ms;
Read busy address or polling busy flag is the fastest, of which took 1us; 
This library uses busy flag to write to and read from the LCD, 
except the initialization, which requires timed delay between commands;
=================================================================
# An Advanced MCU Project - 2024 © Flyandance
################################################################*/

#include "V4DEV.h"
#include "v4LCD.h"

//#################################################################################
//### 4-bit LCD mode enable 
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void LCD_init_4bitMode ( void ){
//LCD Hardware Connections:
//LCD: VC(VO-D5-[OC0B]) DC(RS-D4) R/W(D3) LCK(E-D7) LED(D6-[OC0A]-Inverted)
//4-bit Data: DB4:DB7 --> C0:C3
DDRD|=(1<<7)|(1<<6)|(1<<5)|(1<<4)|(1<<3);

//Hardware 2 PWM channels control LCD contrast and LCD backlight
TCCR0A|=(1<<WGM00)|(1<<WGM01)|(1<<COM0B1)|(1<<COM0A1)|(1<<COM0A0); 
TCCR0B|=2; //Clock/64  (0:Off 1-5:[1,8,64,256,1024])
OCR0B=50;  //Contrast
OCR0A=15;  //LCD backlit

//4 Data IO C3:0 -- OUTPUT
DDRC|=0x0f;
PORTC&=~0x0f;

//Command and Write operation - Enter 4-bit mode here
PORTD &= ~((1<<4)|(1<<3)); //DC & R/W LOW

PORTC&=~0x0f;
PORTC|=0x3;
PORTD |= (1<<7);   //High to LOW
PORTD &= ~(1<<7);  //Failing edge for write
delay50us();       //Wait 50us

PORTC&=~0x0f;
PORTC|=0x3;
PORTD |= (1<<7);   //High to LOW
PORTD &= ~(1<<7);  //Failing edge for write
delay50us();       //Wait 50us

PORTC&=~0x0f;
PORTC|=0x3;
PORTD |= (1<<7);   //High to LOW
PORTD &= ~(1<<7);  //Failing edge for write
delay50us();       //Wait 50us

PORTC&=~0x0f;
PORTC|=0x2;
PORTD |= (1<<7);   //High to LOW
PORTD &= ~(1<<7);  //Failing edge for write
delay50us();       //Wait 50us

//Default LCD settings
LCD_COM(0x28);  //4-bit, 2-line, 5x8
LCD_COM(0x06);  //Address Increment, No-shift
LCD_COM(0x0C);  //Display-ON
//LCD_COM(0x02);  //Home command -- (1.64ms)
LCD_COM(0x01);  //clear command -- (1.64ms)
}

//#################################################################################
//### 4-bit Write Command
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void LCD_COM ( uint8_t command ){
  PORTD &= ~((1<<4)|(1<<3)); //DC & R/W LOW
  
  //4 Data IO C3:0 -- OUTPUT
  DDRC|=0x0f;
  PORTC&=~0x0f;
  //PORTD &= ~(1<<7);   //Failing edge for write
  
  PORTC&=~0x0f;
  PORTC|=(command>>4)&0x0f; //High nibble first
  PORTD |= (1<<7);          //High to LOW
  PORTD &= ~(1<<7);         //Failing edge for write

  PORTC&=~0x0f;
  PORTC|=(command)&0x0f; //Low nibble next
  PORTD |= (1<<7);   //High to LOW
  PORTD &= ~(1<<7);  //Failing edge for write
  
  while ( LCD_Busy()&0x80 ); //Wait while LCD is busy, normal wait time is 40us
}

//#################################################################################
//### 4-bit Write SRAM
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void LCD_RAM( uint8_t data ){
  PORTD &= ~((1<<4)|(1<<3)); //DC & R/W LOW
  PORTD |= (1<<4);           //DC HIGH = Data
  
  //4 Data IO C3:0 -- OUTPUT
  DDRC|=0x0f;
  PORTC&=~0x0f;
  //PORTD &= ~(1<<7);   //Failing edge for write
  
  PORTC&=~0x0f;
  PORTC|=(data>>4)&0x0f;  //High nibble first
  PORTD |= (1<<7);        //High to LOW
  PORTD &= ~(1<<7);       //Failing edge for write

  PORTC&=~0x0f;
  PORTC|=(data)&0x0f; //Low nibble next
  PORTD |= (1<<7);    //High to LOW
  PORTD &= ~(1<<7);   //Failing edge for write
  
  while ( LCD_Busy()&0x80 ); //Wait while LCD is busy, normal wait time is 40us
}

//#################################################################################
//### 4-bit Read from SRAM
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
uint8_t LCD_Read( void ){
  PORTD |= ((1<<4)|(1<<3)); //DC & R/W --> HIGH
  
  //4 Data IO C3:0 -- Input with pull-up
  uint8_t temp=0;
  DDRC&=~0x0f;
  PORTC|=0x0f;

  PORTD |= (1<<7);         //High to LOW
  PORTD &= ~(1<<7);        //Failing edge for write
  temp|=(0x0f&PINC)<<4;    //read high nibble first

  PORTD |= (1<<7);         //High to LOW
  PORTD &= ~(1<<7);        //Failing edge for write
  temp|=(0x0f&PINC);       //read low nibble next
  
  while ( LCD_Busy()&0x80 ); //Wait while LCD is busy, normal wait time is 40us
  return temp;
}

//#################################################################################
//### 4-bit LCD busy poll
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
uint8_t LCD_Busy( void ){
  PORTD &= ~((1<<4)|(1<<3)); //DC & R/W LOW
  PORTD |= (1<<3);           //R/W=HIGH, DC=LOW (poll)
  
  //4 Data IO C3:0 -- Input with pull-up
  uint8_t temp=0;
  DDRC&=~0x0f;
  PORTC|=0x0f;

  PORTD |= (1<<7);         //High to LOW
  PORTD &= ~(1<<7);        //Failing edge for write
  temp|=(0x0f&PINC)<<4;    //read high nibble first

  PORTD |= (1<<7);         //High to LOW
  PORTD &= ~(1<<7);        //Failing edge for write
  temp|=(0x0f&PINC);       //read low nibble next
  return temp;
}

//#################################################################################
//### Custom new character up to 8 (add: 0-7) from Flash memory - 8 bytes
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void LCD_LoadNewCharFlash( uint8_t *Newchar, uint8_t add ){
  LCD_COM( 0x40|(add*8) );  //Set Char address 0 out of 64
  //write first Custom Character
  for( uint8_t i=0; i<8; i++ ){
    LCD_RAM( pgm_read_byte( &(Newchar[i])) ); 
  }
}

//#################################################################################
//### Custom new character up to 8 (add: 0-7) from SRAM memory - 8 bytes
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void LCD_LoadNewChar( uint8_t *Newchar, uint8_t add ){
  LCD_COM( 0x40|(add*8) );  //Set Char address 0 out of 64
  //write first Custom Character
  for( uint8_t i=0; i<8; i++ ){
    LCD_RAM( Newchar[i] ); 
  }
}

//#################################################################################
//### Write Decimal number to an address location on the LCD with a length option
//### 16-bit unsigned = 65535, so max len is 5 
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void LCD_writeDec( uint8_t add, uint16_t DECnum, uint8_t len){

  uint8_t temp[5];
  temp[4]=DECnum/10000+'0';
  temp[3]=DECnum/1000%10+'0';
  temp[2]=DECnum/100%10+'0';
  temp[1]=DECnum/10%10+'0';
  temp[0]=DECnum%10+'0';

  //Write to line two
  LCD_COM(0x80|add); 
  for( int8_t i=(len-1); i>-1; i-- ){
    LCD_RAM( temp[i] );
  }

}

//#################################################################################
//### Write Hex number to an address location on the LCD - 16-bit Hex, max len is 4
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void LCD_writeHex( uint8_t add, uint16_t hexNum, uint8_t len){

  uint8_t temp[4];
  temp[3]=(hexNum/0x1000)>9 ? (hexNum/0x1000)+'A'-10 : (hexNum/0x1000)+'0';
  temp[2]=(hexNum/0x100%0x10)>9 ? (hexNum/0x100%0x10)+'A'-10 : (hexNum/0x100%0x10)+'0';
  temp[1]=(hexNum/0x10%0x10)>9 ? (hexNum/0x10%0x10)+'A'-10 : (hexNum/0x10%0x10)+'0';
  temp[0]=(hexNum%0x10)>9 ? (hexNum%0x10)+'A'-10 : (hexNum%0x10)+'0' ;

  //Write to line two
  LCD_COM(0x80|add); 
  for( int8_t i=(len-1); i>-1; i-- ){
    LCD_RAM( temp[i] );
  }

}

//#################################################################################
//### Write text to address
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void LCD_writeText( uint8_t add, char *text, uint8_t len ){ 
  LCD_COM(0x80|add); 
  for( uint8_t i=0; i<len; i++ ){
    LCD_RAM( text[i] );
  }
}

//#################################################################################
//### LCD Contrast 10-110 ( default 50 is good )
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void LCD_Contrast( uint8_t contrast ){
  OCR0B=contrast;
}

//#################################################################################
//### LCD's LED brightness level 0-255
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void LCD_Backlight( uint8_t pwm ){
  OCR0A=pwm;
}

//#################################################################################
//### Delay code - It's more efficient to define it as a function here
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void delay50us(void){
  _delay_us(50);
}
