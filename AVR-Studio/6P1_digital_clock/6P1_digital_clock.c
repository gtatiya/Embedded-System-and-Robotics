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
DDRD=0xff;
lcd_init();


dis_cmd(0x82);
lcd_string("Digital Clock");



while(1)
{
dis_cmd(0xc4);
lcd_string("00:00:00");

for(int h=0;h<12;h++)
{
 for(int m=0;m<60;m++)
  {
   for(int s=0;s<60;s++)
    {
	dis_cmd(0xcb);
	lcd_number(s);

    dis_cmd(0xc8);
    lcd_number(m);
   
    dis_cmd(0xc5);
    lcd_number(h);
    _delay_ms(1000);
  }
 }
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
 //while (abc!=0)
  
   d=abc%10;
   dis_data(d+48);
   abc=abc/10;
   d=abc%10;
   dis_data(d+48);
   
 //dis_cmd(0x06);
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
