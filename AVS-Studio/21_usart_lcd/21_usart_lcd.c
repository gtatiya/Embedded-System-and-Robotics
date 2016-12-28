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

void trans(int);   //Transmission w.r.t controller
int rec();         //receive w.r.t. controller

int main()
{
DDRD=0xff;  //LCD output
lcd_init();

UCSRB=0x18;
UCSRC=0x86;
UBRRL=51;

dis_cmd(0xc1);lcd_string("USART");

while(1)
{

int x =rec();                               //receive from PC
dis_cmd(0x01);_delay_ms(50);
dis_cmd(0x81);
lcd_number(x);;_delay_ms(50);


trans (x+1);                              //transmit to PC
   

}
return 0;
}

void trans(int i)
{while((UCSRA&0x20)==0); UDR=i;}

int rec()
{while((UCSRA&0x80)==0); return (UDR);}


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
