#include <reg52.h>

unsigned int i = 0;

void init1()
{
	EA=1;//�����ж� 
	ET1=1;//�򿪼�����0
	TMOD|=0x10;//���ö�ʱ������ģʽ  �� ��ʱ��1��������ʽ1
	TR1=1;//��ʼ����
	//TH0=(65536-50000)/256;
	//TL0=(65536-50000)%256;
	TH0=0x3c;
	TL0=0xb0;
}

void int1() interrupt 3
{
	//TH0=(65536-50000)/256;
	//TL0=(65536-50000)%256;
	TH0=0x3c;
	TL0=0xb0;
	i++;
}

void main()
{
	init1();
	while(1)
	{
		if(i==10)
		{
			i=0;
			P2=~P2;
		}
	}
}