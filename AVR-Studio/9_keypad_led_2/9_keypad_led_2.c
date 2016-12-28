#include<avr/io.h>
#include<util/delay.h>
int main()
{
DDRA=0x00;
DDRD=0x0f;
DDRB=0xff;
PORTA=0x0f;

while(1)
{
PORTD=0b00001110;

if ((PINA&0b00000001)==0){PORTB=0x00;}
if ((PINA&0b00000010)==0){PORTB=0x01;}
if ((PINA&0b00000100)==0){PORTB=0x0f;}
if ((PINA&0b00001000)==0){PORTB=0x7f;}
 
}
return 0;
}
