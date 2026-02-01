/*
 * File:   slave_pic.c
 * Author: girid
 *
 * Created on 31 January, 2026, 10:39 AM
 */

#// SLAVE PIC16F877A
#include <xc.h>

// CONFIG
#pragma config FOSC = HS, WDTE = OFF, PWRTE = OFF
#pragma config BOREN = OFF, LVP = OFF, CPD = OFF, WRT = OFF, CP = OFF

#define _XTAL_FREQ 20000000

void main() {
    TRISD = 0xFF;   // PORTD as INPUT (Data)
    TRISB0 = 1;     // RB0 as INPUT (Control)
    TRISC0 = 0;     // RC0 as OUTPUT (LED)

    RC0 = 0;

    while(1) {
        if (RB0 == 1) {           // Data ready
            if (PORTD == 0x01) {  // If received data = 1
                RC0 = 1;
                __delay_ms(300);
                RC0 = 0;
            }
            else if (PORTD == 0x02) {
                RC0 = 1;
                __delay_ms(800);
                RC0 = 0;
            }

            while(RB0 == 1); // wait until master clears signal
        }
    }
}

