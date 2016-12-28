#include<avr/io.h>
#include<util/delay.h>
#include<avr/eeprom.h>

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

void pass_function();

int main()
{

DDRB=0xff;           //output ground keys
DDRA=0x00;           //input keys
PORTA=0x0f;          //pull up

DDRD=0xff;           //display output

lcd_init();

dis_cmd(0x82);lcd_string("EEPROM");_delay_ms(1000);

eeprom_write_block("1234",0x000000,4);   //preset password
char c[4];
//char *pf[4];
eeprom_read_block(c,0x000000,4);
if(c[0]=='1','2','3','4'){pass_function();}   //   {eeprom_write_block("back",0x000000,4);}
//int a=c[0]-48;
//dis_cmd(0xc6);lcd_number(a);_delay_ms(1000);


return 0;
}

/* -----------------------------------------------
connect PA0-3 to Row1-4  & PB0-3 to coulmn 1-4 
--------------------------------------------------*/

void pass_function()
{
unsigned int s=0,y=0,j=0,i=0;
char p[4];
dis_cmd(0x01);_delay_ms(10);
dis_cmd(0x80);lcd_string("Enter New Password");
dis_cmd(0xc6);
while(i!=5)
{
y=key();
if(y==12) {i++;break;}
else
{
p[j]=y;j++;
s=(s*10)+y;
lcd_string("*");
i++;
}
}

eeprom_write_block(p,0x000000,4);
dis_cmd(0x01);_delay_ms(10);
//dis_cmd(0xc9);                               //lcd_number(p);_delay_ms(50);
int a=p[0]-48;
dis_cmd(0xc6);lcd_number(a);_delay_ms(1000);

/*for(int k=0;k<4;k++)
{
int a=p[k]-48;
lcd_number(a);_delay_ms(50);
}*/

}

int key()
{
while(1)
{
PORTB=0b00000111;
{
if ((PINA&0b00000001)==0){while((PINA&0b00000001)==0);return ;}
if ((PINA&0b00000010)==0){while((PINA&0b00000010)==0);return 12;}
if ((PINA&0b00000100)==0){while((PINA&0b00000100)==0);return 0;}
if ((PINA&0b00001000)==0){while((PINA&0b00001000)==0);return ;}
}
PORTB=0b00001011;
{
if ((PINA&0b00000001)==0){while((PINA&0b00000001)==0);return ;}
if ((PINA&0b00000010)==0){while((PINA&0b00000010)==0);return 3;}
if ((PINA&0b00000100)==0){while((PINA&0b00000100)==0);return 2;}
if ((PINA&0b00001000)==0){while((PINA&0b00001000)==0);return 1;}
}
PORTB=0b00001101;
{
if ((PINA&0b00000001)==0){while((PINA&0b00000001)==0);return ;}
if ((PINA&0b00000010)==0){while((PINA&0b00000010)==0);return 6;}
if ((PINA&0b00000100)==0){while((PINA&0b00000100)==0);return 5;}
if ((PINA&0b00001000)==0){while((PINA&0b00001000)==0);return 4;}
}
PORTB=0b00001110;
{
if ((PINA&0b00000001)==0){while((PINA&0b00000001)==0);return ;}
if ((PINA&0b00000010)==0){while((PINA&0b00000010)==0);return 9;}
if ((PINA&0b00000100)==0){while((PINA&0b00000100)==0);return 8;}
if ((PINA&0b00001000)==0){while((PINA&0b00001000)==0);return 7;}
}}
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
