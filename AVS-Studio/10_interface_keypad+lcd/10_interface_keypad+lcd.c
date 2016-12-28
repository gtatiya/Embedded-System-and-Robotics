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


int main()
{


DDRA=0x00;
DDRD=0xff;
DDRB=0x0f;
lcd_init();

PORTA=0x0f;
while(1)
{
PORTB=0b00001110;

if ((PINA&0b00000001)==0)
{while((PINA&0b00000001)==0);
 dis_cmd(0x84);
 lcd_string("Forward");
 _delay_ms(2000);
 dis_cmd(0x01);
 _delay_ms(5);
 }

 if ((PINA&0b00000010)==0)
{while((PINA&0b00000010)==0);
 dis_cmd(0x84);
 lcd_string("Backward");
 _delay_ms(2000);
 dis_cmd(0x01);
 _delay_ms(5);
 }
 
}

return 0;
}

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
