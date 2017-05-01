// UARTTestMain.c
// Runs on LM4F120/TM4C123


#define GPIO_PORTF_DATA_R       (*((volatile unsigned long *)0x400253FC))
#define GPIO_PORTF_DIR_R        (*((volatile unsigned long *)0x40025400))
#define GPIO_PORTF_AFSEL_R      (*((volatile unsigned long *)0x40025420))
#define GPIO_PORTF_PUR_R        (*((volatile unsigned long *)0x40025510))
#define GPIO_PORTF_DEN_R        (*((volatile unsigned long *)0x4002551C))
#define GPIO_PORTF_LOCK_R       (*((volatile unsigned long *)0x40025520))
#define GPIO_PORTF_CR_R         (*((volatile unsigned long *)0x40025524))
#define GPIO_PORTF_AMSEL_R      (*((volatile unsigned long *)0x40025528))
#define GPIO_PORTF_PCTL_R       (*((volatile unsigned long *)0x4002552C))
#define SYSCTL_RCGC2_R          (*((volatile unsigned long *)0x400FE108))
unsigned long Out; // outputs to PF3,PF2,PF1 (multicolor LED)



#include "PLL.h"
#include "UART.h"

//---------------------OutCRLF---------------------
// Output a CR,LF to UART to go to a new line
// Input: none
// Output: none
void OutCRLF(void){
  UART_OutChar(CR);
  UART_OutChar(LF);
}
//debug code
int main(void){
  unsigned char i;
  char string[20];  // global to assist in debugging
  unsigned long n,j;
	int a;
  PLL_Init();
  UART_Init();              // initialize UART
  OutCRLF();
	
	
	// led init
	
	SYSCTL_RCGC2_R |= 0x00000020;     // 1) F clock
  //delay = SYSCTL_RCGC2_R;           // delay   
  GPIO_PORTF_LOCK_R = 0x4C4F434B;   // 2) unlock PortF PF0  
  GPIO_PORTF_CR_R = 0x1F;           // allow changes to PF4-0       
  GPIO_PORTF_AMSEL_R = 0x00;        // 3) disable analog function
  GPIO_PORTF_PCTL_R = 0x00000000;   // 4) GPIO clear bit PCTL  
  GPIO_PORTF_DIR_R = 0x0E;          // 5) PF4,PF0 input, PF3,PF2,PF1 output   
  GPIO_PORTF_AFSEL_R = 0x00;        // 6) no alternate function
  GPIO_PORTF_PUR_R = 0x11;          // enable pullup resistors on PF4,PF0       
  GPIO_PORTF_DEN_R = 0x1F;          // 7) enable digital pins PF4-PF0      
	
	
	
	
  /*for(i='A'; i<='Z'; i=i+1){// print the uppercase alphabet
    UART_OutChar(i);
  }*/
  OutCRLF();
  
	
	GPIO_PORTF_DATA_R = 0x00;
	while(1)
	{
		i=UART_InChar();
		GPIO_PORTF_DATA_R = 0x08;//green pf 3 
		if(i=='0')
		GPIO_PORTF_DATA_R = 0x08;//green pf 3 
		else
		if(i=='1')
			{
				
				GPIO_PORTF_DATA_R = 0x04;//buzzer and red pf2
				a=12000000;
				while(a--);//delay
			}
		
			GPIO_PORTF_DATA_R = 0x08;//green pf 3 
			
	}
}
