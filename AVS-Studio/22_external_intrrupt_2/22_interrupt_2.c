#include<avr/io.h>
#include<util/delay.h>

#include<avr/interrupt.h>

void main ()
{
sei();
GICR|=0x80;  //for interrupt INT1
DDRD=0x00;   //INT0 pin is at PD3
PORTD=0xff;  //pull up ON to detect interrupt
DDRB=0xff;
PORTB=0x00;

while(1);   //to keep Controller busy
}

ISR(INT1_vect)   //when interrupt is called PD3 is set to 0
{
//_delay_ms(50);
PORTB=~PORTB;

}
