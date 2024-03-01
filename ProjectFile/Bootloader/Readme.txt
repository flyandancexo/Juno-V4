## Juno Bootloader (FDxboot):

A world's fastest bootloader has been developed for V4 that is very loosely based on AVR109, and different variants of bootloaders have been compiled for the same board. New code can be uploaded to board using the following command lines.

Note: The bootloader is still in beta phase, but its upload speed is the fastest already. EEPROM is not supported yet, and it's a 1k-size bootloader. 

//Bootloader at 1Mbps (default pre-loaded bootloader)
avrdude.exe -c avr109 -p m88 -b 1000000 -P COM3 -U flash:w:"hexFile.hex":i -v

//Bootloader at 500kbps (In cause 1Mbps is not stable enough)
avrdude.exe -c avr109 -p m88 -b 500000 -P COM3 -U flash:w:"hexFile.hex":i -v
