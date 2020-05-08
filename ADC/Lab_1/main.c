/*
 * File:   main.c
 * Author: Khalid BENEDDINE
 *
 * Created on 15 janvier 2020, 14:56
 */


#include <xc.h>
#include <stdint.h>
#include"Config.h"
#define _XTAL_FREQ 4000000

void PWM1_Int();
void PWM1_Set_Duty_Cycle(uint16_t);
void ADC_Init();
uint16_t ADC_Read(uint8_t);

void main(void) {
    PWM1_Int();
    ADC_Init();
    while(1){
        PWM1_Set_Duty_Cycle(ADC_Read(0));
        __delay_ms(1);
    }
    return;
}

void PWM1_Int(){
    // Config CCP Module to PWM Mode
    CCP1M3 = 1;
    CCP1M2 = 1;
    TRISC2 = 0;
    // Set the PWM FERQU 5Khz
    PR2 = 124;
    // Set the PS for Timer 2 Ratoi 1/4
    T2CKPS0 = 1;
    T2CKPS1 = 0;
    //Start the CCP 1 PWM
    TMR2ON = 1;
    
}

void PWM1_Set_Duty_Cycle(uint16_t DC){
    // Check if DC value is 10-Bits
    if(DC < 1024){
    CCP1Y = DC & 1;
    CCP1X = DC & 2;
    CCPR1L = DC >> 2;
    }
}

void ADC_Init(){
    ADCON0 = 0x41;
    ADCON1 = 0x80;
}

uint16_t ADC_Read(uint8_t ANC){
    if(ANC<0 || ANC>7){
        return 0;
    }
    ADCON0 &= 0b11000101; // Clear The Channel Selection Bits
    ADCON0 |= ANC<<3;     // Select The Required Channel (ANC)
    __delay_us(30); 
    GO_DONE = 1;          // Start A/D Conversion
    while(ADCON0bits.GO_DONE); // Polling GO_DONE Bit
                               // Provides Delay Until Conversion Is Complete
    return ((ADRESH << 8) + ADRESL); // Return The Right-Justified 10-Bit
}
