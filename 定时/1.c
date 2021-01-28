#include <reg52.h>
#include <intrins.h>

#define uint unsigned int
#define uchar unsigned char

sbit LSA = P2^2;
sbit LSB = P2^3;
sbit LSC = P2^4;
sbit LED = P2^7;
sbit beep = P1^5;

uchar tt;
uint num;
uchar code table[17]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,
							0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};//显示0~F的值


void delay(uint a)
{
	while(a--);
}

/*
int pow(int a,int b)
{
	int ret=1;
	int i=0;
	for(i=0;i<b;i++)
	{
		ret*=a;
	}
	return ret;
}
*/

void exter1() interrupt 1 //
{
	TH0 = (65536 - 50000)/256;//定时器0高8位
	TL0 = (65536 - 50000)%256;//定时器0低8位
	tt++;
}

/*
void exter0() interrupt 0 //中断0
{
	beep = ~beep;
	delay(100);
}
*/

void main()
{
	num = 0;
	tt = 0;
	TMOD = 0x01;//设置定时器0为工作方式1
	TH0 = (65536 - 50000)/256;//定时器0高8位
	TL0 = (65536 - 50000)%256;//定时器0低8位
	//TH1 定时器1高8位   TL1  定时器1低8位
	EA = 1; //打开总中断  
	ET0 = 1; //开定时器0中断
	TR0 = 1;//启动定时器0
	//EX0 = 1; //打开外部中断0
	//IT0 = 0; 默认为0，即为电平触发方式 P32;
	//IT0 = 1;//跳变沿触发方式
	//TCON = 0x01; // 通过位操作调节触发方式，效果与上相同
	while(1)
	{
		if(tt == 4)//一个tt 50毫秒
		{
			tt = 0;
			LED = 1;
			LSA = 0;
			LSB = 0;
			LSC = 0;
			P0 = table[num];
			num++;
			if (num == 16)
				num = 0;
	  } 
  }
}

