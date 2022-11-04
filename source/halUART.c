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

unsigned int j;
unsigned int h;
char check;
void ActiveUART(void){
	UCA0CTL1 |= UCSSEL_2;	// SMCLK
	UCA0BR0 = 104;	        //Baud Rate Control 0
	UCA0BR1 = 0;		//Baud Rate Control 1
	UCA0MCTL = UCBRS0;	//No modulation
	UCA0CTL1 &= ~UCSWRST; 	// Initialize USCI state machine
	IE2 |= UCA0RXIE;
}

void TxString(void){
  IE2 |= UCA0TXIE; // Enable USCI_A0 TX interrupt
  UCA0TXBUF = string_State5[i++];
}

void sendJoystickInfo(void){
  IE2 |= (UCA0TXIE + UCA0RXIE); // USCI_A0 TX & RX interrupt enable
  UCA0TXBUF = JoystickInfo[i++];	// TX first character
}

void sendStepinfo(void){
  IE2 |= (UCA0TXIE + UCA0RXIE); // USCI_A0 TX & RX interrupt enable
  UCA0TXBUF = stepsInFullCircle[i++];    // TX first character
}


//******************************************************************
// Tx
//******************************************************************

#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=USCIAB0TX_VECTOR
__interrupt void USCI0TX_ISR(void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(USCIAB0TX_VECTOR))) USCI0TX_ISR (void)
#else
#error Compiler not supported!
#endif
{
	if (state == state2){
		if (JoystickInfo[i] == '\0'){
			state = state9; // Return to sleep state
			IFG2 &= ~UCA0TXIFG;
			i = 0;
			LPM0_EXIT;
		}
		else
			UCA0TXBUF = JoystickInfo[i++]; // TX next character
	}
	else if (state == state6){
            if (stepsInFullCircle[i] == '\0') // TX over
            {
                IE2 &= ~UCA0TXIE;
                IFG2 &= ~UCA0TXIFG;
                state = state9;
                i = 0;
                LPM0_EXIT;

                //LPM0_EXIT;

            }
            else
                UCA0TXBUF = stepsInFullCircle[i++]; // TX next character
        }
}

//******************************************************************
// Rx
//******************************************************************
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=USCIAB0RX_VECTOR
__interrupt void USCI0RX_ISR(void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(USCIAB0RX_VECTOR))) USCI0RX_ISR (void)
#else
#error Compiler not supported!
#endif
{


     if (state == state4){
         __disable_interrupt();
         check = UCA0RXBUF;
         if(check == 'x'){
             LPM0_EXIT; // Quit sleep mode
             __enable_interrupt();
             return ;
         }else
         if(check>='G'){
             if(check == '\0') check = 0;
             if(check == 'G') scriptNumber = 0;
             else if(check == (1+'G')) scriptNumber = 1;
             else scriptNumber = 2;
            scriptSpot[scriptNumber] = flashPtr;
            state = state4;
         }
         else{
             FCTL2 = FWKEY + FSSEL0 + FN1;             // MCLK/3 for Flash Timing Generator
            // FCTL1 = FWKEY + ERASE;                    // Set Erase bit
             FCTL3 = FWKEY;                            // Clear Lock bit
//             *flashPtr = 0;                           // Dummy write to erase Flash segment
             FCTL1 = FWKEY + WRT;                      // Set WRT bit for write operation

             *flashPtr++ = UCA0RXBUF;

             FCTL1 = FWKEY;                            // Clear WRT bit
             FCTL3 = FWKEY + LOCK;                     // Set LOCK bit
             //check = *scriptSpot[scriptNumber];
         }
         __enable_interrupt();
     }

     else{
        StopTIMER();
        StopADC();
        IE2 &= ~UCA0TXIE;
        IFG2 &= ~UCA0TXIFG;
        if(UCA0RXBUF == '1'){
            state = state1;
        }

        if(UCA0RXBUF == '2'){
            state = state2;
        }

        if(UCA0RXBUF == '3'){
            state = state3;
        }

        if(UCA0RXBUF == '4'){
            flashPtr = (char *) 0x1000;
            state = state4;

        }

        if(UCA0RXBUF == '5'){
            state = state5;
            flag=1;

        }
        if(UCA0RXBUF == '6'){
            state = state6;
        }

        if (UCA0RXBUF == '7'){
            state = state7;
        }

        if(UCA0RXBUF == '8'){
            state = state8;
        }
        if(UCA0RXBUF == '9'){
            state = state9;
        }
        if(UCA0RXBUF == 'A'){
                    state = state10;
                }
        if(UCA0RXBUF == 'B'){
                    state = state11;
                }
        if(UCA0RXBUF == 'C'){
                    state = state12;
                }

        LPM0_EXIT; // Quit sleep mode
     }

}



