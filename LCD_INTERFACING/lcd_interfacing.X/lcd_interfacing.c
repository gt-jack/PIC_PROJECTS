/*
 * File:   lcd_interfacing.c
 * Author: girid
 *
 * Created on 20 January, 2026, 9:15 AM
 */


#include <xc.h>

// CONFIGURATION BITS
#pragma config FOSC = HS
#pragma config WDTE = OFF
#pragma config PWRTE = ON
#pragma config BOREN = OFF
#pragma config LVP = OFF
#pragma config CPD = OFF
#pragma config WRT = OFF
#pragma config CP = OFF

#define _XTAL_FREQ 10000000

// LCD Pins
#define RS RB0
#define EN RB1

#define D4 RD4
#define D5 RD5
#define D6 RD6
#define D7 RD7

// Function Prototypes
void LCD_Command(unsigned char);
void LCD_Char(unsigned char);
void LCD_Init(void);
void LCD_String(const char *);
void LCD_Clear(void);
void LCD_SetCursor(unsigned char, unsigned char);

// Send 4-bit data
void LCD_Send4Bit(unsigned char data)
{
    D4 = (data >> 0) & 1;
    D5 = (data >> 1) & 1;
    D6 = (data >> 2) & 1;
    D7 = (data >> 3) & 1;

    EN = 1;
    __delay_ms(1);
    EN = 0;
}

// LCD Command
void LCD_Command(unsigned char cmd)
{
    RS = 0;
    LCD_Send4Bit(cmd >> 4);
    LCD_Send4Bit(cmd & 0x0F);
    __delay_ms(2);
}

// LCD Character
void LCD_Char(unsigned char data)
{
    RS = 1;
    LCD_Send4Bit(data >> 4);
    LCD_Send4Bit(data & 0x0F);
    __delay_ms(2);
}

// LCD Initialize
void LCD_Init()
{
    TRISB = 0x00;
    TRISD = 0x00;

    __delay_ms(20);

    LCD_Command(0x02); // 4-bit mode
    LCD_Command(0x28); // 2 line, 5x7 matrix
    LCD_Command(0x0C); // Display ON, Cursor OFF
    LCD_Command(0x06); // Auto increment cursor
    LCD_Command(0x01); // Clear display
}

// Print String
void LCD_String(const char *str)
{
    while(*str)
        LCD_Char(*str++);
}

// Clear LCD
void LCD_Clear()
{
    LCD_Command(0x01);
}

// Set Cursor
void LCD_SetCursor(unsigned char row, unsigned char col)
{
    if(row == 1)
        LCD_Command(0x80 + col);
    else
        LCD_Command(0xC0 + col);
}

// MAIN
void main()
{
    LCD_Init();

    LCD_SetCursor(1,0);
    LCD_String("PIC LCD TEST");

    LCD_SetCursor(2,0);
    LCD_String("No I2C Mode");

    while(1);
}
