#include <reg52.h>
//1�����ö�ʱ/������T0��P1.0�������Ϊ1s�ķ������÷����������1HZ��˸���辧��Ƶ��Ϊ12MHz��

#define uint unsigned int
#define uchar unsigned char
	
sbit led=P2^0;
sbit output=P1^0;
	
uint i=0;
uint a=0;
/*
void delay(uint a)
{
	while(a--);
}
*/
void time0() interrupt 1
{
	
	TH0=(65536-10000)/256;
	TL0=(65536-10000)%256;
	i++;
}

void time1() interrupt 3
{
	
	TH1=(65536-10000)/256;
	TL1=(65536-10000)%256;
	a++;
}

void init_time0_1()
{
	EA=1;
	
	TMOD=0x11;
	
	ET0=1;
	TR0=1;
	TH0=(65536-10000)/256;//10 ms
	TL0=(65536-10000)%256;
	
	ET1=1;
	TR1=1;
	TH1=(65536-10000)/256;//10 ms
	TL1=(65536-10000)%256;
	
}

void main()
{
	init_time0_1();
	while(1)
	{
		if (i==10)
		{
			i=0;
			led=~led;
		}
		if(a==100)
		{
			a=0;
			output=~output;
		}
	}
}