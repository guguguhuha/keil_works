#include <reg52.h>
/***********************************************************************
***        间隔300ms第一次一个管亮流动一次，第二次两个管亮流动.      ***
***        依次到8个管亮，然后重复整个过程。          		           ***
***********************************************************************/
#include <intrins.h>
#define uint unsigned int
#define uchar unsigned char
	
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

void main()
{
	uint i=0,j=0;
	while(1)
	{
		uchar temp=0xfe;
		for(i=0;i<8;i++)
		{
			P2=temp;
			for(j=0;j<8-i;j++)						
			{
				delay(65535);
				P2=_crol_(P2,1);//控制灯的移动
			}
			temp-=pow(2,i+1);//控制灯的个数 
		}
	}
}