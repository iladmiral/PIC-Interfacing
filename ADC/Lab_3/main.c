/*
 * File:   main.c
 * Author: Khalid BENEDDINE
 *
 * Created on 20 janvier 2020, 21:42
 */


#include <xc.h>
#include <stdint.h>
#include <stdio.h>
#include "Config.h"
//D�clarations
#define _XTAL_FREQ 4000000
#define Baud 9600

//Globals
uint16_t AN0RES = 0;
float Tempurature, Voltage;
char* TempSTR[25];

//Routines
void ADC_Init();
uint16_t ADC_Read(uint8_t);
void UART_TX_Init(void);
void UART_Write(uint8_t);
void UART_Write_String (char *);

void main(void) {
    ADC_Init();
    UART_TX_Init();
    while(1){
        //Read the ADC
        AN0RES = ADC_Read(0); // Read analog channel 0
        //Calculate the tempurature
        Voltage = AN0RES * 0.0048828;
        Tempurature = Voltage/0.01;
        //Convert Tempurature from flaot to String
        sprintf(TempSTR, "Temperature is -> %.3fc \r\n", Tempurature);
        //Print out the temprature
        UART_Write_String(TempSTR);
        __delay_ms(10);
    }
    return;
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
void UART_TX_Init(void){
    BRGH = 1; //Set High-speed Baud Rate
    SPBRG = 25; // 96000 Baud Rate
    SYNC = 0; // Enable Asyn mode
    SPEN = 1; 
    TRISC6 = 1; // TX & RT Pins
    TRISC7 = 1;
    TXEN = 1; // Enable the transmission 
}

void UART_Write(uint8_t Data){
    while(!TRMT);
    TXREG = Data;
}
void UART_Write_String (char *text){
    uint16_t i;
    for(i=0; text[i]!='\0';i++)
        UART_Write(text[i]);
}