#include <reg52.h>
/***********************************************************************
***        ���300ms��һ��һ����������һ�Σ��ڶ���������������.      ***
***        ���ε�8��������Ȼ���ظ��������̡�          		           ***
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
				P2=_crol_(P2,1);//���ƵƵ��ƶ�
			}
			temp-=pow(2,i+1);//���ƵƵĸ��� 
		}
	}
}