
#include "reg52.h"			 //此文件中定义了单片机的一些特殊功能寄存器

typedef unsigned int u16;	  //对数据类型进行声明定义
typedef unsigned char u8;

sbit LSA=P2^2;
sbit LSB=P2^3;
sbit LSC=P2^4;

u16 count=0;


u8 code smgduan[17]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,
					0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};//显示0~F的值

/******************************************************************************
* 函 数 名         : delay
* 函数功能		   : 延时函数，i=1时，大约延时10us
******************************************************************************/
void delay(u16 i)
{
	while(i--);	
}

void DigDisplay()
{
	u8 i,j;
	P0=smgduan[count];//发送段码
	for(j=0;j<50;j++) //来控制时间间隔
	{
		for(i=0;i<8;i++)
		{
			switch(i)	 //位选，选择点亮的数码管，可以控制亮哪几个灯
			{
				case(0):
					LSA=1;LSB=1;LSC=1; break;//显示第0位
				case(1):
					LSA=0;LSB=1;LSC=1; break;//显示第1位
				case(2):
					LSA=1;LSB=0;LSC=1; break;//显示第2位
				case(3):	
					LSA=0;LSB=0;LSC=1; break;//显示第3位
				case(4):
					LSA=1;LSB=1;LSC=0; break;//显示第4位
				case(5):
					LSA=0;LSB=1;LSC=0; break;//显示第5位
				case(6):
					LSA=1;LSB=0;LSC=0; break;//显示第6位
				case(7):
					LSA=0;LSB=0;LSC=0; break;//显示第7位	
			}
			delay(100); //间隔一段时间扫描	
	    }
    }
}
	


void main()
{	
	while(1)
	{	
		DigDisplay();  //数码管显示函数	
		count++;
		if (count==16)//循环往复
			count=0;
	}		
}
