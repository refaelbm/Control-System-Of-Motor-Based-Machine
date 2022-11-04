
#include <header/bspMotor.h>
#include <header/halMotor.h>
#include <stdio.h>
#include <stdlib.h>
#include <msp430G2553.h>
#include "../header/bspGPIO.h"
#include "../header/halGPIO.h"
#include "../header/bspMOTOR.h"
#include "../header/halMOTOR.h"
#include <math.h>

#include "../header/bspUART.h"
#include "../header/halUART.h"

#include "../header/api.h"
#include  "../header/app.h"
#include  "../header/halScript.h"

enum FSMstate state;
enum SYSmode lpm_mode;

//Motor variabels
unsigned int MotorFlag = 0; 
unsigned int step_clockwise[] = {0x01,0x08,0x04,0x02};
unsigned int halfstep_clockwise[] = {0x08,0x0C,0x04,0x06,0x02,0x03,0x01,0x09};
unsigned int step_counter_clockwise[] = {0x08,0x01,0x02,0x04};
unsigned int halfstep_counter_clockwise[] = {0x01,0x03,0x02,0x06,0x04,0x0C,0x08,0x09};
int loop = 8;
int X_sample = 0;
int Y_sample = 0;
int X_sample1 = 0;
int Y_sample1 = 0;
unsigned int sample_type = 1;
double old_phi = 0;
unsigned int old_middle = 0;
unsigned int old_penType = 0;

double phi = 0;
unsigned int new_phi = 0;
double step_angle = 0.7;
unsigned int steps_full_circle = 515;
unsigned int steps = 0;
unsigned int middle = 1;
unsigned int penType = 1;
unsigned int wanted_step = 0;
unsigned int current_step = 0;
char *flashPtr;
unsigned int scriptNumber = 0;
char *scriptSpot[];
char stepsInFullCircle[]={'0','0','0','0','0','0','0','0','\0'};

unsigned int RGB = 0x00;
unsigned int Leds = 0x00;
unsigned int d = 50;
int xTimes = 1;
int xTimesCounter = 1;
int scriptTask = 1;

unsigned int i = 0;
unsigned int X = 500;
unsigned int pot_volt;
unsigned int old_samp = 0;
unsigned int counter = 0;
unsigned int count_up = 0;
unsigned int count_down = 65535;
unsigned int flag = 1;
unsigned int counterPB1=0;
unsigned int BuzzFlag = 0;

//unsigned int RGB_colors[8] = {0x0,0x1,0x2,0x3,0x4,0x5,0x6,0x7};

unsigned int step_number = 0;
// all menu in a string  
char JoystickInfo[] = {'0','0','0','0','0','\0'};

char new_X[7] = "";
char string_State5[] ={'0','.','0','0'};



void main(void)
{

    state = state9;        // start in idle state on RESET
    lpm_mode = mode0;     // start in idle state on RESET

    ConfigGPIO();
    ConfigUART();
    ActiveUART();
    ConfigADC();
	//lcd_init();
	ConfigMotor();
	flashPtr = (char *) 0x1000;
	initflash();

	while(1)
	{
	  switch(state)
		{

	  case state1: //Manual control of motor based machine
            StartADCsampleX();
            enterLPM(lpm_mode);
            sample_type = 0 ;
            StartADCsampleY();
            enterLPM(lpm_mode);
            CalcPhi();
            sample_type = 1 ;
            StartTIMER1();
            enterLPM(lpm_mode);
            break;

	  case state2://Joystick based PC painter
	      StartADCsampleX();
	      enterLPM(lpm_mode);
	      sample_type = 0 ;
	      StartADCsampleY();
		  enterLPM(lpm_mode);
		  CalcPhi();
		  sample_type = 1 ;
		  StopADC();
		  JoystickPinter();
		  //if(middle != old_middle || phi != old_phi || penType != old_penType){
          sendJoystickInfo();
          //    old_middle = middle;
          //    old_phi = phi ;
          //    old_penType = penType;
          enterLPM(lpm_mode);
		  //}
		  break;/*
*/
	  case state3://Stepper Motor
	      CalbrationMotor();
	      enterLPM(lpm_mode);

		  break;

		case state4://Script Mode 
		    enterLPM(lpm_mode);
		    state = state9;
		  break;

		case state5: // Calibration Motor
		    CalbrationMotor();
		    enterLPM(lpm_mode);
		  break;

		 case state6: // Clear
		       showSteps();
               sendStepinfo();
               enterLPM(lpm_mode);
		  break;
/*
		 case state7:
		     enterLPM(lpm_mode);
                break;
*/
	/*	 case state8:

               break;*/

		 case state9: // Clear
		     Sleep();
		     counter = 0;
		     enterLPM(lpm_mode);
		           break;
		 case state10:
		     scriptNumber = 0;
		     readScript();
             state = state9;
              break;
		 case state11:
		     scriptNumber = 1;
              readScript();
              state = state9;
                 break;
		 case state12:
		     scriptNumber = 2;
              readScript();
              state = state9;
                 break;
				   
		}
	}
}

