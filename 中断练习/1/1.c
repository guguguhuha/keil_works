#include <reg52.h>
#define uint unsigned int 
#define uchar unsigned char

sbit k3=P3^2;
sbit ESA=P2^2;
sbit ESB=P2^3;
sbit ESC=P2^4;

void delay(uint a)
{
	while(a--);
}

void init0()
{
	EA=1;//�����ж�
	EX0=1;//���ⲿ�ж�0
	IT0=1;//������ʽ��������
	//TT0=0;//������ʽ����ƽ����
}

void int0() interrupt 0
{
	delay(1000);//����������
	if (k3==0)//�ж��Ƿ����˰���
	{
		ESA=1;
		ESB=0;
		ESC=1;
		P0=0x6f;
		delay(1000);
	}
}

void main()
{
	init0();
	P2=0x00;
	while(1)
	{
		P2=~P2;
		delay(50000);
	}
}
