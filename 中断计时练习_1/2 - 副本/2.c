#include <reg52.h>
#include <intrins.h>
//���ö�ʱ/������T1������ʱʱ��,��P1�ڿ���8�����������,ʹ8��ָʾ������һ��һ��������Ϩ��
//������Ƶ��Ϊ10��/��(8����������һ��Ϊһ������)��ѭ����

#define uint unsigned int
#define uchar unsigned char
	

uint i=0;
uint count=0;
uchar temp=0xfe;

void init_time0()
{
	EA=1;
	TMOD=1;
	ET0=1;
	TR0=1;
	TH0=0xDC;//10ms
	TL0=0x05;
}

void time0() interrupt 1
{
	TH0=0xDC;//10ms
	TL0=0x05;
	i++;

}

void main()
{
	init_time0();
	while(1)
	{
		if(i==50)
		{
			i=0;
			count++;
			if(count%2==0)
			{
				if (count<16)
				{
					P2=temp;
					temp=_crol_(temp,1);
				}
				else 
				{
					P2=temp;
					temp=_cror_(temp,1);
				}
				if(count==28)
				{
					count=0;
				}
			}
			else
			{
				P2=0xff;
			}
		}
	}
}