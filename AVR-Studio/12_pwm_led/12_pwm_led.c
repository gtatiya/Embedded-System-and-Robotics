#include<avr/io.h>
#include<util/delay.h>

int main()
{  
DDRB=0xff;
TCCR0=0x61;   //PWM Mode is used for LED
while(1)
{
for(int i=0;i<=255;i++)
{
OCR0=i;_delay_ms(2);        //OCR0 is connected to BP3 LED
}
_delay_ms(1000);
for(int i=255;i>=0;i--)
{
OCR0=i;_delay_ms(2);
}
}
return 0;
}


