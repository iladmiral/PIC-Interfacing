/*
 * File:   main.c
 * Author: Khalid BENEDDINE
 *
 * Created on 19 d�cembre 2019, 16:11
 */


#include <xc.h>
#include "Config.h"
#define _XTAL_FREQ 4000000

void main(void) {
    
    unsigned char i = 0;
    TRISB = 0x00;
    PORTB = 0x00;
    
    while (1){
        
        for (int j = 0; j < 48; j++){
            PORTB = (1<<i);
            i++;
            __delay_ms(100);
            if (i == 4)
                i = 0;
        }
        __delay_ms(1000);
        for (int j = 0, i = 0; j < 48; j++){
            PORTB = (8>>i);
            i++;
            __delay_ms(100);
            if (i == 4)
                i = 0;
        }
       
    }
    
    return;
}
