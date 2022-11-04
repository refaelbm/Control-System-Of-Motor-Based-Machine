#ifndef _halUART_H_
#define _halUART_H_

extern __interrupt void USCI0TX_ISR (void);
extern __interrupt void USCI0RX_ISR (void);
extern void sendJoystickInfo(void);
extern void sendStepinfo(void);

extern void ActiveUART(void);
extern void TxString(void);
extern char JoystickInfo[];
extern char string_State5[];
extern char new_X[];
extern unsigned int i; 
extern unsigned int X;
extern char *flashPtr;
extern char *scriptSpot[];
extern unsigned int scriptNumber;

#endif

