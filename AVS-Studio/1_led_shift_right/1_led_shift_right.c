#include<avr/io.h>
#include<util/delay.h>
int main()
{
DDRD=0xff;
while(1)
{
PORTD=0x80;
_delay_ms(500);
for(int i=0;i<7;i++)
{
PORTD=PORTD>>1;
_delay_ms(500);
}}
return 0;
}
