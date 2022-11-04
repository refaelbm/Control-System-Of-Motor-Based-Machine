#include <header/bspMotor.h>
#include <header/halMotor.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <msp430G2553.h>
#include "../header/bspGPIO.h"
#include "../header/halGPIO.h"
#include "../header/bspUART.h"
#include "../header/halUART.h"
#include "../header/bspMOTOR.h"
#include "../header/halMOTOR.h"
#include "../header/api.h"
#include  "../header/app.h"
#include  "../header/halScript.h"

//******************************************************************
// JoyStick
//******************************************************************

void CalcPhi(){
    double temp_phi;
    double x;
    double y;
    double y_x,y_x2;
    y = (Y_sample1-1574);
    x= X_sample1-1587;
    // = (double)();
    if((y>-100 && y<100) && (x>-100 && x<100)){
        phi = 0;
        middle = 1;
    }else if((y>-100 && y<100) && x >100){
        phi = 0;
        middle = 0;
    }else if((y>-100 && y<100) && x <-100){
        phi = 180;
        middle = 0;
    }else if((x>-100 && x<100) && y >100){
        phi = 90;
        middle = 0;
    }else if((x>-100 && x<100) && y <-100){
        phi = -90;
        middle = 0;
    }else{
        y_x = y/x;
        y_x2 = y_x*y_x;
        temp_phi = +(y_x) - (1/3)*y_x*y_x2 + (1/5)*y_x*y_x2*y_x2;
        phi = temp_phi*57.3;
        if(y<-100 && x<-100)
            phi += 180;
        middle = 0;
    }

    if(phi < 0)
        phi+= 360;
}

void JoystickPinter(){
    new_phi = phi;
    JoystickInfo[0] = middle + '0';
/*    if(PBsIntPend & PB){
        penType++;
        if(penType>2) penType = 0;
        PBsIntPend &= ~PB;
    }*/
    JoystickInfo[1] = penType + 0x30;
    JoystickInfo[4] = new_phi % 10 + 0x30;
    new_phi = new_phi/10;
    JoystickInfo[3] = new_phi % 10 + 0x30;
    new_phi = new_phi/10;
    JoystickInfo[2] = new_phi % 10 + 0x30;
}

//******************************************************************
// start the buzzer
//******************************************************************


void StartBuzzer(){
    unsigned int F;

    PBsIntEn |= BIT4;
    F = 131072/(2000 + counterPB1/10);

}


//******************************************************************
// send a command to the LCD
//******************************************************************
void lcd_cmd(unsigned char c){ ///s

    LCD_WAIT; // may check LCD busy flag, or just delay a little, depending on lcd.h

    if (LCD_MODE == FOURBIT_MODE)
    {
        LCD_DATA_WRITE &= ~OUTPUT_DATA;// clear bits before new write
                LCD_DATA_WRITE |= ((c >> 4) & 0x0F) << LCD_DATA_OFFSET;
        lcd_strobe();
                LCD_DATA_WRITE &= ~OUTPUT_DATA;
            LCD_DATA_WRITE |= (c & (0x0F)) << LCD_DATA_OFFSET;
        lcd_strobe();
    }
    else
    {
        LCD_DATA_WRITE = c;
        lcd_strobe();
    }
}

//******************************************************************
// send data to the LCD
//******************************************************************
void lcd_data(unsigned char c){

    LCD_WAIT; // may check LCD busy flag, or just delay a little, depending on lcd.h

    LCD_DATA_WRITE &= ~OUTPUT_DATA;
    LCD_RS(1);
    if (LCD_MODE == FOURBIT_MODE)
    {
            LCD_DATA_WRITE &= ~OUTPUT_DATA;
                LCD_DATA_WRITE |= ((c >> 4) & 0x0F) << LCD_DATA_OFFSET;
        lcd_strobe();
                LCD_DATA_WRITE &= (0xF0 << LCD_DATA_OFFSET) | (0xF0 >> 8 - LCD_DATA_OFFSET);
                LCD_DATA_WRITE &= ~OUTPUT_DATA;
        LCD_DATA_WRITE |= (c & 0x0F) << LCD_DATA_OFFSET;
        lcd_strobe();
    }
    else
    {
        LCD_DATA_WRITE = c;
        lcd_strobe();
    }

    LCD_RS(0);
}
//******************************************************************
// write a string of chars to the LCD
//******************************************************************
void lcd_puts(const char * s){

  while(*s){
        lcd_data(*s++);

  }
}

//******************************************************************
// Delay usec functions
//******************************************************************
void DelayUs(unsigned int cnt){

    unsigned char i;
        for(i=cnt ; i>0 ; i--) asm(" nop"); // tha command asm("nop") takes raphly 1usec

}
//******************************************************************
// Delay msec functions
//******************************************************************
void DelayMs(unsigned int cnt){

    unsigned char i;
        for(i=cnt ; i>0 ; i--) DelayUs(1000); // tha command asm("nop") takes raphly 1usec

}
//******************************************************************
// lcd strobe functions
//******************************************************************
void lcd_strobe(){
  LCD_EN(1);
  asm(" nop");
  asm(" nop");
  LCD_EN(0);
}
//******************************************************************
// State 1 - RGB cycle
//******************************************************************

void RGB_ColorCycle(void){
    unsigned int TEMP;
    TEMP = (RGB-1)<<5;
    RGBOUT &= ~TEMP;
    if(RGB == 0x8) RGB = 0;
    TEMP = RGB<<5;
    RGBOUT |= TEMP;
    RGB +=1;

}
void WriteColor(unsigned int RGB){
    lcd_clear();
    lcd_puts("Color:");/// 6 chars
    switch(RGB){

        case 0x00:
            lcd_puts(" Black");
            break;

        case 0x01:
            lcd_puts(" Blue");
            break;

        case 0x02:
            lcd_puts(" Green");
            break;

        case 0x03:
            lcd_puts(" Cyan");
            break;

        case 0x04:
            lcd_puts(" Red");
            break;

        case 0x05:
            lcd_puts(" Magenta");
            break;

        case 0x06:
            lcd_puts(" Yellow");
            break;

        case 0x07:
            lcd_puts(" White");
            break;
    }
}

//******************************************************************
// State 2 - Count Up
//******************************************************************
void rlc_Leds(void){
    unsigned int TEMP;
    LedsOUT &= ~Leds;
    if(Leds == 0x00) Leds = 0x08;
    if(Leds == 0x80) Leds = 0x00;
        TEMP = Leds<<1;
        LedsOUT |= TEMP;
        Leds = TEMP;
}

void Count_up_display(){
  char Dispalycount[6];
  unsigned int num[5];
  unsigned int temp;

  num[4]= count_up/10000;
  Dispalycount[0] = num[4]+0x30;
  temp= count_up/1000;
  num[3] = temp%10;
  Dispalycount[1] = num[3]+0x30;
  temp= count_up/100;
  num[2] = temp%10;
  Dispalycount[2] = num[2]+0x30;
  temp= count_up/10;
  num[1] = temp%10;
  Dispalycount[3] = num[1]+0x30;
  num[0] = count_up%10;
  Dispalycount[4] = num[0]+0x30;
  Dispalycount[5] = '\0';
  lcd_puts(Dispalycount);
  count_up++;
  /*if (count_up==65536){
      count_up=0;
  }*/

}
//******************************************************************
// State 3 - Count Down
//******************************************************************
void rrc_Leds(void){
    unsigned int TEMP;
    LedsOUT &= ~Leds;
    if(Leds == 0x00) Leds = 0x100;
    if(Leds == 0x10) Leds = 0x00;
       // if(Leds == 0x10) Leds = 0;
    TEMP = Leds>>1;
    LedsOUT |= TEMP;
    Leds = TEMP;
}
void Count_down_display(){
  char Dispalycount[6];
  unsigned int num[5];
  unsigned int temp;

  num[4]= count_down/10000;
  Dispalycount[0] = num[4]+0x30;
  temp= count_down/1000;
  num[3] = temp%10;
  Dispalycount[1] = num[3]+0x30;
  temp= count_down/100;
  num[2] = temp%10;
  Dispalycount[2] = num[2]+0x30;
  temp= count_down/10;
  num[1] = temp%10;
  Dispalycount[3] = num[1]+0x30;
  num[0] = count_down%10;
  Dispalycount[4] = num[0]+0x30;
  Dispalycount[5] = '\0';
  lcd_puts(Dispalycount);
  count_down--;
  /*if (count_down==0){
      count_down=65535;
  }*/

}

//******************************************************************
// State 5 - Puts potentiometer volt
//******************************************************************
void ClearAll(void){
    lcd_clear();
    count_up = 0;
    count_down = 65535;
}

void Print_For_Pot(void){
    lcd_cmd(0xC0);
    lcd_puts(string_State5);

}

//******************************************************************
// State 6 - Clear lcd & reset counters
//******************************************************************


//******************************************************************
// State 8 - Sleep
//******************************************************************
void Sleep(void){

    StopTIMER();
    StopADC();

}
