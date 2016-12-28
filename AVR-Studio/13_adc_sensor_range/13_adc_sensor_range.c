#include<avr/io.h>
#include<util/delay.h>

#define rs 0
#define rw 1
#define en 2

void lcd_init(void);
void lcd_cmd(int);
void dis_cmd(int);
void lcd_data(int);
void dis_data(int);

void lcd_string(char *str);
void lcd_number(int);

unsigned int adc_read(unsigned);

int main()
{
DDRA=0x00;
DDRD=0xff;
DDRB=0x0f;
lcd_init();

dis_cmd(0xc3);
lcd_string("RANGE");_delay_ms(1000);

PORTB=0xff;_delay_ms(50);
PORTB=0x00;_delay_ms(50);

while(1)
{
dis_cmd(0x01);_delay_ms(50);
int a=adc_read(0);
dis_cmd(0x85);
lcd_number(a);_delay_ms(150);               //a is b/w 0 to 1023

if (a<600)      {PORTB=0x09;}     //forward
if (a==600)      {PORTB=0b00000000;}              //stop
if (a>600)      {PORTB=0x06;}   //backward
}
return 0;
}


unsigned int adc_read(unsigned chn)
{
ADMUX=chn|0x40;
ADCSRA=0xd7;
while((ADCSRA&0x10)==0);
ADCSRA|=0x10;                //ADIF=1
//dis_cmd(0xc5);
//lcd_number(ADC);_delay_ms(1000);
return ADC;

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
