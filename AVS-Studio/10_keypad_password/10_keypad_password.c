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

DDRA=0x00;  //input (PA3-0 = Coulmn)
DDRB=0x0f;  //ground (PB3-0 = Row)

DDRD=0xff;
lcd_init();

PORTA=0x0f;  //pull up on


while(1)
{
unsigned int sum1=3654,sum=0,y=0;
dis_cmd(0x80);
lcd_string("Password Control");
_delay_ms(1000);

while(1)
{
dis_cmd(0x01);_delay_ms(10);
dis_cmd(0x80);
lcd_string("Enter Password");
dis_cmd(0xc4);

do
{
y=key();
if(y==12) {break;}
else
{
sum=(sum*10)+y;
lcd_string("*");
}
}while(y!=12);



if(sum==sum1)
{
dis_cmd(0x01);_delay_ms(10);
dis_cmd(0x80);
lcd_string("Right Password");
_delay_ms(1500);
}
else
{
dis_cmd(0x01);_delay_ms(10);
dis_cmd(0x80);
lcd_string("Wrong Password");
_delay_ms(1500);
}

}}

return 0;
}

int key()
{//_delay_ms(50);
//while(1)
{
PORTB=0b00000111;
{
if ((PINA&0b00000001)==0){while((PINA&0b00000001)==0);return 7;}//(r1,c1)
if ((PINA&0b00000010)==0){while((PINA&0b00000010)==0);return 4;}//(r1,c2)
if ((PINA&0b00000100)==0){while((PINA&0b00000100)==0);return 1;}//(r1,c3)
if ((PINA&0b00001000)==0){while((PINA&0b00001000)==0);return 11;}//(r1,c4)
}
PORTB=0b00001011;
{
if ((PINA&0b00000001)==0){while((PINA&0b00000001)==0);return 8;}//(r2,c1)
if ((PINA&0b00000010)==0){while((PINA&0b00000010)==0);return 5;}//(r2,c2)
if ((PINA&0b00000100)==0){while((PINA&0b00000100)==0);return 2;}//(r2,c3)
if ((PINA&0b00001000)==0){while((PINA&0b00001000)==0);return 0;}//(r2,c4)
}
PORTB=0b00001101;
{
if ((PINA&0b00000001)==0){while((PINA&0b00000001)==0);return 9;}//(r3,c1)
if ((PINA&0b00000010)==0){while((PINA&0b00000010)==0);return 6;}//(r3,c2)
if ((PINA&0b00000100)==0){while((PINA&0b00000100)==0);return 3;}//(r3,c3)
if ((PINA&0b00001000)==0){while((PINA&0b00001000)==0);return 12;}//(r3,c4) for Enter
}
PORTB=0b00001110;
{
if ((PINA&0b00000001)==0){while((PINA&0b00000001)==0);return 13;}//(r4,c1)
if ((PINA&0b00000010)==0){while((PINA&0b00000010)==0);return 14;}//(r4,c2)
if ((PINA&0b00000100)==0){while((PINA&0b00000100)==0);return 15;}//(r4,c3)
if ((PINA&0b00001000)==0){while((PINA&0b00001000)==0);return 16;}//(r4,c4)
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
