#include<avr/io.h>
#include<util/delay.h>

int main()
{
DDRB=0x0f;  //motor output, OCR0 is connected to PB3
DDRA=0x00;  // sensor input

TCCR0=0x19;   //CTC Mode for speaker

while(1)
{
int a=PINA&0b00000001;  //ANDing to remove NOISE //we want only last 1 bits to giving our command to move
if (a==0b00000001)     {OCR0=50;_delay_ms(500);}
if (a==0b00000000)     {OCR0=255;_delay_ms(500);} 
}
return 0;

}
/*
===================Connections================

connect sensor to PA0*/
