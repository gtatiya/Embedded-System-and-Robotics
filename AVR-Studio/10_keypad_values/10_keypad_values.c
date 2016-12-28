#include<avr/io.h>
#include<util/delay.h>

#define rs PD0
#define rw PD1
#define en PD2

void lcd_init(void);
void lcd_cmd(int);
void dis_cmd(int);
void lcd_data(int);
void dis_data(int);

void lcd_string(char *str);
void lcd_number(int);

int key();


int main()
{

DDRA=0x00;
DDRD=0xff;
DDRB=0x0f;
lcd_init();

PORTA=0x0f;
while(1)
{
int y=key();
if(y==7) {dis_data(0x80); dis_data('7');}
if(y==4) {dis_data(0x80); dis_data('4');}
if(y==1) {dis_data(0x80); dis_data('1');}
if(y==11) {dis_data(0x80); dis_cmd(0x01);}

if(y==8) {dis_data(0x80); dis_data('8');}
if(y==5) {dis_data(0x80); dis_data('5');}
if(y==2) {dis_data(0x80); dis_data('2');}
if(y==0) {dis_data(0x80); dis_data('0');}

if(y==9) {dis_data(0x80); dis_data('9');}
if(y==6) {dis_data(0x80); dis_data('6');}
if(y==3) {dis_data(0x80); dis_data('3');}
if(y==12) {dis_data(0x80); dis_data('=');}

if(y==13) {dis_data(0x80); dis_data('/');}
if(y==14) {dis_data(0x80); dis_data('x');}
if(y==15) {dis_data(0x80); dis_data('-');}
if(y==16) {dis_data(0x80); dis_data('+');}
}

return 0;
}

int key()
{
while(1)
{
PORTB=0b00000111;
{
if ((PINA&0b00000001)==0){while((PINA&0b00000001)==0);return 7;}
if ((PINA&0b00000010)==0){while((PINA&0b00000010)==0);return 4;}
if ((PINA&0b00000100)==0){while((PINA&0b00000100)==0);return 1;}
if ((PINA&0b00001000)==0){while((PINA&0b00001000)==0);return 11;}
}
PORTB=0b00001011;
{
if ((PINA&0b00000001)==0){while((PINA&0b00000001)==0);return 8;}
if ((PINA&0b00000010)==0){while((PINA&0b00000010)==0);return 5;}
if ((PINA&0b00000100)==0){while((PINA&0b00000100)==0);return 2;}
if ((PINA&0b00001000)==0){while((PINA&0b00001000)==0);return 0;}
}
PORTB=0b00001101;
{
if ((PINA&0b00000001)==0){while((PINA&0b00000001)==0);return 9;}
if ((PINA&0b00000010)==0){while((PINA&0b00000010)==0);return 6;}
if ((PINA&0b00000100)==0){while((PINA&0b00000100)==0);return 3;}
if ((PINA&0b00001000)==0){while((PINA&0b00001000)==0);return 12;}
}
PORTB=0b00001110;
{
if ((PINA&0b00000001)==0){while((PINA&0b00000001)==0);return 13;}
if ((PINA&0b00000010)==0){while((PINA&0b00000010)==0);return 14;}
if ((PINA&0b00000100)==0){while((PINA&0b00000100)==0);return 15;}
if ((PINA&0b00001000)==0){while((PINA&0b00001000)==0);return 16;}
}

}}


void lcd_string(char *str)
{

  for(int i=0;str[i]!='\0';i++)
  {
  dis_data(str[i]);
  }
}

void lcd_number(int abc)
{
 dis_cmd(0x04);
 unsigned int d=0;
 while (abc!=0)
  {
   d=abc%10;
   dis_data(d+48);
   abc=abc/10;
   }
   
    
 dis_cmd(0x06);
}


void lcd_init()
{
dis_cmd(0x02);
dis_cmd(0x28);
dis_cmd(0x0C);
dis_cmd(0x06);
}

void lcd_cmd(int x)
{
PORTD=x;
PORTD&=~(1<<rs);
PORTD&=~(1<<rw);
PORTD|=(1<<en);
_delay_ms(1);
PORTD&=~(1<<en);
}

void dis_cmd(int x)
{
int x1;
x1=x&0xf0;
lcd_cmd(x1);
x1=(x<<4)&0xf0;
lcd_cmd(x1);
}

void lcd_data(int x)
{
PORTD=x;
PORTD|=(1<<rs);
PORTD&=~(1<<rw);
PORTD|=(1<<en);
_delay_ms(1);
PORTD&=~(1<<en);
}

void dis_data(int x)
{
int x1;
x1=x&0xf0;
lcd_data(x1);
x1=(x<<4)&0xf0;
lcd_data(x1);
}
