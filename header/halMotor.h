#ifndef _halMotor_H_
#define _halMotor_H_

extern __interrupt void USCI0TX_ISR (void);
extern __interrupt void USCI0RX_ISR (void);

extern void CalbrationMotor(void);
extern void Do_step(unsigned int);
void Update_step(void);
extern void Move_motor_clockwise(unsigned int step);
extern void Move_motor_counter_clockwise(unsigned int step);
extern void showSteps(void);


extern double old_phi;
extern unsigned int old_middle;
extern unsigned int old_penType;

extern double phi;
extern unsigned int new_phi;
extern unsigned int step_clockwise[];
extern unsigned int halfstep_clockwise[];
extern unsigned int step_counter_clockwise[];
extern unsigned int halfstep_counter_clockwise[];
extern unsigned int steps_full_circle;
extern unsigned int steps;
extern unsigned int step_number; 
extern double step_angle;
extern double Hstep_angle;
extern unsigned int wanted_step;
extern unsigned int current_step;
extern char stepsInFullCircle[];

extern void ActiveUART(void);
extern void TxString(void);
extern char string_State5[];
extern char new_X[];
extern unsigned int i; 
extern unsigned int X;

#endif

