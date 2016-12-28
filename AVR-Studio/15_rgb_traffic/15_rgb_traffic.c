#include<avr/io.h>
#include<util/delay.h>

int main()
{
DDRB=0xff;//connect RGB to PB0-3 in which PB2 is common



while(1)
{
PORTB=0b00001010;_delay_ms(2000);//orange
PORTB=0b00001000;_delay_ms(5000);//red
PORTB=0b00000010;_delay_ms(5000);//green

}
}
