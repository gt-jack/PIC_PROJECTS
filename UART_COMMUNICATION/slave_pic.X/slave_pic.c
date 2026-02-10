/*
 * File:   slave_pic.c
 * Author: girid
 *
 * Created on 3 February, 2026, 3:44 PM
 */


// SLAVE PIC - UART RECEIVER
#include <xc.h>

#define _XTAL_FREQ 20000000

#pragma config FOSC = HS, WDTE = OFF, PWRTE = OFF, BOREN = OFF
#pragma config LVP = OFF, CPD = OFF, WRT = OFF, CP = OFF

void UART_Init() {
    TRISC6 = 0;  // TX
    TRISC7 = 1;  // RX
    SPBRG = 129;
    TXSTA = 0x24;
    RCSTA = 0x90;
}

char UART_Read() {
    while (!RCIF);
    return RCREG;
}

void main() {
    TRISB0 = 0;  // LED output
    RB0 = 0;

    UART_Init();

    while (1) {
        char data = UART_Read();
        if (data == 'A') {
            RB0 = 1;
            __delay_ms(300);
            RB0 = 0;
        }
    }
}
