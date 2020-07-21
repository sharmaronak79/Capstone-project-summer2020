#include <LPC214X.h>
#include "uart0.h"
void delay(int time)
{
	int i,j;
	for(i=0;i<=999;i++)
	{
		for(j=0;j<=time;j++);
	}
}

void sendmsg(void)
{
  string_uart0("AT+CMGF=1");    //Sets the GSM Module in Text Mode
	 trans_uart0(0x0D); // for new line
	//trans_uart0(0x0A);
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  string_uart0("AT+CMGS=\"4168276583\""); // Replace x with mobile number
	 
	trans_uart0(0x0D);
	//trans_uart0(0x0A);
  delay(1000);
 string_uart0("sim900a sms");// The SMS text you want to send
  
   trans_uart0(0x1A);// ASCII code of CTRL+Z
  //delay(5000);
}

void makecall()
{
  string_uart0("ATD+14168276583;"); // ATDxxxxxxxxxx; -- watch out here for semicolon at the end!!
 trans_uart0(0x0D);
	trans_uart0(0x0A);
  delay(1000);
}


int main()
{
init_uart0();
//string_uart0("kunskap solution\n\r");
sendmsg();
	//makecall();
	while(1)
	{
	 //trans_uart0(rec_uart0());
		//sendmsg();
	} 
}

