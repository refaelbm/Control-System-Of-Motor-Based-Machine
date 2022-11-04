#include <header/bspMotor.h>
#include <header/halMotor.h>
#include <stdio.h>
#include <stdlib.h>
#include <msp430G2553.h>
#include "../header/bspGPIO.h"
#include "../header/halGPIO.h"
#include "../header/bspUART.h"
#include "../header/halUART.h"
#include "../header/bspMOTOR.h"
#include "../header/halMOTOR.h"
#include "../header/api.h"
#include "../header/app.h"
#include  "../header/halScript.h"











//******************************************************************
//GPIO Conficuration
//******************************************************************

void ConfigGPIO(void){
  WDTCTL = WDTPW + WDTHOLD; // Stop watchdog timer
  DCOCTL = 0;               // Select lowest DCOx and MODx settings
  BCSCTL1 = CALBC1_1MHZ;    // Set DCO
  DCOCTL = CALDCO_1MHZ;


  RGBDIR |= 0xE0; 	// RGB as GPIO-output direction
  RGBOUT &= ~0xE0; 	// Turn off RGB

  LedsDIR |= 0xF0;   // RGB as GPIO-output direction
  LedsOUT &= ~0xF0;  // Turn off RGB

  // PushButtons Setup

  PBsPortSel &= ~BIT4;
  PBsPortDir &= ~BIT4;
  PBsIntEdgeSel |= BIT4;          // pull-up mode
  PBsIntEn |= BIT4;
  PBsIntPend = 0;            // clear pending interrupts

  enable_interrupts();
}

//******************************************************************
// TIMER Conficuration
//******************************************************************

void StartTIMER(void)
{
    CCR0 = 1048;              // 2^20 * 10^-3 = 1048 = 1 MS
    TACTL = TASSEL_2 + MC_1;  // SMCLK, up mode
    CCTL0 = CCIE;             // CCR0 interrupt enabled
}
void StartTIMER1(void)
{
    CCR0 = 500;              // 2^20 * (21000)^-1 ~ 50Hz
    TACTL = TASSEL_2 + MC_1;  // SMCLK, up mode
    CCTL0 = CCIE;             // CCR0 interrupt enabled
}

void StartTIMER2(void)
{
    CCR0 = 10480;              // 2^20 * 10^-3*10 = 10480 = 10 MS
    TACTL = TASSEL_2 + MC_1;  // SMCLK, up mode
    CCTL0 = CCIE;             // CCR0 interrupt enabled
}

void StopTIMER(void) // Stoping CLK
{
    TACTL = 0;
    CCTL0 = 0;
}
//******************************************************************
// ADC Conficuration
//******************************************************************

void ConfigADC(void){
  ADCINPSELA3 |= BIT3 + BIT0 ; // P1.3 as ADC analog input
}

void StartADCsampleX(void){
	ADC10CTL0 = ADC10SHT_3 + ADC10ON + ADC10IE;  // Sample&Hold time=8, Turn on ADC10, enbale interrupt
	ADC10CTL1 = INCH_3 + CONSEQ_0 + ADC10SSEL_3 + ADC10DIV_7; // Input channel select - A3,  single channel, SMCLK
	ADC10CTL0 |= ENC;                            // Enable conversion
	ADC10CTL0 |= ADC10SC;                        // Start conversion
}
void StartADCsampleY(void){
    ADC10CTL0 = ADC10SHT_3 + ADC10ON + ADC10IE;  // Sample&Hold time=8, Turn on ADC10, enbale interrupt
    ADC10CTL1 = INCH_0 + CONSEQ_0 + ADC10SSEL_3 + ADC10DIV_7; // Input channel select - A0,  single channel, SMCLK
    ADC10CTL0 |= ENC;                            // Enable conversion
    ADC10CTL0 |= ADC10SC;                        // Start conversion
}

void StopADC(void){
    ADC10CTL0 &= ~ADC10IE;  // Sample&Hold time=8, Turn on ADC12, enbale interrupt
   // ADC10CTL1 = INCH_3 + CONSEQ_2 + ADC10SSEL_3; // Input channel select - A3, Repeat single channel, SMCLK
    ADC10CTL0 &= ~ENC;                            // Enable conversion
    ADC10CTL0 &= ~ADC10SC;                        // Start conversion
}


//******************************************************************
// initialize the LCD
//******************************************************************
void lcd_init(){

    char init_value;

    if (LCD_MODE == FOURBIT_MODE) init_value = 0x3 << LCD_DATA_OFFSET;
        else init_value = 0x3F;
    P2SEL &= ~0xE0; // P2.5-7 as GPIO
    P1SEL &= ~0xF0;
    LCD_RS_DIR(OUTPUT_PIN);
    LCD_EN_DIR(OUTPUT_PIN);
    LCD_RW_DIR(OUTPUT_PIN);
        LCD_DATA_DIR |= OUTPUT_DATA;
        LCD_RS(0);
    LCD_EN(0);
    LCD_RW(0);

    DelayMs(15);
        LCD_DATA_WRITE &= ~OUTPUT_DATA;
    LCD_DATA_WRITE |= init_value;
    lcd_strobe();
    DelayMs(5);
        LCD_DATA_WRITE &= ~OUTPUT_DATA;
    LCD_DATA_WRITE |= init_value;
    lcd_strobe();
    DelayUs(200);
        LCD_DATA_WRITE &= ~OUTPUT_DATA;
    LCD_DATA_WRITE |= init_value;
    lcd_strobe();

    if (LCD_MODE == FOURBIT_MODE){
        LCD_WAIT; // may check LCD busy flag, or just delay a little, depending on lcd.h
                LCD_DATA_WRITE &= ~OUTPUT_DATA;
        LCD_DATA_WRITE |= 0x2 << LCD_DATA_OFFSET; // Set 4-bit mode
        lcd_strobe();
        lcd_cmd(0x28); // Function Set
    }
        else lcd_cmd(0x3C); // 8bit,two lines,5x10 dots

    lcd_cmd(0x0F); //Display On, Cursor On, Cursor Blink
    lcd_cmd(0x01); //Display Clear
    lcd_cmd(0x06); //Entry Modeaq
    lcd_cmd(0x80); //Initialize DDRAM address to zero
        lcd_cmd(0x02);
}
/*
void RGB_ColorCycle(void){
    DMA0SA = (int)RGB_colors;
    DMA0SZ = 8;
    DMA0DA = (int)&RGBOUT;
    DMACTL0 = DMA0TSEL_1;
    DMA0CTL = DMADT_4 + DMASRCINCR_3 + DMAEN + DMAIE;
    TACCR0 = 32786*X;
    TACTL = TASSEL_1+MC_3 + TACLR;
}*/
