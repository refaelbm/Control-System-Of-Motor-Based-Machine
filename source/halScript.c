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
#include "../header/halScript.h"


void initflash(void){
    _DINT();                             // Disable interrupts(IAR workbench).
    FCTL2 = FWKEY + FSSEL0 + FN1;             // MCLK/3 for Flash Timing Generator
    FCTL1 = FWKEY + ERASE;               // Set Erase bit
    FCTL3 = FWKEY;                       // Clear Lock bit
    *flashPtr = 0;                      // Dummy write to erase Flash segment
     FCTL1 = FWKEY;                      // Clear WRT bit
     FCTL3 = FWKEY + LOCK;               // Set LOCK bit
     _EINT();
}

void readScript(){

    flashPtr = scriptSpot[scriptNumber];

    while(!(*flashPtr == 0x0A && *(flashPtr+1) == 0x30 && *(flashPtr+2) == 0x38)){
        if(*flashPtr == 0x0A) flashPtr++;

        if((*flashPtr == 0x30 && *(flashPtr+1) == 0x31)){
            flashPtr = flashPtr+2;
            if((*flashPtr >= 'A') != 0)
                xTimes = (*flashPtr - 'A' + 1)*16;
            else xTimes = (*flashPtr - '0')*16;
            *flashPtr++;
            if((*flashPtr >= 'A') != 0)
                xTimes = xTimes + (*flashPtr - 'A' + 1);
            else xTimes = xTimes + (*flashPtr - '0');
            xTimesCounter = xTimes*8;
            scriptTask =  1;
            StartTIMER2();
            flashPtr++;
            enterLPM(mode0);
        }else{
        if((*flashPtr == 0x30 && *(flashPtr+1) == 0x32)){
            flashPtr = flashPtr+2;
            if((*flashPtr >= 'A') != 0)
                xTimes = (*flashPtr - 'A' + 1)*16;
            else xTimes = (*flashPtr - '0')*16;
            *flashPtr++;
            if((*flashPtr >= 'A') != 0)
                xTimes = xTimes + (*flashPtr - 'A' + 1)*16;
            else xTimes = xTimes + (*flashPtr - '0');
            xTimesCounter = xTimes;
                        scriptTask =  2;
                        StartTIMER2();
                        flashPtr++;
                        enterLPM(mode0);
         }else{
            if((*flashPtr == 0x30 && *(flashPtr+1) == 0x33)){
                flashPtr = flashPtr+2;
                if((*flashPtr >= 'A') != 0)
                                xTimes = (*flashPtr - 'A' + 1)*16;
                            else xTimes = (*flashPtr - '0');
                            *flashPtr++;
                            if((*flashPtr >= 'A') != 0)
                                xTimes = xTimes + (*flashPtr - 'A' + 1)*16;
                            else xTimes = xTimes + (*flashPtr - '0');
                            xTimesCounter = xTimes;
                                        scriptTask =  3;
                                        StartTIMER2();
                                        flashPtr++;
                            enterLPM(mode0);
                }else{
                    if((*flashPtr == 0x30 && *(flashPtr+1) == 0x34)){
                        flashPtr = flashPtr+2;
                            if((*flashPtr >= 'A') != 0)
                                d = (*flashPtr - 'A' + 1)*16;
                            else d = (*flashPtr - '0')*16;
                            *flashPtr++;
                            if((*flashPtr >= 'A') != 0)
                                d = d + (*flashPtr - 'A' + 1);
                            else d = d + (*flashPtr - '0');
                            flashPtr = flashPtr+2;
                            }else{
                            if((*flashPtr == 0x30 && *(flashPtr+1) == 0x35)){
                                flashPtr = flashPtr+2;
                                RGB = 0x00;
                                Leds = 0x00;
                                RGBOUT &= ~0xE0;
                                LedsOUT &= ~0xF0;
                            }else{
                            if((*flashPtr == 0x30 && *(flashPtr+1) == 0x36)){
                                flashPtr = flashPtr+2;
                                flashPtr = flashPtr+2;
                                    }else{
                                    if((*flashPtr == 0x30 && *(flashPtr+1) == 0x37)){
                                        flashPtr = flashPtr+2;
                                        flashPtr = flashPtr+2;
                                        flashPtr = flashPtr+2;
                                            }
                                    }
                            }
                            }
                }
         }
        }



    }

}
