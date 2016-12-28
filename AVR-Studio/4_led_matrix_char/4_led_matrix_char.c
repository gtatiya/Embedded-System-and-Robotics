#include<avr/io.h>
#include<util/delay.h>
int main()
{
DDRD=0xff;
DDRB=0xff;

  {
  PORTB=0b01111011;
  PORTD=0b00111111;
  }
  _delay_ms(20);
  {
  PORTB=0b11001111;
  PORTD=0b10000000;
  }
  _delay_ms(20);
  {
   PORTB=0b10110111;
   PORTD=0b01000000;
  }
  _delay_ms(20);
  {
   PORTB=0b00000011;
   PORTD=0b00001000;
  }
  _delay_ms(10);
  }
