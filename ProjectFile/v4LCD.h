/*###############################################################
# Advanced 2x16 LCD Code - Declaration File 
# Note: 4-bit LCD driver with Write and Read Enable

//LCD Hardware Connections:
//LCD: VC(VO-D5-[OC0B]) DC(RS-D4) R/W(D3) LCK(E-D7) LED(D6-[OC0A]-Inverted)
//4-bit Data: DB4:DB7 --> C0:C3

// 0123456789ABCEDF
// Juno V4 - Serial 
// COM ADC LCD DEV!
=================================================================
# An Advanced MCU Project - 2024 © Flyandance
################################################################*/

#ifndef V4LCD_h
#define V4LCD_h

//Macro to use to see address (these codes should be memorized)
#define LCD_line1 0x00     //First line starts at address 0x00
#define LCD_line2 0x40     //Second line starts at address 0x40
#define LCD_setADD 0x80    //0x80 is the set address code

//default mode enabled - (encoded) <<<---------
#define LCD_functionMode 0x28 //4-bit, 2-line, 5x8
#define LCD_entryMode 0x06    //Address Increment, No-shift
#define LCD_displayON 0x0C    //Display-ON
 
//There are 4 main commands: ( These codes are not used in this library )
//Function  command
#define LCD_function 0x20            //(1<<5)
#define LCD_functionModeA 0x38       //8-bit, 2-line, 5x8
#define LCD_functionModeB 0x28       //4-bit, 2-line, 5x8
#define LCD_functionModeC 0x20       //4-bit, 1-line, 5x8
#define LCD_functionModeD 0x30       //8-bit, 1-line, 5x8

//Cursor  command
#define LCD_cursor 0x10              //(1<<4)
#define LCD_cursorDSR 0x1C	         //Display shift Right
#define LCD_cursorDSL 0x18	         //Display shift Left
#define LCD_cursorCMR 0x14	         //Cursor move right
#define LCD_cursorCML 0x10	         //Cursor move left

//Display command
#define LCD_display 0x08             //(1<<3)
#define LCD_displayOFF 0x08          //Display-OFF
#define LCD_displayONwBlinker 0x0D   //Display-OFF
#define LCD_displayONwCursor 0x0E    //Display-OFF

//Entry command
#define LCD_entry 0x04               //(1<<2)
#define LCD_entryAIDS 0x07	         //Address Increment w/ display shift
#define LCD_entryAINS 0x06	         //Address Increment w/o display shift
#define LCD_entryADDS 0x05	         //Address Decrement w/ display shift
#define LCD_entryADNS 0x04	         //Address Decrement w/o display shift

//And 2 last commands
#define LCD_returnHome 0x02    //(1<<1) (1.64ms) returns the display and cursor to address 0
#define LCD_clearDisplay 0x01  //(1<<0) (1.64ms) is the Home + with 80-byte Output SRAM written a space char

//#################################################################################
//### Core LCD function - 4-bit with Write and Read capacity
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
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

void delay50us(void);

#endif //V4_LCD-END
