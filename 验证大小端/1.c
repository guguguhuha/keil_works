#include <reg52.h>

#define uint unsigned int
	
sbit LSA=P2^2;
sbit LSB=P2^3;
sbit LSC=P2^4;

void delay(uint a)
{
	while(a--);
}

int check_sys()
{
	int a = 1;
	return (*(char*)&a);
}

int main()
{
	int ret = check_sys();
	LSA=1;
	LSB=1;
	LSC=1;
	while(1)
	{
		if (ret == 1)
		{
			P0=0x06;//在数码管的首位显示 1
		}
		else
		{
			P0=0x3f;//在数码管的首位显示 0
		}
		delay(1000);
	}
}