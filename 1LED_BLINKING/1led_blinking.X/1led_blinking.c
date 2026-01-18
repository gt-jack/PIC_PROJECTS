/*
 * File:   1led_blinking.c
 * Author: girid
 *
 * Created on 18 January, 2026, 10:42 AM
 */


#include <xc.h>

/* CONFIGURATION BITS */
#pragma config FOSC = HS
#pragma config WDTE = OFF
#pragma config PWRTE = ON
#pragma config BOREN = ON
#pragma config LVP = OFF
#pragma config CPD = OFF
#pragma config WRT = OFF
#pragma config CP = OFF

#define _XTAL_FREQ 10000000

void main(void)
{
    TRISBbits.TRISB0 = 0;
    PORTBbits.RB0 = 0;

    while(1)
    {
        PORTBbits.RB0 = 1;
        __delay_ms(500);
        PORTBbits.RB0 = 0;
        __delay_ms(500);
    }
}
