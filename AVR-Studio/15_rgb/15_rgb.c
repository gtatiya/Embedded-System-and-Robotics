#include<avr/io.h>
#include<util/delay.h>

int main()
{
DDRD=0xff;  //RGB output
DDRB=0xff;  //RGB output

DDRA=0x00;  //keypad
PORTA=0x0f;

while(1)
{
PORTB=0x00;
PORTD=0x00;
if((PINA&0b00000001)==0){PORTD=0b00010000;while((PINA&0b00000001)==0);_delay_ms(10);}//red
if((PINA&0b00000010)==0){PORTD=0b00100000;while((PINA&0b00000010)==0);_delay_ms(10);}//green
if((PINA&0b00000100)==0){PORTB=0b00001000;while((PINA&0b00000100)==0);_delay_ms(10);}//blue
if((PINA&0b00001000)==0){PORTD=0b00100000;PORTB=0b00001000;while((PINA&0b00001000)==0);_delay_ms(10);}//green+blue

}


}
//connect RGB to CN10 ,common pin to 3rd base
