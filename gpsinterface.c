#include <lpc214x.h>
#include "serial.h"


unsigned int j;

unsigned char Gpsdata;             // for incoming serial data
unsigned int finish =0;            // indicate end of message
unsigned int pos_cnt=0;            // position counter
unsigned int lat_cnt=0;            // latitude data counter
unsigned int log_cnt=0;            // longitude data counter
unsigned int flg    =0;            // GPS flag
unsigned int com_cnt=0;            // comma counter
unsigned char lat[20];             // latitude array
unsigned char lg[20];              // longitude array
unsigned int i=0;
unsigned int fg=0;;
void gps(void);


int main(void)
{

    
 Uart1Init();
while(1)
 {
   gps();
    Uart1PutS("LT:");
		 Uart1PutS(lat);
		 Uart1PutS("N");
		 Uart1PutCh (0x0D);
	   Uart1PutS("LG:");
		 Uart1PutS(lg);
		 Uart1PutS("E");
		 Uart1PutCh (0x0D);
 }
}


void gps()
{
   while(finish==0){
    
     Gpsdata = Uart0GetCh();
        flg = 1;
      if( Gpsdata=='$' && pos_cnt == 0)   // finding GPRMC header
        pos_cnt=1;
      if( Gpsdata=='G' && pos_cnt == 1)
         pos_cnt=2;
      if( Gpsdata=='N' && pos_cnt == 2)
         pos_cnt=3;
      if( Gpsdata=='R' && pos_cnt == 3)
         pos_cnt=4;
      if( Gpsdata=='M' && pos_cnt == 4)
         pos_cnt=5;
      if( Gpsdata=='C' && pos_cnt==5 )
         pos_cnt=6;
      if(pos_cnt==6 &&  Gpsdata ==','){   // count commas in message
        com_cnt++;
         flg=0;
       }

      if(com_cnt==3 && flg==1){
        lat[lat_cnt++] =  Gpsdata;         // latitude
       flg=0;
       }

      if(com_cnt==5 && flg==1){
         lg[log_cnt++] =  Gpsdata;         // Longitude
        flg=0;
       }

      if( Gpsdata == '*' && com_cnt >= 5 && flg == 1){
         lat[lat_cnt] ='\0';             // end of GNRMC message
        lg[log_cnt]  = '\0';
     com_cnt = 0;                      // end of GNRMC message
        lat_cnt = 0;
         log_cnt = 0;
         flg     = 0;
         finish  = 1;

      }
    }

   finish = 0;
   pos_cnt = 0;
}
///////$GPRMC,194530.000,A,3051.8007,N,10035.9989,W,1.49,111.67,310714,,,A*74
