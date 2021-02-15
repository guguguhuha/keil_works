#include <reg52.h>

#define uint unsigned int 
#define uchar unsigned char
	
sbit LSA=P2^2;
sbit LSB=P2^3;
sbit LSC=P2^4;
sbit k1=P3^1;
sbit k2=P3^0;
sbit k3=P3^2;
sbit k4=P3^3;

uint ms=0,sec=0,min=0;
	
uchar code table[16]={  0x3f,0x06,0x5b,0x4f,
						0x66,0x6d,0x7d,0x07,
						0x7f,0x6f,0x77,0x7c,
						0x39,0x5e,0x79,0x71};//œ‘ æ0~Fµƒ÷µ
uchar smg[8];
						
void delay(uint a)
{
	while(a--);
}

void init()
{
	EA=1;
	TMOD=0x01;
	ET0=1;
	TR0=1;
	TH0=0xdb;
	TL0=0xff;
}

void timer0() interrupt 1
{
	TH0=0xdb;
	TL0=0xff;
	ms++;
	if(ms==100)
	{
		ms=0;
		sec++;
	}
	if(sec==60)
	{
		sec=0;
		min++;
	}
	if(min==100)
	{
		min=0;
	}
}

void smginit()
{
	smg[0]=table[ms%10];
	smg[1]=table[ms/10];
	smg[2]=0x40;
	smg[3]=table[sec%10];
	smg[4]=table[sec/10];
	smg[5]=0x40;
	smg[6]=table[min%10];
	smg[7]=table[min/10];
}

void display()
{
	uint i=0;
	for(i=0;i<8;i++)
	{
		switch(i)
		{
			case 0:
				LSA=0;LSB=0;LSC=0;break;
			case 1:
				LSA=1;LSB=0;LSC=0;break;
			case 2:
				LSA=0;LSB=1;LSC=0;break;
			case 3:
				LSA=1;LSB=1;LSC=0;break;
			case 4:
				LSA=0;LSB=0;LSC=1;break;
			case 5:
				LSA=1;LSB=0;LSC=1;break;
			case 6:
				LSA=0;LSB=1;LSC=1;break;
			case 7:
				LSA=1;LSB=1;LSC=1;break;
		}
		P0=smg[i];
		delay(100);
		P0=0x00;
	}
}

void check()
{
	if(k1==0)
	{
		delay(1000);
		if(k1==0)
		{
			TR0=0;
			while(!k1);
			TR0=1;
		}
	}
}

void main()
{
	init();
	while(1)
	{
		smginit();
		display();
		check();
	}
}