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

void bell();
void bell2();
void sl1();
void sl2();
void sr1();
void sr2();
void sm1();
void sm2();

int main()
{
DDRD=0xff;
lcd_init();
bell();
bell2();
sl1();
sl2();
sr1();
sr2();
sm1();
sm2();
while(1)
{
dis_cmd(0x82);
dis_data(0x00);
_delay_ms(50);
dis_cmd(0x82);
dis_data(0x01);
_delay_ms(50);

dis_cmd(0x81);
dis_data(0x02);
_delay_ms(50);
dis_cmd(0x81);
dis_data(0x03);
_delay_ms(50);

dis_cmd(0x83);
dis_data(0x04);
_delay_ms(50);
dis_cmd(0x83);
dis_data(0x05);
_delay_ms(50);

dis_cmd(0xc2);
dis_data(0x06);
_delay_ms(50);
dis_cmd(0xc2);
dis_data(0x07);
_delay_ms(50);
}

return 0;
}


void bell()
{
dis_cmd(0x40);
dis_data(0x04);
dis_data(0x0e);
dis_data(0x1f);
dis_data(0x1f);
dis_data(0x1f);
dis_data(0x04);
dis_data(0x04);
dis_data(0x00);
}
void bell2()
{
dis_cmd(0x48);
dis_data(0x04);
dis_data(0x0e);
dis_data(0x1f);
dis_data(0x1f);
dis_data(0x1f);
dis_data(0x08);
dis_data(0x08);
dis_data(0x00);
}


void sl1()
{
dis_cmd(0x50);
dis_data(0x08);
dis_data(0x04);
dis_data(0x02);
dis_data(0x00);
dis_data(0x02);
dis_data(0x04);
dis_data(0x08);
dis_data(0x00);
}

void sl2()
{
dis_cmd(0x58);
dis_data(0x04);
dis_data(0x02);
dis_data(0x01);
dis_data(0x00);
dis_data(0x01);
dis_data(0x02);
dis_data(0x04);
dis_data(0x00);
}

void sr1()
{
dis_cmd(0x60);
dis_data(0x02);
dis_data(0x04);
dis_data(0x08);
dis_data(0x00);
dis_data(0x08);
dis_data(0x04);
dis_data(0x02);
dis_data(0x00);
}

void sr2()
{
dis_cmd(0x68);
dis_data(0x01);
dis_data(0x02);
dis_data(0x04);
dis_data(0x00);
dis_data(0x04);
dis_data(0x02);
dis_data(0x01);
dis_data(0x00);
}

void sm1()
{
dis_cmd(0x70);
dis_data(0x00);
dis_data(0x0a);
dis_data(0x0a);
dis_data(0x00);
dis_data(0x0a);
dis_data(0x04);
dis_data(0x00);
dis_data(0x00);
}
void sm2()
{
dis_cmd(0x78);
dis_data(0x00);
dis_data(0x0a);
dis_data(0x0a);
dis_data(0x00);
dis_data(0x00);
dis_data(0x0a);
dis_data(0x04);
dis_data(0x00);
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
