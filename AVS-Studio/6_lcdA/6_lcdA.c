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

int main()
{
DDRD=0xff;
lcd_init();
while(1)
{
dis_cmd(0x80);
dis_data('0');

dis_cmd(0x81);
dis_data('1');

dis_cmd(0x82);
dis_data('2');

dis_cmd(0x83);
dis_data('3');

dis_cmd(0x84);
dis_data('4');


dis_cmd(0xc0);
dis_data('5');

dis_cmd(0xc1);
dis_data('6');

dis_cmd(0xc2);
dis_data('7');

dis_cmd(0x83);
dis_data('8');
}
return 0;
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
