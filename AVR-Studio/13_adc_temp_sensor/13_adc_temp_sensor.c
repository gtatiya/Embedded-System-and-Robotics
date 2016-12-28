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
DDRA=0b00000101;  //LM35 from smooth side left pin ground(o/p) ,middle pin data(i/p) ,vcc (o/p)
DDRD=0xff;

PORTA=0b00000001;   // ground-->0 , data-->0, vcc-->1
lcd_init();

dis_cmd(0xc0);lcd_string("Temperature sensor");_delay_ms(500);

while(1)
{
int a=adc_read(1);              // pin-1 is for data
dis_cmd(0x01);_delay_ms(50);

dis_cmd(0x81);
lcd_number(a);

//CALIBRATION     LM35 gives value b/w -55 to 150 ,which is converted into °C

a=(a*500);
a=a/1024;
int b=a/10;
int c=a%10;
dis_cmd(0x85);
dis_data(b+48);
dis_data(c+48);
//dis_cmd(0x85);
//lcd_number(a);
_delay_ms(500);
}
return 0;
}

/*==============================================
connect 3-pin relimate to PORTA0-3            */


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
