#include<avr/io.h>
#include<util/delay.h>

int main()
{
DDRB=0xff;//connect RGB to PB0-3 in which PB2 is common

DDRA=0xf0;  //keypad
PORTA=0x0f;

while(1)
{
PORTA=0b01111111;_delay_ms(50);
{
if((PINA&0b00000001)==0){PORTB=0b00001000;while((PINA&0b00000001)==0);_delay_ms(50);}//red
if((PINA&0b00000010)==0){PORTB=0b00000010;while((PINA&0b00000010)==0);_delay_ms(50);}//green
if((PINA&0b00000100)==0){PORTB=0b00000001;while((PINA&0b00000100)==0);_delay_ms(50);}//blue
if((PINA&0b00001000)==0){PORTB=0b00001010;while((PINA&0b00001000)==0);_delay_ms(50);}//red+green=orange
}
//PORTB=0x00;_delay_ms(50);
PORTA=0b10111111;_delay_ms(50);
{
if((PINA&0b00000001)==0){PORTB=0b00001001;while((PINA&0b00000001)==0);_delay_ms(50);}//red+blue=pink
if((PINA&0b00000010)==0){PORTB=0b00000011;while((PINA&0b00000010)==0);_delay_ms(50);}//green+blue=light blue
if((PINA&0b00000100)==0){PORTB=0b00001011;while((PINA&0b00000100)==0);_delay_ms(50);}//all=white
if((PINA&0b00001000)==0){PORTB=0b00001010;while((PINA&0b00001000)==0);_delay_ms(50);}//red+green=orange
}

PORTB=0x00;_delay_ms(50);


}


}
