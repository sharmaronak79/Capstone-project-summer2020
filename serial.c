#include<lpc214x.h>		 //Includes LPC2148 register definitions
#include "serial.h"

void Uart1Init (void)		    // Initialize Serial Interface       
{               	   
    PINSEL0 = 0x050000;           //Enable RxD1 and TxD1                     
    U1LCR = 0x83;                   // 8 bits, no Parity, 1 Stop bit            
    U1DLL = 97;                     // 9600 Baud Rate @ 15MHz PCLK         
    U1LCR = 0x03; 		    // DLAB = 0  
}
				
void Uart1PutCh (unsigned char ch)  // Write character to Serial Port   
{                  		
   	U1THR = ch;
	  while (!(U1LSR & 0x20));        // Wait till THRE bit becomes 1
}

void  Uart1PutS(unsigned char *str)  //A function to send a string on UART1
{  
   while(*str)
   {  
      Uart1PutCh(*str++);	    
   }
}
unsigned char Uart1GetCh (void)		// Read character from Serial Port   
{            
  while (!(U1LSR & 0x01));
  return (U1RBR);
}
