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


int main()
{

DDRB=0xff;           //output ground {2 keys (c4,r4)-START & (c4,r3)-STOP}
DDRA=0x00;           //input 
DDRD=0xff;                        //display output
PORTA=0x0f;          //pull up
lcd_init();

dis_cmd(0x82);
lcd_string("Stop Watch");
_delay_ms(1000);

/*while(1)
{


//int a=PIND;

PORTB=PINA;
*/
mi:
while(1)
{
int y=key();
if(y==1) 
{
	dis_cmd(0xc0); lcd_string("Start ");     //press (c4,r4)-START
	dis_cmd(0xc6);
	lcd_string("00:00:00");

	for(int h=0;h<12;h++)
	{
	 for(int m=0;m<60;m++)
	  {
	   for(int s=0;s<60;s++)
	    {              
		dis_cmd(0xcd);
		lcd_number(s);

	    dis_cmd(0xca);
	    lcd_number(m);
   
	    dis_cmd(0xc7);
	    lcd_number(h);

		               y=key();if(y==2) {dis_cmd(0xc0);lcd_string("     ");     //press (c4,r3)-STOP
		                                 dis_cmd(0xc0);lcd_string("Stop"); goto mi;}
		}}}

}

if(y==2) {dis_cmd(0xc0); lcd_string("Stop");break;}
}

return 0;
}

/* -----------------------------------------------
connect PA0-3 to Row1-4  & PB0-3 to coulmn 1-4 
--------------------------------------------------*/



int key()
{

{
PORTB=0b00001110;                                    //PORTB gives ground
{
if((PINA&0b00000001)==0)
{while((PINA&0b00000001)==0);dis_cmd(0x80);lcd_string("1");_delay_ms(1000);return 1;}

if((PINA&0b00000010)==0)
{while((PINA&0b00000010)==0);dis_cmd(0x80);lcd_string("2");_delay_ms(1000);return 2;}
}
}
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
