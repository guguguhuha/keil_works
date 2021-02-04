
#include<reg52.h>

#define uchar unsigned char
#define uint unsigned int 
	
//同时用两个定时器控制蜂鸣器发声，定时器0控制频率，定时器1控制同个频率持续的时间，
//间隔300ms依次输出1，10，50,100，200,400,800,1k（hz）的方波。

sbit beep=P1^5;

uint code yanshi[]={50000,10000,5000,2500,1250,625,500};

uchar t,bp,pd;

void time0() interrupt 1 //定时器0控制频率
{
	TH0=(65536-yanshi[pd])/256;
	TL0=(65536-yanshi[pd])%256;
	bp++;
}

void time1() interrupt 3 //定时器1控制间隔
{
	TH1=(65536-50000)/256;
	TL1=(65536-50000)%256;
	t++;
}

void init()
{
	EA=1;
	ET0=1;
	ET1=1;
	TMOD=0x11;
	TH0=(65536-yanshi[pd])/256;
	TL0=(65536-yanshi[pd])%256;	
	TH1=(65536-50000)/256;
	TL1=(65536-50000)%256;
	TR0=1;TR1=1;
}


void main()
{
	bp=0;
	pd=0;
	beep=0;
	t=0;
	
	init();
	
	while(1)
	{
		if(bp>0)
		{
			TR0=0;
			bp=0;
			beep=~beep;
			if(t==6)//控制300ms
			{
				pd++;
				t=0;
			}
			if(pd==7)//控制yanshi[pd]的值
			{
				pd=0;
			}
			TR0=1;
		}
	}
}

/*
void main()
{
	bp=0;
	pd=0;
	beep=0;
	t=0;
	init();
	while(1)
	{
		while(t<6)
		{
			if(bp>0)
			{
				TR0=0;
				bp=0;
				beep=~beep;
				TR0=1;
			}
		}
		t=0;
		pd++;
		if(pd>6)
		{
			pd=0;
		}
	}
}
*/
