#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/debug.h"
#include "driverlib/pwm.h"
#include "driverlib/pin_map.h"
#include "inc/hw_gpio.h"
#include "driverlib/rom.h"
#define PWM_FREQUENCY 55
#define DELAY_MS(x) (SysCtlDelay(6700000/500*x))

int i=999;
uint8_t transitionDelay=0;

void part1(){
    volatile uint32_t ui32Load;
    volatile uint32_t ui32PWMClock;
    volatile uint8_t ui8Adjust;
    ui8Adjust = 999;
    ROM_SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_OSC_MAIN|SYSCTL_XTAL_16MHZ);
    ROM_SysCtlPWMClockSet(SYSCTL_PWMDIV_64);
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM1);
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);

    ROM_GPIOPinTypePWM(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);
    ROM_GPIOPinConfigure(GPIO_PF1_M1PWM5);
    ROM_GPIOPinConfigure(GPIO_PF2_M1PWM6);
    ROM_GPIOPinConfigure(GPIO_PF3_M1PWM7);
    HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) = GPIO_LOCK_KEY;
    HWREG(GPIO_PORTF_BASE + GPIO_O_CR) |= 0x01;
    HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) = 0;
    ROM_GPIODirModeSet(GPIO_PORTF_BASE, GPIO_PIN_4|GPIO_PIN_0, GPIO_DIR_MODE_IN);
    ROM_GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_4|GPIO_PIN_0, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
    ui32PWMClock = SysCtlClockGet() / 64;
    ui32Load = (ui32PWMClock / PWM_FREQUENCY) - 1;

    // Pin R
    PWMGenConfigure(PWM1_BASE, PWM_GEN_2, PWM_GEN_MODE_DOWN);
    PWMGenPeriodSet(PWM1_BASE, PWM_GEN_2, ui32Load);
    ROM_PWMPulseWidthSet(PWM1_BASE, PWM_OUT_5, 1 * ui32Load / 1000);
    ROM_PWMOutputState(PWM1_BASE, PWM_OUT_5_BIT, true);
    ROM_PWMGenEnable(PWM1_BASE, PWM_GEN_2);

    // Pin G
    PWMGenConfigure(PWM1_BASE, PWM_GEN_3, PWM_GEN_MODE_DOWN);
    PWMGenPeriodSet(PWM1_BASE, PWM_GEN_3, ui32Load);
    ROM_PWMPulseWidthSet(PWM1_BASE, PWM_OUT_6, 1 * ui32Load / 1000);
    ROM_PWMOutputState(PWM1_BASE, PWM_OUT_6_BIT, true);
    ROM_PWMGenEnable(PWM1_BASE, PWM_GEN_3);


    // Pin B
    ROM_PWMPulseWidthSet(PWM1_BASE, PWM_OUT_7, 1 * ui32Load / 1000);
    ROM_PWMOutputState(PWM1_BASE, PWM_OUT_7_BIT, true);

    while(1)
    {
        // Auto mode
        for(i=1;i<=999;i++){
            // Increase G
            ROM_PWMPulseWidthSet(PWM1_BASE, PWM_OUT_7, i * ui32Load / 1000);
            DELAY_MS(1);
        }
        for(i=999;i>=1;i--){
            // Decrease R
            ROM_PWMPulseWidthSet(PWM1_BASE, PWM_OUT_5, i * ui32Load / 1000);
            DELAY_MS(1);
        }
        for(i=1;i<=999;i++){
            // Increase B
            ROM_PWMPulseWidthSet(PWM1_BASE, PWM_OUT_6, i * ui32Load / 1000);
            DELAY_MS(1);
        }
        for(i=999;i>=1;i--){
            // Decrease G
            ROM_PWMPulseWidthSet(PWM1_BASE, PWM_OUT_7, i * ui32Load / 1000);
            DELAY_MS(1);
        }
        for(i=1;i<=999;i++){
            // Increase R
            ROM_PWMPulseWidthSet(PWM1_BASE, PWM_OUT_5, i * ui32Load / 1000);
            DELAY_MS(1);
        }
        for(i=999;i>=1;i--){
            // Decrease B
            ROM_PWMPulseWidthSet(PWM1_BASE, PWM_OUT_6, i * ui32Load / 1000);
            DELAY_MS(1);
        }

        //        ROM_SysCtlDelay(100000);

    }
}
void part2(){
    volatile uint32_t ui32Load;
    volatile uint32_t ui32PWMClock;
    volatile uint8_t ui8Adjust;
    ui8Adjust = 83;
    ROM_SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_OSC_MAIN|SYSCTL_XTAL_16MHZ);
    ROM_SysCtlPWMClockSet(SYSCTL_PWMDIV_64);
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM1);
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    ROM_GPIOPinTypePWM(GPIO_PORTD_BASE, GPIO_PIN_0);
    ROM_GPIOPinConfigure(GPIO_PD0_M1PWM0);
    HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) = GPIO_LOCK_KEY;
    HWREG(GPIO_PORTF_BASE + GPIO_O_CR) |= 0x01;
    HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) = 0;
    ROM_GPIODirModeSet(GPIO_PORTF_BASE, GPIO_PIN_4|GPIO_PIN_0, GPIO_DIR_MODE_IN);
    ROM_GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_4|GPIO_PIN_0, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
    ui32PWMClock = SysCtlClockGet() / 64;
    ui32Load = (ui32PWMClock / PWM_FREQUENCY) - 1;
    PWMGenConfigure(PWM1_BASE, PWM_GEN_0, PWM_GEN_MODE_DOWN);
    PWMGenPeriodSet(PWM1_BASE, PWM_GEN_0, ui32Load);
    ROM_PWMPulseWidthSet(PWM1_BASE, PWM_OUT_0, ui8Adjust * ui32Load / 1000);
    ROM_PWMOutputState(PWM1_BASE, PWM_OUT_0_BIT, true);
    ROM_PWMGenEnable(PWM1_BASE, PWM_GEN_0);
    while(1)
    {
        if(ROM_GPIOPinRead(GPIO_PORTF_BASE,GPIO_PIN_4)==0x00)
        {
            ui8Adjust--;
            if (ui8Adjust < 10)
            {
                ui8Adjust = 10;
            }
            ROM_PWMPulseWidthSet(PWM1_BASE, PWM_OUT_0, ui8Adjust * ui32Load / 1000);
        }
        if(ROM_GPIOPinRead(GPIO_PORTF_BASE,GPIO_PIN_0)==0x00)
        {
            ui8Adjust++;
            if (ui8Adjust > 111)
            {
                ui8Adjust = 111;
            }
            ROM_PWMPulseWidthSet(PWM1_BASE, PWM_OUT_0, ui8Adjust * ui32Load / 1000);
        }
        ROM_SysCtlDelay(100000);

    }
}
int main(void)
{
    part1();
}
void Timer0IntHandler(void)
{
    // Clear the timer interrupt
    TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);

//    Change SW1 state after looking at key press
    switch(sw1State){
    case idle:
        if(detectKey1Press()){
            sw1State = press;
            switch1PressAction();
        }
        else
            sw1State = idle;
        break;
    case press:
            if(detectKey1Press())
                sw1State = release;
            else
                sw1State = idle;
            break;
    case release:
            if(detectKey1Press())
                sw1State = release;
            else
                sw1State = idle;
            break;
    }


//    Change SW2 state after looking at key press
    switch(sw2State){
    case idle:
        if(detectKey2Press()){
            sw2State = press;
            switch2PressAction();
        }
        else
            sw2State = idle;
        break;
    case press:
        if(detectKey2Press())
            sw2State = release;
        else
            sw2State = idle;
        break;
    case release:
        if(detectKey2Press())
            sw2State = release;
        else
            sw2State = idle;
        break;
    }
}

