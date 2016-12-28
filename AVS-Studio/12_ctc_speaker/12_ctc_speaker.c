#include<avr/io.h>
#include<util/delay.h>
void main()
{
DDRB=0xff;    //spesker output
TCCR0=0x19;   //CTC Mode for speaker
while(1)
{
OCR0=59;_delay_ms(500);  //sa
OCR0=52;_delay_ms(500);  //re
OCR0=56;_delay_ms(500);  //ga
OCR0=46;_delay_ms(500);  //ma
OCR0=44;_delay_ms(500);  //pa
OCR0=38;_delay_ms(500);  //dha
OCR0=30;_delay_ms(500);  //ni
OCR0=28;_delay_ms(500);  //se

for(int i=0;i<=255;i++)
{
OCR0=i;_delay_ms(2);           //OCR0 is connected to PB3
}
_delay_ms(500);
for(int i=255;i>=0;i--)
{
OCR0=i;_delay_ms(2);
}
}
}
