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



void CalbrationMotor(void){
	StartTIMER();
	counter = 0 ;
	step_number = 0 ;
}

void Do_step(unsigned int step){
	MOTOROUT = halfstep_clockwise[step];
}

void Update_step(){
    if(middle){
        wanted_step = current_step;
    }else if(phi<step_angle)
        wanted_step = 0;
    else
        wanted_step = phi/step_angle;

}

void Move_motor_clockwise(unsigned int step){
    MOTOROUT = step_clockwise[step];
}

void Move_motor_counter_clockwise(unsigned int step){
    MOTOROUT = step_counter_clockwise[step];
}

void showSteps(void){
    double fullCircle = 360;
    double angal;
    unsigned int calc;
    angal = fullCircle/steps;
    calc = angal;
    stepsInFullCircle[0] = calc + 0x30;
    calc = angal*10;
    stepsInFullCircle[1] = calc % 10 + 0x30;
    calc = angal*100;
    stepsInFullCircle[2] = calc % 10 + 0x30;
    if(steps < 1000){
        stepsInFullCircle[7] = steps % 10 + 0x30;
        steps = steps/10;
        stepsInFullCircle[6] = steps % 10 + 0x30;
        steps = steps/10;
        stepsInFullCircle[5] = steps % 10 + 0x30;
        stepsInFullCircle[4] = 0x30;
        stepsInFullCircle[3] = 0x30;
    }else if(steps < 10000){
            steps = steps/10;
            stepsInFullCircle[4] = steps % 10 + 0x30;
            stepsInFullCircle[3] = 0x30;
    }else if(steps < 100000){
        steps = steps/10;
        stepsInFullCircle[3] = steps % 10 + 0x30;
    }
}
