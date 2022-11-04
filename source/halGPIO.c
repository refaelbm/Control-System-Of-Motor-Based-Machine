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

//---------------------------------------------------------------------
//            Enter from LPM0 mode
//---------------------------------------------------------------------
void enterLPM(unsigned char LPM_level){
    if (LPM_level == 0x00)
      _BIS_SR(LPM0_bits);     /* Enter Low Power Mode 0 */
        else if(LPM_level == 0x01)
      _BIS_SR(LPM1_bits);     /* Enter Low Power Mode 1 */
        else if(LPM_level == 0x02)
      _BIS_SR(LPM2_bits);     /* Enter Low Power Mode 2 */
    else if(LPM_level == 0x03)
      _BIS_SR(LPM3_bits);     /* Enter Low Power Mode 3 */
        else if(LPM_level == 0x04)
      _BIS_SR(LPM4_bits);     /* Enter Low Power Mode 4 */
}
//---------------------------------------------------------------------
//            Enable interrupts
//---------------------------------------------------------------------
void enable_interrupts(){
  _BIS_SR(GIE);
}
//---------------------------------------------------------------------
//            Disable interrupts
//---------------------------------------------------------------------
void disable_interrupts(){
  _BIC_SR(GIE);
}

//******************************************************************
// Timer_A Interrupt Service Rotine
//******************************************************************
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A (void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(TIMER0_A0_VECTOR))) Timer_A (void)
#endif
{

	if(state==state5){
		counter+=1;
		if(counter==8){
			Do_step(step_number);
			step_number+= 1;
			if(step_number==8){
				step_number = 0;}

			counter = 0;
		}
	}
	if(state==state10 || state==state11 || state==state12){
	    if(scriptTask==1){
	        if(counter == d){
	            if(xTimesCounter>0){
	                RGB_ColorCycle();
	                xTimesCounter--;
	            }else LPM0_EXIT;
	            counter = 0;
	        }else counter++;
	    }
	    if(scriptTask==2){
	                if(counter == d){
	                    if(xTimesCounter>0){
	                        rlc_Leds();
	                        xTimesCounter--;
	                    }else LPM0_EXIT;
	                    counter = 0;
	                }else counter++;
	            }
	    if(scriptTask==3){
	                if(counter == d){
	                    if(xTimesCounter>0){
	                        rrc_Leds();
	                        xTimesCounter--;
	                    }else LPM0_EXIT;
	                    counter = 0;
	                }else counter++;
	            }
	}
	if(state==state3){
	        counter+=1;
	        if(counter==8){
	            Do_step(step_number);
	            step_number+= 1;
	            if(step_number==8){
	                step_number = 0;
	                steps+=1;
	            }

	            counter = 0;
	        }
	    }
	if(state==state1){

	    if(loop > 0) loop--;
	    else Update_step();

        if(current_step>wanted_step){
            Move_motor_clockwise(step_number);
            step_number+= 1;
            if(step_number==4){
                step_number = 0;
                current_step-= 1;
            }
        }else{
            if(current_step<wanted_step){
                Move_motor_counter_clockwise(step_number);
                step_number+= 1;
                if(step_number==4){
                    step_number = 0;
                    current_step+= 1;
                }
            }

	    }
        StopTIMER();
        LPM0_EXIT; // Quit sleep mode

	}
/*
  if(state==state7){
      if(BuzzFlag){
          BUZZEROUT &= ~BIT3;
          BuzzFlag = 0;
      }else{
          BUZZEROUT |= BIT3;
          BuzzFlag = 1;
      }


  }else
      counter+=1;
      if (counter >= X){

          if(state==state1)
              RGB_ColorCycle();

          if(state==state2){
              lcd_cursor_left();
              lcd_cursor_left();
              lcd_cursor_left();
              lcd_cursor_left();
              lcd_cursor_left();
              Count_up_display();
          }

          if(state==state3){
              lcd_cursor_left();
              lcd_cursor_left();
              lcd_cursor_left();
              lcd_cursor_left();
              lcd_cursor_left();
              Count_down_display();
          }
        //  if(state==state4){
        //      CCTL0 = 0;

        //   }

          counter=0;
        }*/
}

//******************************************************************
// Port1 Interrupt Service Routine
//******************************************************************

#pragma vector=PORT1_VECTOR
__interrupt void PORT1_ISR (void){
    
    DelayMs(debounceVal);
    if(PBsIntPend & PB){
      if(state==state2){
          penType += 1;
          if(penType>2) penType = 0;
      }else state = state2;


        }
    //---------------------------------------------------------------------
    //            Exit from a given LPM
    //---------------------------------------------------------------------

           //
    PBsIntPend &= ~PB;
    LPM0_EXIT; // must be called from ISR only
}


//******************************************************************
// ADC10 Interrupt Service Routine
//******************************************************************
#pragma vector = ADC10_VECTOR
__interrupt void ADC10_ISR(void)
{

    if(sample_type){
        X_sample = (int)(1000 * (3.3 * ADC10MEM / 1023)); //1000-for 4 digit value
        if(abs(X_sample-X_sample1)>X_sample/100){
            X_sample1 = X_sample;
            /*
            sample = X_sample;
            sample=sample/10;
            string_State5[3] = sample % 10 + '0';
            sample=sample/10;
            string_State5[2] = sample % 10 + '0';
            sample=sample/10;
            string_State5[0] = sample + '0';*/
            }
        }else{
            Y_sample = (int)(1000 * (3.3 * ADC10MEM / 1023)); //1000-for 4 digit value
            if(abs(Y_sample-Y_sample1)>Y_sample/100){
                Y_sample1 = Y_sample;/*
                sample = X_sample;
                sample=sample/10;
                string_State5[3] = sample % 10 + '0';
                sample=sample/10;
                string_State5[2] = sample % 10 + '0';
                sample=sample/10;
                string_State5[0] = sample + '0';*/
                }
    }

    LPM0_EXIT; // Quit sleep mode
}
