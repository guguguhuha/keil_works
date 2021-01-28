#include <reg52.h>
#include <intrins.h>
#define uint unsigned int
#define uchar unsigned char
	
sbit beep = P1^5;
	
void delay(uint a)
{
	while(a--);
}

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

void exter0() interrupt 0 //中断0
{
	beep = ~beep;
	delay(100);
}

void main()
{
	EA = 1; //打开总中断  
	EX0 = 1; //打开外部中断0
	//IT0 = 0; 默认为0，即为电平触发方式 P32;
	IT0 = 1;//跳变沿触发方式
	// TCON = 0x01; // 通过位操作调节触发方式，效果与上相同
	while(1)
	{
		uint j,i;
		uchar temp=0xfe;
		for(i=0;i<8;i++)
		{
			P2=temp;
			for(j=0;j<8-i;j++)						
			{
				delay(10000);
				P2=_crol_(P2,1);//控制灯的移动
			}
			temp-=pow(2,i+1);//控制灯的个数 
	  }
  }
}

