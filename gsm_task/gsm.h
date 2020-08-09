// declaration of functions
void ser_init(void);      
void tx(unsigned char c);
unsigned char rx(void);
void tx_str(unsigned char *s);
 
void sms(unsigned char *num1,unsigned char *msg);
void gsm_delay(void);
 
unsigned int dell;

void sms(unsigned char *num1,unsigned char *msg)    // definition of sms function
{
    tx_str("AT");   //sending attention command
    tx(0x0d);       // for new line
    gsm_delay();
 
    tx_str("AT+CMGF=1");  // to set up GSM module in text mode
    tx(0x0d);
    gsm_delay();
 
    tx_str("AT+CMGS=");    // to enter number on which message will be sent
    tx('"');              
    while(*num1)
        tx(*num1++);       // entering the digits one by one
    tx('"');
    tx(0x0d);
    gsm_delay();
 
    while(*msg)           // writing the message
        tx(*msg++);
    tx(0x1a);
    gsm_delay();
}
 
void gsm_delay()         // function for delay
{
    unsigned long int gsm_del,ff;
    for(gsm_del=0;gsm_del<=500000;gsm_del++)
         for(ff=0;ff<25;ff++);
}
 
void ser_init()        // initializing function for serial communication
{
    VPBDIV=0x02;      //PCLK = 30MHz
    PINSEL0=0x5;      //to define P0.0 as Tx and P0.1 as Rx pin
    U0LCR=0x83;       // 8 BIT data,1 stop bit,enabling DLAB bit
    U0DLL=195;        // setting baud rate at 9600      
    U0DLM=0;          
    U0LCR=0x03;       // disable DLAB bit
    U0TER=(1<<7);    
}
 
void tx(unsigned char c)    // function for serial transmissin of character
{
    U0THR=c;
    while((U0LSR&(1<<5))==0);   // wait for THRE bit to be 1
}
 
void tx_str(unsigned char *s)   // function for serial transmission of string
{
    while(*s) {
        tx(*s++);
    }
}
 
unsigned char rx()             // function for serial reception
{
    while((U0LSR&(1<<0))==0);  // waits for Receiver Data Ready Pin to be high
    return U0RBR;              // read the value in Receiver Buffer Register
}
