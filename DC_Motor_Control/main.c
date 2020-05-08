/*
 * File:   main.c
 * Author: Khalid BENEDDINE
 *
 * Created on 26 janvier 2020, 02:40
 */


#include <xc.h>
#include "Config.h"
#include <stdint.h>
#define _XTAL_FREQ 4000000

// PIN Defination
#define Rev RB0   // Reverse Direction Button
#define LV0 RB1   // 0% Speed Button
#define LV1 RB2   // 50% Speed Button
#define LV2 RB3   // 75% Speed Button
#define LV3 RB4   // 100% Speed Button

void PWM_Duty_Cycle(uint16_t);





void main(void) {
    TRISB = 0x1F;  // Pins INPUT
    
    TRISD0 = 0;  // Init the direction
    TRISD1 = 0;
    RD0 = 0;
    RD1 = 1;
    
    CCP1M3 = 1;
    CCP1M2 = 1;
    TRISC2 = 0;
    
    PR2 = 124; // 2Khz
    
    T2CKPS0 = 1; 
    T2CKPS1 = 0;
    
    TMR2ON = 1;
    
    while(1){
        if(Rev){
            RD0 = ~RD0;
            RD1 = ~RD1;
            __delay_ms(500);
        }
        if(LV0){
            PWM_Duty_Cycle(0);
            __delay_ms(100);
        }
        if(LV1){
        PWM_Duty_Cycle(250);
         __delay_ms(100);
        }
        if(LV2){
         PWM_Duty_Cycle(370);
          __delay_ms(100);
         }
          if(LV3){
        PWM_Duty_Cycle(500);
         __delay_ms(100);
        }
        __delay_ms(10);
    }
    
    
    
    return;
}

void PWM_Duty_Cycle(uint16_t DC){
    if(DC<1024){
        CCP1Y = DC & 1;
        CCP1X = DC & 2;
        CCPR1L = DC >> 2;
    }
}