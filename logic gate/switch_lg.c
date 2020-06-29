#include <lpc214x.h>
#define selection IOPIN0
#define input IOPIN1

void delay(int time)
{
	int i,j;
	for(i=0;i<=1000;i++)
	{
		for(j=0;j<=time;j++);
	}
}


void main()
{
	PINSEL0=0x00000000;
	PINSEL2=0x00000000;
	IODIR0=0x01;
	IODIR1=0x00000;
	while(1)
	{
		if((!(selection&(1<<1)))&& (!(selection&(1<<2))) ) // condition for AND Gate
		{
			if(input&(1<<16) && input&(1<<17))
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
	
	if((!(selection&(1<<1)))&& (selection&(1<<2)) ) // condition for OR Gate
		{
			if((!(input&(1<<16))) && (!(input&(1<<17))))
 			{
				IOCLR0=(1<<0);
				delay(1000);
			}
		
			else
			{
				IOSET0=(1<<0);
				delay(1000);
			}
	}
	
	if((!(selection&(1<<2)))&& (selection&(1<<1)) ) // condition for NAND Gate
		{
			if((input&(1<<16)) && (input&(1<<17)))
 			{
				IOCLR0=(1<<0);
				delay(1000);
			}
		
			else
			{
				IOSET0=(1<<0);
				delay(1000);
			}
	}
	
	if((selection&(1<<1))&& (selection&(1<<2)) ) // condition for NOR Gate
		{
			if((!(input&(1<<16))) && (!(input&(1<<17))))
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
}