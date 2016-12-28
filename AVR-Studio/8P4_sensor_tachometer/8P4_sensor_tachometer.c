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


//void cal(int,int,int);


int main()
{
DDRA=0x00;  // sensor input
DDRD=0xff;  // LCD output
DDRB=0x0f;  // to check
lcd_init();


dis_cmd(0x82);
lcd_string("Tachometer"); //_delay_ms(1000);

int h,m,s,t,val;;

b:
while(1)
{
int a=PINA&0b00000001;
PORTB=a;
if(a==0b00000001) goto b;  //it will only start with white surface
if(a==0b00000000)          //begins as enters a black surface
{
while((PINA&0b00000001)==0);  //wait white its in black surface
dis_cmd(0xc4);
lcd_string("00:00:00");       //timer starts
for(h=0;h<12;h++)
{
 for(m=0;m<60;m++)
  {
   for(s=0;s<60;s++)
    {
	dis_cmd(0xcb);
	lcd_number(s);

    dis_cmd(0xc8);
    lcd_number(m);
   
    dis_cmd(0xc5);
    lcd_number(h);
    _delay_ms(1000);

	if ((PINA&0b00000001)==0) {goto ca;}//{cal(s,m,h);} //checks after every second if it enters next black surface & passes the parameters
  }
 }
}
}
}
ca:
t=s+(m*60)+(h*3600);        //calculate  speed
val=50/t;                   // taking distance 50cm
//dis_cmd(0xc4);lcd_string("            ");
dis_cmd(0x01);_delay_ms(50);
dis_cmd(0x85);lcd_string("SPEED:");
dis_cmd(0xc5);lcd_number(val);
dis_cmd(0xca);lcd_string("spmc");     //cm per sec

return 0;
}

/*void cal(int s,int m,int h)
{
int t,val;
t=s+(m*60)+(h*3600);
val=50/t;
dis_data(0xc4);lcd_string("            ");dis_data(0xc0);lcd_string("SPEED");
dis_data(0xc6);lcd_number(val);
}*/


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
