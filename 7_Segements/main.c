/*
 * File:   main.c
 * Author: Home
 *
 * Created on 19 décembre 2019, 14:38
 */


#include <xc.h>
#include "Config.h"
#define _XTAL_FREQ 4000000

void main(void) {
    
    unsigned char segment_code[10] = {0xFC, 0x60, 0xDA, 0xF2, 0x66, 0xB6, 0xBE, 0xE0, 0xFE, 0xF6};
    
    TRISB = 0x00;
    PORTB = 0x00;
    unsigned char counter = 0;
    
    while (1) {
        PORTB = segment_code [counter];
        __delay_ms(1000);
        counter++;
        
        if (counter == 10) {
            counter = 0;
        }
    
   }
    
    return;
}
