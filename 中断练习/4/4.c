#include <reg52.h>

unsigned int i = 0;

void init1()
{
	EA=1;//打开总中断 
	ET1=1;//打开计数器0
	TMOD|=0x10;//设置定时器工作模式  ： 计时器1，工作方式1
	TR1=1;//开始计数
	//TH0=(65536-50000)/256;
	//TL0=(65536-50000)%256;
	TH0=0x3c;
	TL0=0xb0;
}

void int1() interrupt 3
{
	//TH0=(65536-50000)/256;
	//TL0=(65536-50000)%256;
	TH0=0x3c;
	TL0=0xb0;
	i++;
}

void main()
{
	init1();
	while(1)
	{
		if(i==10)
		{
			i=0;
			P2=~P2;
		}
	}
}