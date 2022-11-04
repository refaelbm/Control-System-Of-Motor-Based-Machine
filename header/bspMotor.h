#ifndef _bspMotor_H_
#define _bspMotor_H_

#define MOTORDIR P2DIR
#define MOTOROUT P2OUT

extern void ConfigMotor(void);

extern unsigned int MotorFlag; // Tell if we did Reset to the motor






extern unsigned int state;
extern unsigned int X;
extern unsigned int counter;
extern unsigned int pot_volt;

#endif
