/*
 * File:   poweron_reset_indicator.c
 * Author: girid
 *
 * Created on 19 January, 2026, 2:51 PM
 */


#include <xc.h>

// CONFIG
#pragma config FOSC = HS        // High Speed Oscillator
#pragma config WDTE = OFF
#pragma config PWRTE = ON       // Power-up Timer ENABLED
#pragma config BOREN = ON
#pragma config LVP = OFF
#pragma config CPD = OFF
#pragma config WRT = OFF
#pragma config CP = OFF

#define _XTAL_FREQ 10000000     // 20 MHz crystal

void main(void)
{
    ADCON1 = 0x06;      // Disable ADC, make all pins digital
    TRISB0 = 0;         // RB0 as output

    PORTBbits.RB0 = 1;  // LED ON ? Power ON Indicator
    __delay_ms(1000);   // 1 second delay
    PORTBbits.RB0 = 0;  // LED OFF

    while(1)
    {
        // Main application code
    }
}
