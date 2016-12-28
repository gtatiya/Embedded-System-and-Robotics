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
DDRB=0xf0;
DDRA=0xff;
lcd_init();
while(1)
{
 PORTB=0b10010001;
 PORTA=0b00000001;
 dis_cmd(0x84);
 lcd_string("Forward");
 _delay_ms(1000);
 dis_cmd(0x01);
 PORTB=0b00000000;
 
 PORTB=0b01100000;
 PORTA=0b00000010;
 dis_cmd(0x84);
 lcd_string("Backward");
 _delay_ms(1000);
 dis_cmd(0x01);
 PORTB=0b00000000;

 PORTB=0b10000000;
 PORTA=0b00000100;
 dis_cmd(0x84);
 lcd_string("Right Turn");
 _delay_ms(1000);
 dis_cmd(0x01);
 PORTB=0b00000000;

 PORTB=0b00010000;
 PORTA=0b00001000;
 dis_cmd(0x84);
 lcd_string("Left Turn");
 _delay_ms(1000);
 dis_cmd(0x01);
 PORTB=0b00000000;
 
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
