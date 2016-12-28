#include<avr/io.h>
#include<util/delay.h>

#include<avr/interrupt.h>
int count=0;

void main ()
{
sei();
DDRB=0xff;
DDRA=0xff;
TCCR0=3;    //increase prescale 1 to 5 to decrease interrupt occurrence
TIMSK=1;
while(1);{PORTA=0xff;}
}

ISR(TIMER0_OVF_vect)
{
count++;
if(count==20)        //just to slow down interruts visibility
{
PORTB=~PORTB;
count=0;
}
}
