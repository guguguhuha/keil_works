#include <reg52.h>

void init0()
{
	EA=1;//打开总中断 
	ET0=1;//打开计数器0
	TMOD=0x01;//设置定时器工作模式  ： 计时器0，工作方式1
	TR0=1;//开始计数
	//TH0=(65536-50000)/256;
	//TL0=(65536-50000)%256;
	TH0=0x3c;
	TL0=0xb0;
}

void int0() interrupt 1
{
	static unsigned int i = 0;
	//TH0=(65536-50000)/256;
	//TL0=(65536-50000)%256;
	TH0=0x3c;
	TL0=0xb0;
	i++;
	if(i==20)
	{
		i=0;
		P2=~P2;
	}

}

void main()
{
	init0();
	while(1)
	{
		;
	}
}