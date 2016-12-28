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
DDRA=0x00;  //connect DTMF to PA0-3

DDRD=0xff;
DDRB=0x0f;  //motor output
lcd_init();

dis_cmd(0x80);
lcd_string("DTMF");_delay_ms(50);


while(1)
{
int a;
a=adc_read(0);    //**it reads 4-bits PA0-3**
a=(PINA&0x0f);  //PORTB=a;
dis_cmd(0xc2);
lcd_number(a);_delay_ms(500);

if (a==2) {PORTB=0b00000101;dis_cmd(0x01); _delay_ms(50); dis_cmd(0xc5);lcd_string("forword");_delay_ms(50); }     //forword
if (a==4) {PORTB=0b00000100;dis_cmd(0x01); _delay_ms(50); dis_cmd(0xc5);lcd_string("left");_delay_ms(50);}          //left
if (a==6) {PORTB=0b00000001;dis_cmd(0x01); _delay_ms(50); dis_cmd(0xc5);lcd_string("right");_delay_ms(50);}         //right
if (a==8) {PORTB=0b00001010;dis_cmd(0x01); _delay_ms(50); dis_cmd(0xc5);lcd_string("backword");_delay_ms(50);}      //backword
if (a==5) {PORTB=0b00000000;dis_cmd(0x01); _delay_ms(50); dis_cmd(0xc5);lcd_string("stop");_delay_ms(50);}          //stop
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
