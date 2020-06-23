

// Define LPC2148 Header File

//#define led IO1PIN // Define LED to Port1

//#define tled IO1DIR // Define Port1 as output


	// this PINSEL register select how to work wit pin as GPIO/pwm/x fun/y fun  so 00,01,10,11
	// so it 0000 0000 0000 0000 0000 0000 0000 0000     
//this is 32 bit register so each two bits for one pin to select its function

// PINSEL ,IODIR , IOSET , IOCLR all are 32 bit register,
// now if i want to turn led on , for port p1.16to p1.23, we first define POINSEL as show before
//now to define them as output so, IODIR1= 0000 0000 0000 0000 0000 0000  0000  0000 we cannot use p1.0 to p1.15 as it is reserved for other
// so   we have to calulate value after decidinig which pin we want to make high 
// so if we want  to make pin 16 to pin 23 high so IODIR1= 0000 0000 1111 1111 0000 0000
//                                                 IODIR1= 0x0   0    F     F   0     0


// same concept for IOSET1 and IOCLR1  , AS Which pin we want to make high and which we want to make low

#include <LPC214X.H>
void delay(int x);

int main()

{

PINSEL2 = 0x00000000; 
	
IODIR1 = 0x00FF0000; // output IODIR used to make as input/output 0/1 respectelely   

while(1) // Loop forever

{

IOSET1 = 0x00010000; // Turn ON P1.16 and 17  make it high
delay(1500);
IOSET1 = 0x00030000; // Turn ON P1.16 and 17  make it high
delay(1500);
IOSET1 = 0x00070000; // Turn ON P1.16 and 17  make it high
delay(1500);
IOSET1 = 0x000F0000; // Turn ON P1.16 and 17  make it high
delay(1500);
IOSET1 = 0x001F0000; // Turn ON P1.16 and 17  make it high
delay(1500);
IOSET1 = 0x003F0000; // Turn ON P1.16 and 17  make it high
delay(1500);
IOSET1 = 0x007F0000; // Turn ON P1.16 and 17  make it high
delay(1500);
IOSET1 = 0x00FF0000; // Turn ON P1.16 and 17  make it high
delay(1500);

IOCLR1 = 0x00FF0000; // Turn OFF P1.16 and 17 make it low 
delay(1500);

}

return 0;

}

void delay(int x)

{

unsigned int k,l;

for(k = x;k > 0;k--)

for(l = 0;l < x;l++);

}
