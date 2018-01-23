#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include "inc/tm4c123gh6pm.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "driverlib/interrupt.h"
#include "driverlib/gpio.h"
#include "driverlib/timer.h"
#include "inc/hw_gpio.h"
//#include "inc/hw_ints.h"
/**
 * main.c
 */
#define DELAY_MS(x) (SysCtlDelay(6700000/500*x))
#define DELAY_US(x) (SysCtlDelay(6700000/500000*x))

int flag=0,sw2Status=0;
uint8_t ui8PinData=2;
bool sw1Activation=0, sw2Activation=0;

enum state{
    idle,
    press,
    release
};

enum state sw1State, sw2State;
void pin_config(void)
{

    HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) = GPIO_LOCK_KEY;   // unlock the GPIOCR register for port F
    HWREG(GPIO_PORTF_BASE + GPIO_O_CR) = 0x01;      // Free up pin 0
    HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK)= 0 ;

    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);
    GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_0|GPIO_PIN_4);
    GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_0|GPIO_PIN_4, GPIO_STRENGTH_8MA, GPIO_PIN_TYPE_STD_WPU);

}
int main(void)
{
    uint32_t ui32Period;
    sw1State = idle;

    SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    pin_config();

    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
    TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC);

    ui32Period = (SysCtlClockGet() / 10) / 2;
    TimerLoadSet(TIMER0_BASE, TIMER_A, ui32Period -1);

    IntEnable(INT_TIMER0A);
    TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
    IntMasterEnable();
    TimerEnable(TIMER0_BASE, TIMER_A);

    while(1){
        // Turn on the LED
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, ui8PinData);
        // Delay for a bit
        DELAY_MS(500);
        // Turn off LED
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, 0);
        // Delay
        DELAY_MS(500);

    }
    return 0;
}
unsigned char detectKey1Press()
{
    sw1Activation = !GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_4); // Since SW1 is pull-up, negation of value is status, i.e. if pin in HIGH then switch is not pressed
    if(sw1Activation){
        flag=1;
    }
    else {
        flag=0;
    }
    return flag;
}

void switch1PressAction(){
    if(ui8PinData==8) {ui8PinData=2;} else {ui8PinData=ui8PinData*2;}
}
void switch1ReleaseAction(){
}
//Switch2
unsigned char detectKey2Press()
{
    sw2Activation = !GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_0); // Since SW1 is pull-up, negation of value is status, i.e. if pin in HIGH then switch is not pressed
    if(sw2Activation){
        flag=1;
    }
    else {
        flag=0;
    }
    return flag;
}
void switch2PressAction(){
    sw2Status++;
}
void switch2ReleaseAction(){
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
