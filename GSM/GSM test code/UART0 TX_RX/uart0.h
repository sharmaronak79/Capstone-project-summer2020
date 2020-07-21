void init_uart0 (void)					    // Initialize Serial Interface       
{               	   
  	PINSEL0 |= 0x00000005;           //Enable RxD0 and TxD0                    
    U0LCR = 0x83;                   // 8 bits, no Parity, 1 Stop bit            
    U0DLL = 97;                     // 9600 Baud Rate @ 15MHz Pclk Clock as default setting        
    U0LCR = 0x03;					 					// DLAB = 0  
}

void trans_uart0 (unsigned char ch)   // Write character to Serial Port   
{                  		
   while (!(U0LSR & 0x20));
  	U0THR = ch;
}
unsigned char rec_uart0 (void)		// Read character from Serial Port   
{            
  while (!(U0LSR & 0x01));
  return (U0RBR);
}

void  string_uart0(unsigned char *str)	 //A function to send a string on UART0
{  
   while(*str)
   {  
      trans_uart0(*str++);	    
   }
}
