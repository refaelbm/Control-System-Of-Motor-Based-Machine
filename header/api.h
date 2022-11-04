#ifndef _api_H_
#define _api_H_


extern void lcd_cmd(unsigned char c);
extern void lcd_data(unsigned char c);
extern void lcd_puts(const char * s);
extern void DelayUs(unsigned int cnt);
extern void DelayMs(unsigned int cnt);
extern void lcd_strobe();

extern void CalcPhi(void);
extern void JoystickPinter();
extern unsigned int middle;
extern unsigned int penType;

extern void RGB_ColorCycle (void);
extern void WriteColor(unsigned int RGB);

extern void rlc_Leds(void);
extern void Count_up_display();
extern unsigned int count_up;

extern void rrc_Leds(void);
extern void Count_down_display();
extern unsigned int count_down;

extern void Pot_volt_read();
extern void Print_For_Pot();
extern unsigned int old_samp;
extern unsigned int flag;

extern void StartBuzzer();

extern void ClearAll(void);

extern void Sleep(void);
#endif
