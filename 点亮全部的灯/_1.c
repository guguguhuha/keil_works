#include<reg52.h>
/*****************
***点亮全部的灯***
*****************/

//方法一
//以位操作方式

/*
sbit D1=P2^0;
sbit D2=P2^1;
sbit D3=P2^2;
sbit D4=P2^3;
sbit D5=P2^4;
sbit D6=P2^5;
sbit D7=P2^6;
sbit D8=P2^7;
void main()
{
	D1=0;
	D2=0;
	D3=0;
	D4=0;
	D5=0;
	D6=0;
	D7=0;
	D8=0;
}
*/

//方法二
//以总线操作方式
void main()
{
	P2=0x00;
}
