/*
 * File:   led_chaser.c
 * Author: girid
 *
 * Created on 18 January, 2026, 11:21 AM
 */

#include <xc.h>

/* CONFIG BITS */
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
    TRISB = 0x00;    // PORTB as OUTPUT
    PORTB = 0x00;

    while(1)
    {
        PORTB = 0x01;   // 00000001
        __delay_ms(300);

        PORTB = 0x02;   // 00000010
        __delay_ms(300);

        PORTB = 0x04;   // 00000100
        __delay_ms(300);

        PORTB = 0x08;   // 00001000
        __delay_ms(300);
    }
}
