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

unsigned int adc_read(unsigned);

int main()
{
DDRD=0xff;
lcd_init();

DDRB=0xff;

dis_cmd(0x81);
lcd_string("touch screen");_delay_ms(1000);
while(1)
{
DDRA=0b00000101;
PORTA=0b00000001;
int x=adc_read(1);


DDRA=0b00001010;
PORTA=0b00000010;
int y=adc_read(2);

dis_cmd(0x01);_delay_ms(10);
dis_cmd(0x80);lcd_string("X=");
dis_cmd(0xc0);lcd_string("Y=");
dis_cmd(0x86);
lcd_number(x);
dis_cmd(0xc6);
lcd_number(y);_delay_ms(150);

if(x<270){PORTB=0b00000110;_delay_ms(150);}//back
if(x>590){PORTB=0b00001001;_delay_ms(150);}//forward
if(270<x<590)if(y<370){PORTB=0b00000001;_delay_ms(150);}//right
if(270<x<590)if(370<y<670){PORTB=0b00000000;_delay_ms(150);}//stop
if(270<x<590)if(y>670){PORTB=0b00001000;_delay_ms(150);}//right


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
