#include <lpc214x.h>
#include <stdint.h>
#include <stdio.h>

uint8_t count;
uint32_t rising_edge1, falling_edge, rising_edge2;
int pr;
void delay_ms(uint16_t j)
{
    uint16_t x,i;
	for(i=0;i<j;i++)
	{
    for(x=0; x<6000; x++);    /* loop to generate 1 milisecond delay with Pclk=15MHz */
	}
}

__irq void T0_ISR (void)
{
	if(count == 0)
	{
		rising_edge1 = T0CR1;
		T0CCR = 0x0030; /* Capture mode Cap0.1, capture on falling edge with interrupt */
	}
	else if(count == 1)
	{
		falling_edge = T0CR1;
		T0CCR = 0x0028; /* Capture mode Cap0.1, capture on rising edge with interrupt */
	}
	else if(count == 2)
	{
		rising_edge2 = T0CR1;
	}
	count++;
	T0IR = ( T0IR | 0x20 ); 
	VICVectAddr = 0x00;
}

void UART0_init(void)
{
	PINSEL0 = PINSEL0 | 0x00000005;	/* Enable UART0 Rx0 and Tx0 pins of UART0 */ 
	U0LCR = 0x83;	/* DLAB = 1, 1 stop bit, 8-bit character length*/
	U0DLM = 0x00;	/* For baud rate of 9600 with Pclk = 30MHz */
	U0DLL = 0xC3;	/* We get these values of U0DLL and U0DLM from formula */
	U0LCR = 0x03; /* DLAB = 0 */
}

void UART0_TxChar(char ch) //A function to send a byte on UART0
{
	U0THR = ch;
	while( (U0LSR & 0x40) == 0 );	/* Wait till THRE bit becomes 1 which tells that transmission is completed */
}

void UART0_SendString(char* str) /* A function to send string on UART0 */
{
	uint8_t i = 0;
	while( str[i] != '\0' )
	{
		UART0_TxChar(str[i]);
		i++;
	}
}

int main (void)
{
	//uint32_t period;
	float period;
	float frequency;
	char string1[20];
	char string2[20];
	UART0_init();
	VPBDIV	= 0x00000002; /* For Pclk = 30MHz */
	/* We have configured Cclk=60MHz. Above instruction makes Pclk = Cclk/2 = 30MHz */
	PINSEL0 = PINSEL0 | 0x00000205; /* Configure P0.4 as Capture 0.0 */
	IODIR0=(1<<3); // Making P0.3 pin as output pin
	VICVectAddr0 = (unsigned) T0_ISR; /* T0 ISR Address */
	VICVectCntl0 = 0x00000024; /* Enable T0 IRQ slot */
	VICIntEnable = 0x00000010; /* Enable T0 interrupt */
	VICIntSelect = 0x00000000; /* T0 configured as IRQ */
	T0TCR = 0x02; /* Reset TC and PR */
	T0CCR = 0x0028; /* Capture mode Cap0.1, capture on rising edge with interrupt */
	T0PR = 0x00; /* No pre-scalar */
	T0TCR = 0x01; /* Enable timer */
	count = 0;
	while (1)
	{
		if(count>2)
		{
			VICIntEnable = 0x00000000; /* Disable all interrupts */
			T0CCR = 0x00000000;
			if(rising_edge1<falling_edge<rising_edge2)
			{
				period = ((rising_edge2 - rising_edge1)/1.0);
				frequency = ((30000000/period)*60);
				sprintf(string1,"Period = %f \r\n",period);
				UART0_SendString(string1);
				sprintf(string2,"Frequency = %f \r\n",frequency);								
				UART0_SendString(string2);
				if(frequency>120)
				{
					IOSET0=(1<<3);
					delay_ms(2000);
				}
				else
				{
					IOCLR0= (1<<3);
					delay_ms(1000);
				}
			}
			count = 0;
			VICIntEnable = 0x00000010;
			T0CCR 		= 0x00000028;
			delay_ms(1000);
		}
	}
}

