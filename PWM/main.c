/* 
file : main.c 
author : Khalid BENEDDINE

*/

#include <xc.h>
#include <stdint.h>
#include "Config.h"
#define _XTAL_FREQ 4000000

void PWM1_Set_Duty(uint16_t);

void main(void) {
    //Configuration CCP for PWM mode
    CCP1M2 = 1;
    CCP1M3 = 1;
    //Set PIN C2 output
    TRISC2 = 0;
    //PWM Freaquency
    PR2 = 124;
    //Timer 2 Ratio (1:4) 
    T2CKPS0 = 1;
    T2CKPS1 = 0;
    // Start CCP1 PWM
    TMR2ON = 1;
    uint16_t DC=0;
    
    while (1){
        DC = 0;
        while(DC<500){
            PWM1_Set_Duty(DC);
            DC++;
            __delay_ms(2);
        }
        __delay_ms(100);
        while(DC>0){
        PWM1_Set_Duty(DC);
        DC--;
        __delay_ms(2);
        }
        __delay_ms(100);
    }
    
    return;
}

void PWM1_Set_Duty(uint16_t DC){
 
    if(DC <1024){
        CCP1Y = DC & 1;
        CCP1X = DC & 2;
        CCPR1L = DC >> 2;
    }
    
}