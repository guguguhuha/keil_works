#include <reg52.h>
#include <intrins.h>
#define uint unsigned int
#define uchar unsigned char
	
uchar temp;

void delay(uint a)
{
	while(a--);
}

void main()
{
	temp=0xfe;
	P2=temp;
	while(1)
	{
		temp=_crol_(temp,1);
		delay(5000);
		P2=temp;
	}
	
}