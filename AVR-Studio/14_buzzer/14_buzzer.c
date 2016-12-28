#include<avr/io.h>
#include<util/delay.h>


void main()
{
DDRA=0xff;

DDRB=0xff; //to check


while(1)
{
PORTA=0b10000000;         //PA7 is for BUZZER
_delay_ms(250);
PORTB=PORTA;

PORTA=0b00000000;         //PA7 is for BUZZER
_delay_ms(250);
PORTB=PORTA;
}

}
