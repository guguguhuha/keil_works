#include <reg52.h>

void init0()
{
	EA=1;//�����ж� 
	ET0=1;//�򿪼�����0
	TMOD=0x01;//���ö�ʱ������ģʽ  �� ��ʱ��0��������ʽ1
	TR0=1;//��ʼ����
	//TH0=(65536-50000)/256;
	//TL0=(65536-50000)%256;
	TH0=0x3c;
	TL0=0xb0;
}

void int0() interrupt 1
{
	static unsigned int i = 0;
	//TH0=(65536-50000)/256;
	//TL0=(65536-50000)%256;
	TH0=0x3c;
	TL0=0xb0;
	i++;
	if(i==20)
	{
		i=0;
		P2=~P2;
	}

}

void main()
{
	init0();
	while(1)
	{
		;
	}
}