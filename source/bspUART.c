#include <header/bspMotor.h>
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
#include  "../header/app.h"
#include  "../header/halScript.h"

void ConfigUART(void){
	P1SEL = BIT1 + BIT2; // P1.1 = RXD, P1.2=TXD
	P1SEL2 = BIT1 + BIT2;
}

