#include<avr/io.h>
#include<util/delay.h>
int main()
{
DDRA=0x00;
DDRD=0xff;

PINA=0b00000001;    // manually sensor assigned value

int a=PINA&0b00000001;

if (a==0b00000001)
{
PORTD=0b11111111;
}
else
{
PORTD=0x00;
}
return 0;
}
