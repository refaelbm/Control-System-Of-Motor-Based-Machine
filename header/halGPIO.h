#ifndef _halGPIO_H_
#define _halGPIO_H_

extern __interrupt void PORT1_ISR (void);
extern __interrupt void Timer_A (void);
extern __interrupt void ADC10_ISR(void);

extern int loop;
extern int X_sample;
extern int Y_sample;
extern int X_sample1;
extern int Y_sample1;
extern unsigned int sample_type;
extern char string_State5[];

extern void ShiftLeft (void);
extern void ShiftRight (void);

//extern void AllOff (void);

extern unsigned int state;
extern unsigned int X;
extern unsigned int counter;
extern unsigned int pot_volt;
extern unsigned int counterPB1;
extern unsigned int BuzzFlag;
#endif
