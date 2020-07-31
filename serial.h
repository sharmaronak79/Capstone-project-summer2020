/**
 @file
 
 	This file contains function delaration for source code
 	
*/

#ifndef serial_h_
#define serial_h_
extern void Uart1Init (void);
extern void Uart1PutCh (unsigned char ch);
extern void Uart1PutS (unsigned char *str);
extern unsigned char Uart1GetCh (void);
#endif 


/**

End of file

*/
