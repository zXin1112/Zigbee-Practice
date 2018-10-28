#include "iocc2530.h"

void Init(void){
  P2SEL &=~0x01;
  P2DIR |=0x01;
  P2_0=0;
}

void UART0Init (void){
  
  CLKCONCMD=0x80;
  PERCFG=0x00;
  P0SEL=0x0c;
  U0CSR |=0x80;
  U0BAUD =216;
  U0GCR=11;
  U0UCR |=0x80;
  
   U0CSR |=0x40;
   URX0IF=0;
   EA=1;
}

void main(void){
  Init();
  UART0Init();
  while(1){
    if(URX0IF){
    URX0IF=0;
    unsigned char c=U0DBUF;   
    switch(c){
    case 0xFA:
      P2_0=1;
      break;
    case 0xFB:
      P2_0=0;
      break;
    }
    
    }
  }
}
