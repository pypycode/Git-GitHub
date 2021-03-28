#define _XTAL_FREQ 20000000
#define TMR2PRESCALE 4

#include <xc.h>

// BEGIN CONFIG
#pragma config FOSC = HS // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF // Watchdog Timer Enable bit (WDT enabled)
#pragma config PWRTE = OFF // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = ON // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = OFF // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF // Flash Program Memory Code Protection bit (Code protection off)
//END CONFIG

void PWM1_Init(long u32Frequency);
void PWM2_Init(long u32Frequency);
void PWM1_Duty(unsigned int duty);
void PWM2_Duty(unsigned int duty);
void PWM1_Start(void);
void PWM2_Start(void);

long u32TempFrequency;

void main()
{
    PWM1_Init(5000);
    PWM2_Init(5000);
    PWM1_Duty(512);
    PWM2_Duty(768);
    PWM1_Start();
    PWM2_Start();
    while (1)
    {
      
    }
}

void PWM1_Init(long u32Frequency)
{
    PR2 = (_XTAL_FREQ/(u32Frequency*4*TMR2PRESCALE)) - 1;
    u32TempFrequency = u32Frequency;
}

void PWM2_Init(long u32Frequency)
{
    PR2 = (_XTAL_FREQ/(u32Frequency*4*TMR2PRESCALE)) - 1;
    u32TempFrequency = u32Frequency;
}

void PWM1_Duty(unsigned int duty)
{
    if(duty < 1024)
    {
        duty = ((float)duty/1023)*(_XTAL_FREQ/(u32TempFrequency*TMR2PRESCALE));
        CCP1X = duty & 2;
        CCP1Y = duty & 1;
        CCPR1L = duty>>2;
    }
}

void PWM2_Duty(unsigned int duty)
{
    if(duty<1024)
    {
        duty = ((float)duty/1023)*(_XTAL_FREQ/(u32TempFrequency*TMR2PRESCALE));
        CCP2X = duty & 2;
        CCP2Y = duty & 1;
        CCPR2L = duty>>2;
    }
}

void PWM1_Start(void)
{
    /* 11xx = PWM mode */
    CCP1M3 = 1;
    CCP1M2 = 1;
#if TMR2PRESCALE == 1
    T2CKPS0 = 0;
    T2CKPS1 = 0;
#elif TMR2PRESCALE == 4
    T2CKPS0 = 1;
    T2CKPS1 = 0;
#elif TMR2PRESCALE == 16
    T2CKPS0 = 1;
    T2CKPS1 = 1;
#endif
    TMR2ON = 1;
    TRISC2 = 0;
}

void PWM2_Start(void)
{
    CCP2M3 = 0;
    CCP2M2 = 1;
#if TMR2PRESCALE == 1
    T2CKPS0 = 0;
    T2CKPS1 = 0;
#elif TMR2PRESCALE == 4
    T2CKPS0 = 1;
    T2CKPS1 = 0;
#elif TMR2PRESCALE == 16
    T2CKPS0 = 1;
    T2CKPS1 = 1;
#endif
    TMR2ON = 1;
    TRISC1 = 0;
}
