#include<avr/io.h>
#include<util/delay.h>

#include<avr/interrupt.h>

void main ()
{
sei();        /* set global interrupt enable */
GICR|=0x40;  //for interrupt INT0
DDRD=0x00;   //INT0 pin is at PD2
PORTD=0xff;  //pull up ON to detect interrupt
DDRB=0xff;
PORTB=0x00;

while(1);  //to keep Controller busy
}

ISR(INT0_vect)   //when interrupt is called PD2 is set to 0
{
//_delay_ms(50);
PORTB=~PORTB;

}
