#include<avr/io.h>
#include<util/delay.h>

int main()
{
DDRD=0x0f;
{
PORTD=0b00000001;
PORTD=0b00000010;
PORTD=0b00000100;
PORTD=0b00001000;
}
}
