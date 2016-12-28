#include<avr/io.h>
#include<util/delay.h>
#include<avr/eeprom.h>
void main()
{
/*char c[10];
eeprom_write_block("guru",0x000000,10);
eeprom_read_block(c,0x000000,10);*/

char n[10];
eeprom_write_block("1234",0x000000,10);
eeprom_read_block(n,0x000000,10);
}
