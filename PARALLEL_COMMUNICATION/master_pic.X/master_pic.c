/*
 * File:   master_pic.c
 * Author: girid
 *
 * Created on 31 January, 2026, 10:29 AM
 */


// MASTER PIC16F877A
#include <xc.h>

// CONFIG
#pragma config FOSC = HS, WDTE = OFF, PWRTE = OFF
#pragma config BOREN = OFF, LVP = OFF, CPD = OFF, WRT = OFF, CP = OFF

#define _XTAL_FREQ 20000000

void main() {
    TRISD = 0x00;   // PORTD as OUTPUT (Data)
    TRISB0 = 0;     // RB0 as OUTPUT (Control)

    PORTD = 0x00;
    RB0 = 0;

    while(1) {
        PORTD = 0x01;   // Send data 00000001
        RB0 = 1;        // Data ready
        __delay_ms(1000);

        RB0 = 0;        // Data processed
        __delay_ms(1000);

        PORTD = 0x02;   // Send another data
        RB0 = 1;
        __delay_ms(1000);

        RB0 = 0;
        __delay_ms(1000);
    }
}
