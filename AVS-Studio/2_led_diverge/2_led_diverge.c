#include<avr/io.h>
#include<util/delay.h>
int main()
{
DDRD=0xff;
while(1)
{
PORTD=0x18;
_delay_ms(500);
int a=0x10,b=0x08;
for(int i=0;i<4;i++)
{
PORTD=a+b;
a=a<<1;
b=b>>1;
_delay_ms(500);
}}
return 0;
}
