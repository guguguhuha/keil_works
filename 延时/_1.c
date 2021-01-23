/*
#include<reg52.h>

sbit D1=P2^0;
unsigned int a;


void main()
{
	while(1)
	{
		a=51000;
		D1=0;
		while(a--);
		a=50000;
		D1=1;
		while(a--);
	}
}
*/
#include <reg52.h>
#define uint unsigned int
#define uchar unsigned char
sbit D1=P2^0;

void delay_1()//不带参数
{
	uint x,y;
	for(x=100;x>0;x--)
		for(y=2000;y>0;y--);
}

void delay(uint a)//带参数
{
	while(a--);
}

void main()
{
	while(1)
	{
		D1=0;
		delay_1();
		D1=1;
		delay(50000);
	}
}
