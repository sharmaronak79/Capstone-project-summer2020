#include<LPC214x.h>
#define input IOPIN1
int i,j,time;
int delay (int time)
{
	for(i=0;i<=1000;i++)
	{
		for(j=0;j<=time;j++);
	}
}
void main()
{
	PINSEL0=0x00000000;
	PINSEL2=0x00000000;
	
	IODIR0=0x00000001;
	
	while(1)
	{
		if(input&(1<<16))
		{
			
		IOSET0=(1<<0);
		delay(1000);
		}
	else 
		{
		IOCLR0=(1<<0);
		delay(1000);
}
}
}


