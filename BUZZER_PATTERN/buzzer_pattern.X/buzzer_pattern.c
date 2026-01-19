/*
 * File:   buzzer_pattern.c
 * Author: girid
 *
 * Created on 19 January, 2026, 2:40 PM
 */


#include <xc.h>

// CONFIG
#pragma config FOSC = HS
#pragma config WDTE = OFF
#pragma config PWRTE = OFF
#pragma config BOREN = OFF
#pragma config LVP = OFF
#pragma config CPD = OFF
#pragma config WRT = OFF
#pragma config CP = OFF

#define _XTAL_FREQ 10000000

volatile unsigned char tcount = 0;
volatile unsigned char step = 0;

void main() {
    ADCON1 = 0x06;     // Disable ADC
    TRISB0 = 0;        // RB0 output (buzzer)

    // Timer0 setup
    OPTION_REG = 0b00000111;   // Prescaler 1:256
    TMR0 = 0;
    T0IF = 0;

    while (1) {
        if (T0IF) {
            T0IF = 0;
            TMR0 = 0;
            tcount++;

            switch(step) {

                case 0:                 // Beep 1 ON (100ms)
                    RB0 = 1;
                    if (tcount >= 4) {  // ~100ms
                        tcount = 0;
                        step++;
                    }
                    break;

                case 1:                 // OFF (100ms)
                    RB0 = 0;
                    if (tcount >= 4) {
                        tcount = 0;
                        step++;
                    }
                    break;

                case 2:                 // Beep 2 ON (100ms)
                    RB0 = 1;
                    if (tcount >= 4) {
                        tcount = 0;
                        step++;
                    }
                    break;

                case 3:                 // OFF (300ms)
                    RB0 = 0;
                    if (tcount >= 12) {
                        tcount = 0;
                        step++;
                    }
                    break;

                case 4:                 // Long Beep ON (500ms)
                    RB0 = 1;
                    if (tcount >= 19) { // ~500ms
                        tcount = 0;
                        step++;
                    }
                    break;

                case 5:                 // Pause OFF (1s)
                    RB0 = 0;
                    if (tcount >= 38) { // ~1 second
                        tcount = 0;
                        step = 0;       // Repeat pattern
                    }
                    break;
            }
        }
    }
}

