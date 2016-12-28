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


dis_cmd(0x80);
lcd_string("Visitor Counter");_delay_ms(500);
dis_cmd(0x01);_delay_ms(50);

int c=0,f1=0,f2=0;
;
b:
while(1)
{
int a=PINA&0b00000011;       //RIGHT sensor = PA0 , LEFT sensor = PA1
if (a==0) goto b;
if (a==0b00000010) {f1=1;}   //Entry
if (a==0b00000001) {f2=1;}   //Exit

if (((PINA&0b00000001)==0b00000001)&&(f1==1))
{
while((PINA&0b00000001)==0b00000001);
//if (f1==1)
{c=c+1;dis_cmd(0x01);_delay_ms(50);
dis_cmd(0x81);lcd_string("People");dis_cmd(0xc9);lcd_number(c);_delay_ms(50);f1=0;f2=0;}
}

if (((PINA&0b00000010)==0b00000010)&&(f2==1))
{
while((PINA&0b00000010)==0b00000010);
//if (f2==1)
{c=c-1;dis_cmd(0x01);_delay_ms(50);
dis_cmd(0x81);lcd_string("People");dis_cmd(0xc9);lcd_number(c);_delay_ms(50);f1=0;f2=0;}
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
