#include<avr/io.h>
#include<util/delay.h>

void trans(int);   //Transmission w.r.t controller
int rec();         //receive w.r.t. controller

int main()
{
UCSRB=0x18;
UCSRC=0x86;

UBRRL=51;
DDRB=0xff;
while(1)
{
int x=rec();  //receive from PC

if(x==56){PORTB=0b00001001;} //ascii value of 8 is 56 //press 8 for forward
if(x==52){PORTB=0b00001000;} //ascii value of 4 is 52 //press 4 for left
if(x==54){PORTB=0b00000001;} //ascii value of 6 is 54 //press 6 for right
if(x==50){PORTB=0b00000110;} //ascii value of 2 is 50 //press 2 for backward
if(x==53){PORTB=0b00000000;} //ascii value of 5 is 53 //press 0 to stop
}

}


void trans(int i)
{while((UCSRA&0x20)==0); UDR=i;}

int rec()
{while((UCSRA&0x80)==0); return (UDR);}
