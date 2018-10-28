#include "iocc2530.h"

int flog=0;
int data[4]={0,0,0,0};
  
  void delay(int t){
    int i;
    while(t--){
      for(i=0;i<535;i++);
    }
  }

#pragma vector=P1INT_VECTOR
__interrupt void P1_INT(void){
  if(P1IFG & 0x04){
    if(P1_2==0){
      delay(100);
      if(P1_2==0){
        flog++;
        if(flog==16){
          flog=0;
        }
        int i=0;
        int b=flog;
        if(b!=0){
        while(b!=0){
        data[i]=b%2;
        b=b/2;
        i++;
        }
        }else{
          for(i=0;i<4;i++){
            data[i]=0;
          }
        }
      }
    }
    P1IFG &=~0x04;
  }
  P1IF=0;
}

void main(void){
  P1SEL =0x00;

P1DIR =0x1B;
P1_0=0;
P1_1=0;
P1_3=0;
P1_4=0;

IEN2 |=0x10;
P1IEN |=0x04;
PICTL |=0x02;

EA=1;

 while(1)
    {
  
P1_3=data[0];
P1_4=data[1];
P1_0=data[2];
P1_1=data[3];
  
    }
}