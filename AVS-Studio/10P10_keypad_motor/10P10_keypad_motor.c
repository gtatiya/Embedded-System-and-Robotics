#include<avr/io.h>
#include<util/delay.h>

void main()
{
DDRB=0xff;   //motor output
DDRA=0xf0;

PORTA=0x0f;    //pull up


while(1)
{
PORTA=0b01111111;    //ground
_delay_ms(50);       //**without delay one of the below condition is true for the 1st iteration**
if((PINA&0b00000001)==0){while((PINA&0b00000001)==0);PORTB=0b00001001;}//_delay_ms(2000);}  //key(r1,c1)  forward
if((PINA&0b00000010)==0){while((PINA&0b00000010)==0);PORTB=0b00001000;}//_delay_ms(2000);}  //key(r1,c2)  left
if((PINA&0b00000100)==0){while((PINA&0b00000100)==0);PORTB=0b00000001;}//_delay_ms(2000);}  //key(r1,c3)  right
if((PINA&0b00001000)==0){while((PINA&0b00001000)==0);PORTB=0b00000000;}//_delay_ms(2000);}  //key(r1,c4)  stop

}

}
/*=============================================
connect PA0-3 to column & PA4-7 to row */
