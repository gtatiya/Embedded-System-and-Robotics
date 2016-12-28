#include<avr/io.h>
#include<util/delay.h>

int main()
{
DDRB=0x0f;
DDRA=0x00;

//PINA=0b00000011;  // manually sensor assigned value


while(1)
{
int a=PINA&0b00000011;  //ANDing to remove NOISE //we want only last 2 bits to giving our command to move
if (a==0b00000011)     {PORTB=0b00001001;}  //forward right 2-bits 01 -->LEFT wheel , left 2-bits 10 --> RIGHT wheel
else if (a==0b00000001){PORTB=0b00001000;}  //left
else if (a==0b00000010){PORTB=0b00000001;}  //right
else                   {PORTB=0b00000000;}  //stop
}
return 0;

}
/*
===================Connections================

connect RIGHT sensor to PA0 , LEFT sensor to PA1 (sensor faces towards ground)
connect RIGHE motor to right of L293D , LEFT motor to left of L293D
{connect motor's plug facing smooth surface to each other both sides of L293D}*/
