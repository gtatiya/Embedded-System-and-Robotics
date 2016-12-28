#include<avr/io.h>
#include<util/delay.h>

void main()
{
DDRB=0xff;    //spesker output PB3
TCCR0=0x19;   //CTC Mode for speaker
DDRA=0xf0;

PORTA=0x0f;    //pull up


while(1)
{
PORTA=0b01111111;    //ground
_delay_ms(50);       //**without delay one of the below condition is true for the 1st iteration**
if((PINA&0b00000001)==0){while((PINA&0b00000001)==0);OCR0=15 ;_delay_ms(500);}  //key(r1,c1)  
if((PINA&0b00000010)==0){while((PINA&0b00000010)==0);OCR0=30;_delay_ms(500);}  //key(r1,c2)  
if((PINA&0b00000100)==0){while((PINA&0b00000100)==0);OCR0=45;_delay_ms(500);}  //key(r1,c3) 
if((PINA&0b00001000)==0){while((PINA&0b00001000)==0);OCR0=60;_delay_ms(500);}  //key(r1,c4) 

PORTA=0b10111111;    //ground
_delay_ms(50);       //**without delay one of the below condition is true for the 1st iteration**
if((PINA&0b00000001)==0){while((PINA&0b00000001)==0);OCR0=75 ;_delay_ms(500);}  //key(r1,c1)  
if((PINA&0b00000010)==0){while((PINA&0b00000010)==0);OCR0=90;_delay_ms(500);}  //key(r1,c2)  
if((PINA&0b00000100)==0){while((PINA&0b00000100)==0);OCR0=105;_delay_ms(500);}  //key(r1,c3) 
if((PINA&0b00001000)==0){while((PINA&0b00001000)==0);OCR0=120;_delay_ms(500);}  //key(r1,c4)  

PORTA=0b11011111;    //ground
_delay_ms(50);       //**without delay one of the below condition is true for the 1st iteration**
if((PINA&0b00000001)==0){while((PINA&0b00000001)==0);OCR0=135;_delay_ms(500);}  //key(r1,c1)  
if((PINA&0b00000010)==0){while((PINA&0b00000010)==0);OCR0=150;_delay_ms(500);}  //key(r1,c2)  
if((PINA&0b00000100)==0){while((PINA&0b00000100)==0);OCR0=165;_delay_ms(500);}  //key(r1,c3) 
if((PINA&0b00001000)==0){while((PINA&0b00001000)==0);OCR0=180;_delay_ms(500);}  //key(r1,c4)  

PORTA=0b11101111;    //ground
_delay_ms(50);       //**without delay one of the below condition is true for the 1st iteration**
if((PINA&0b00000001)==0){while((PINA&0b00000001)==0);OCR0=195;_delay_ms(500);}  //key(r1,c1)  
if((PINA&0b00000010)==0){while((PINA&0b00000010)==0);OCR0=210;_delay_ms(500);}  //key(r1,c2)  
if((PINA&0b00000100)==0){while((PINA&0b00000100)==0);OCR0=225;_delay_ms(500);}  //key(r1,c3) 
if((PINA&0b00001000)==0){while((PINA&0b00001000)==0);OCR0=240;_delay_ms(500);}  //key(r1,c4)   
}
}
/*=============================================
connect PA0-3 to column & PA4-7 to row */
