#include <reg52.h>
#define uint unsigned int 
#define uchar unsigned char

sbit k3=P3^3;
sbit beep=P1^5;

sbit ESA=P2^2;
sbit ESB=P2^3;
sbit ESC=P2^4;

void delay(uint a)
{
	while(a--);
}

void init1()
{
	EA=1;//�����ж�
	EX1=1;//���ⲿ�ж�1
	IT1=1;//������ʽ��������
	//TT1=0;//������ʽ����ƽ����
}

void int1() interrupt 2
{
	delay(1000);//����������
	if (k3==0)//�ж��Ƿ����˰���
	{
		ESA=1;
		ESB=0;
		ESC=1;
		P0=0xff;
		beep=~beep;
		delay(100);
	}
}

void main()
{
	init1();
	P2=0x00;
	while(1)
	{
		P2=~P2;
		delay(50000);
	}
}
