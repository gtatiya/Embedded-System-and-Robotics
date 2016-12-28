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

int key();

int store1();
int store2();
int op();
int cal(int,int,int);

void lcd_clear()
{
dis_cmd(0x01);
_delay_ms(50);
}


int main()
{

DDRA=0x00;  //input (PA3-0 = Coulmn)
DDRB=0x0f;  //ground (PB3-0 = Row)

DDRD=0xff;
lcd_init();

PORTA=0x0f;

unsigned int s1,s2,ope,cl;

//while(1)
//{
dis_cmd(0x80);
lcd_string("Arithmatic Calculator");
_delay_ms(5000);
dis_cmd(0x01);
_delay_ms(50);

dis_cmd(0x80);
lcd_string("1st operand");
_delay_ms(500);
lcd_clear();
s1=store1();
lcd_clear();

dis_cmd(0x80);
lcd_string("2nd operand");
_delay_ms(500);
lcd_clear();
s2=store2();
lcd_clear();

dis_cmd(0x80);
lcd_string("Operator");
_delay_ms(500);
lcd_clear();
ope=op();
lcd_clear();
cl=cal(ope,s1,s2);
_delay_ms(500);

lcd_clear();

dis_cmd(0x85);
lcd_number(cl);
//}



return 0;
}

int op()
{
int op1=0;
//while(1)
//{
do
{
op1=key();
if(op1==12) {break;}
else
{
if(op1==13) { dis_cmd(0x81); dis_data('/'); }
if(op1==14) { dis_cmd(0x81); dis_data('*'); }
if(op1==15) { dis_cmd(0x81); dis_data('-'); }
if(op1==16) { dis_cmd(0x81); dis_data('+'); }
}
}while(op1!=12);
//}
dis_cmd(0x85);
lcd_number(op1);
_delay_ms(500);
lcd_clear();
return op1;
}


int cal(int o,int s5,int s6)
{
int re=0;
if(o==13) {re=s5/s6;}
if(o==14) {re=s5*s6;}
if(o==15) {re=s5-s6;}
if(o==16) { lcd_cmd(0x82); lcd_number(s5); re=s5+s6;}
else { lcd_string("wrong result"); }

return re;
}


int store1()
{
int s3=0,y=0;
//while(1)
//{


do
{
y=key();
if(y==12) {break;}
else
{
s3=s3*10+y;
dis_cmd(0x85);
lcd_number(s3);
}
}while(y!=12);

//}
return s3;
}

int store2()
{
int s4=0,y=0;
//while(1)
//{


do
{
y=key();
if(y==12) {break;}
else
{
s4=s4*10+y;
dis_cmd(0x85);
lcd_number(s4);
}
}while(y!=12);

//}
return s4;
}


int key()
{
while(1)
{
PORTB=0b00000111;
{
if ((PINA&0b00000001)==0){while((PINA&0b00000001)==0);return 7;}
if ((PINA&0b00000010)==0){while((PINA&0b00000010)==0);return 4;}
if ((PINA&0b00000100)==0){while((PINA&0b00000100)==0);return 1;}
if ((PINA&0b00001000)==0){while((PINA&0b00001000)==0);return 11;}
}
PORTB=0b00001011;
{
if ((PINA&0b00000001)==0){while((PINA&0b00000001)==0);return 8;}
if ((PINA&0b00000010)==0){while((PINA&0b00000010)==0);return 5;}
if ((PINA&0b00000100)==0){while((PINA&0b00000100)==0);return 2;}
if ((PINA&0b00001000)==0){while((PINA&0b00001000)==0);return 0;}
}
PORTB=0b00001101;
{
if ((PINA&0b00000001)==0){while((PINA&0b00000001)==0);return 9;}
if ((PINA&0b00000010)==0){while((PINA&0b00000010)==0);return 6;}
if ((PINA&0b00000100)==0){while((PINA&0b00000100)==0);return 3;}
if ((PINA&0b00001000)==0){while((PINA&0b00001000)==0);return 12;}
}
PORTB=0b00001110;
{
if ((PINA&0b00000001)==0){while((PINA&0b00000001)==0);return 13;}
if ((PINA&0b00000010)==0){while((PINA&0b00000010)==0);return 14;}
if ((PINA&0b00000100)==0){while((PINA&0b00000100)==0);return 15;}
if ((PINA&0b00001000)==0){while((PINA&0b00001000)==0);return 16;}
}

}}


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
