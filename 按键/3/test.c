
#include <reg52.h>

#define uint unsigned int 
#define uchar unsigned char
	
code uchar table[]={0x3f,0x06,0x5b,0x4f,
					0x66,0x6d,0x7d,0x07,
					0x7f,0x6f,0x77,0x7c,
					0x39,0x5e,0x79,0x71};//显示0~F的值
	
sbit k1=P3^1;
						
sbit LSA=P2^2;
sbit LSB=P2^3;
sbit LSC=P2^4;
						
sbit led=P2^0;						

uint num=0;
						
void delay(uint a)
{
	while(a--);
}


void check()//蜂鸣器一直工作（按下关闭）；
{
	uint i=0;
	uchar temp,key;
	for(i=0;i<4;i++)
	{
		switch(i)//行
		{
			case 0:
				key=0x7f;break;
			case 1:
				key=0xbf;break;
			case 2:
				key=0xdf;break;
			case 3:
				key=0xef;break;
		}
		P1=key;
		temp=P1&0x0f;
		if(temp!=0x0f)
		{
			delay(1000);
			if(temp!=0x0f)
			{
				switch(temp)//列
				{
					case 0x07:
						num=0+(i*4);break;
					case 0x0b:
						num=1+(i*4);break;
					case 0x0d:
						num=2+(i*4);break;
					case 0x0e:
						num=3+(i*4);break;
				}
				while(P1!=key);
			}
		}	
	}
}

void main()
{
	LSA=1;
	LSB=1;
	LSC=1;
	while(1)
	{
		P0=table[num];
		check();
		
	}
}