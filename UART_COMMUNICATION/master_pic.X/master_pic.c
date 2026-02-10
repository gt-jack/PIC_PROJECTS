/*
 * File:   master_pic.c
 * Author: girid
 *
 * Created on 3 February, 2026, 3:41 PM
 */

// MASTER PIC - UART TRANSMITTER
#include <xc.h>

#define _XTAL_FREQ 20000000

#pragma config FOSC = HS, WDTE = OFF, PWRTE = OFF, BOREN = OFF
#pragma config LVP = OFF, CPD = OFF, WRT = OFF, CP = OFF

void UART_Init() {
    TRISC6 = 0;   // TX
    TRISC7 = 1;   // RX
    SPBRG = 129;  // 9600 baud @20MHz
    TXSTA = 0x24; // TX enable, BRGH=1
    RCSTA = 0x90; // Serial enable
}

void UART_Write(char data) {
    while (!TXIF);
    TXREG = data;
}

void main() {
    TRISA0 = 1;  // Button input
    UART_Init();

    while (1) {
        if (RA0 == 0) {   // Button pressed
            UART_Write('A');
            __delay_ms(500);
        }
    }
}
