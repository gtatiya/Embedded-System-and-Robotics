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
int a=PINA&0b00001111;

if (a==0b00001110)
 {PORTB=0x01;}
if (a==0b00001101)
 {PORTB=0x02;}
if (a==0b00001011)
 {PORTB=0x04;}
if (a==0b00000111)
 {PORTB=0x08;}
 
 }
return 0;
}
