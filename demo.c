#include <lpc214x.h>
#define input IOPIN0 //set as an input
int j,k;
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
	
	IODIR0= 0x00000080; //set the seventh pin as an output
	
	while (1)
	{
		if(input& (1<<2))
		{
		
			IOSET0=(1<<7);    //set high on pin 7
			delay(1000);
	}
else 
{
	IOCLR0=(1<<7);   
	delay(1000);
}
}
}

