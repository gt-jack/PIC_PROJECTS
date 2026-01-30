#pragma config FOSC = HS
#pragma config WDTE = OFF
#pragma config PWRTE = ON
#pragma config BOREN = ON
#pragma config LVP = OFF
#pragma config CPD = OFF
#pragma config WRT = OFF
#pragma config CP = OFF

#define _XTAL_FREQ 20000000
#include <xc.h>

// ---------- I2C ----------
void I2C_Init() {
    SSPCON = 0x28;
    SSPCON2 = 0x00;
    SSPADD = (_XTAL_FREQ/(4*100000))-1;
    SSPSTAT = 0x00;
    TRISC3 = 1;
    TRISC4 = 1;
}

void I2C_Wait() {
    while ((SSPCON2 & 0x1F) || (SSPSTAT & 0x04));
}

void I2C_Start(){ I2C_Wait(); SEN = 1; }
void I2C_Stop(){ I2C_Wait(); PEN = 1; }

void I2C_Write(unsigned char data){
    I2C_Wait();
    SSPBUF = data;
}

unsigned char I2C_Read(unsigned char ack){
    unsigned char data;
    I2C_Wait(); RCEN = 1;
    I2C_Wait(); data = SSPBUF;
    I2C_Wait();
    ACKDT = (ack)?0:1;
    ACKEN = 1;
    return data;
}

// ---------- RTC ----------
unsigned char bcd2dec(unsigned char v){
    return ((v>>4)*10 + (v & 0x0F));
}

unsigned char RTC_Read_Seconds() {
    unsigned char sec;

    I2C_Start();
    I2C_Write(0xD0);   // RTC write
    I2C_Write(0x00);   // seconds register
    I2C_Stop();

    I2C_Start();
    I2C_Write(0xD1);   // RTC read
    sec = bcd2dec(I2C_Read(0));
    I2C_Stop();

    return sec;
}

// ---------- MAIN ----------
void main() {
    unsigned char prev_sec = 0, sec;

    ADCON1 = 0x06;   // all digital
    TRISD0 = 0;      // LED output
    RD0 = 0;

    I2C_Init();

    while(1) {
        sec = RTC_Read_Seconds();

        if(sec != prev_sec) {
            RD0 = !RD0;      // toggle LED every second
            prev_sec = sec;
        }
    }
}
