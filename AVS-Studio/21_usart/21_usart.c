#include<avr/io.h>
#include<util/delay.h>

void trans(int);   //Transmission w.r.t controller
int rec();         //receive w.r.t. controller

int main()
{
UCSRB=0x18;
UCSRC=0x86;

UBRRL=51;
while(1)
{
int x =rec();  //receive from PC
trans (x);     //transmit to PC
}

}


void trans(int i)
{while((UCSRA&0x20)==0); UDR=i;}

int rec()
{while((UCSRA&0x80)==0); return (UDR);}
