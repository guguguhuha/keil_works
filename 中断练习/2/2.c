#include <reg52.h>
#define uint unsigned int 
#define uchar unsigned char

sbit k3=P3^3;
sbit beep=P1^5;

sbit ESA=P2^2;
sbit ESB=P2^3;
sbit ESC=P2^4;

void delay(uint a)
{
	while(a--);
}

void init1()
{
	EA=1;//打开总中断
	EX1=1;//打开外部中断1
	IT1=1;//触发方式：跳变沿
	//TT1=0;//触发方式：电平触发
}

void int1() interrupt 2
{
	delay(1000);//按键防抖；
	if (k3==0)//判断是否按下了按键
	{
		ESA=1;
		ESB=0;
		ESC=1;
		P0=0xff;
		beep=~beep;
		delay(100);
	}
}

void main()
{
	init1();
	P2=0x00;
	while(1)
	{
		P2=~P2;
		delay(50000);
	}
}
