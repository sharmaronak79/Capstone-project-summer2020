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
	
	PINSEL0=0x00000000; //make P0.0 to P0.15 as a GPIO pins
	PINSEL2=0x00000000;  //make P1.16 to P0.31 as a GPIO pins
	
	IODIR0=0x00000001;     //Set P0.0 as a output
	
	while(1)
	{
		if(input&(1<<16))    //input is provided by P0.16
		{
			
		IOSET0=(1<<0);   //value of P0.0 is set
		delay(1000);
		}
	else 
		{
		IOCLR0=(1<<0);  //value of P0.0 is clear
		delay(1000);
}
}
}


