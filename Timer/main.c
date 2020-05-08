/*
 * File:   main.c
 * Author: Home
 *
 * Created on 19 décembre 2019, 21:24
 */


#include <xc.h>
#include "Config.h"
//#define _XTAL_FREQ 4000000

unsigned char c = 0;

void main(void) {
    TRISB0 = 0;
    RB0 = 0;
    
    TMR1IE = 1;
    PEIE = 1;
    GIE = 1;
    
    TMR1 = 15536;
    
    TMR1CS = 0;
    
    T1CKPS0 = 0;
    T1CKPS1 = 0;
    
    TMR1ON=1;
    
    while (1){
        
    }
    return;
}

void __interrupt() ISR(){
            if (TMR1IF){
                TMR1 = 15536;
            c++;
            if (c==20){
                RB0 = ~RB0;
                c = 0;
            }
            TMR1IF = 0;
        }
}