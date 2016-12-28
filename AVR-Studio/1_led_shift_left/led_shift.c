#include<avr/io.h>
#include<util/delay.h>


int main()
{
DDRA=0xff;

while(1)
{
PORTA=0x01;
_delay_ms(500);
for(int i=0;i<7;i++)
{
PORTA=PORTA<<1;
_delay_ms(500);
}}
return 0;
}
