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
  PORTB=0b10000111;
  PORTD=0b01000100;
  }
  _delay_ms(20);
  
  }
