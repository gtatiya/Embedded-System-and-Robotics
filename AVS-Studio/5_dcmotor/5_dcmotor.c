#include<avr/io.h>
#include<util/delay.h>

int main()
{
DDRD=0x0f;

{
PORTD=0b00001001;
_delay_ms(2000);
PORTD=0b00000110;
_delay_ms(2000);
PORTD=0b00001000;
_delay_ms(2000);
PORTD=0b00000001;
_delay_ms(2000);
PORTD=0b00000000;
_delay_ms(2000);
}
}
