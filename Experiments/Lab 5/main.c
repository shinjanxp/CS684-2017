/*
 * Lab 5 : Sample Code
 * Course : CS-684
 * Created on: Jan 27, 2018
 * Author: Lab staff ERTS LAB
 * This sample code will help you in interfacing glcd 
 */

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "inc/tm4c123gh6pm.h"
#include "driverlib/debug.h"
#include "driverlib/pin_map.h"
#include "inc/hw_gpio.h"
#include "driverlib/rom.h"
#include "driverlib/adc.h"
#include "glcd.h"
#include "logo.h"
#include "mickey.h"
#include "leopard.h"

#define DELAY_MS(x) SysCtlDelay(6700000/500*x)

volatile uint32_t ui32JoyStickValue[2];
uint32_t ui32ADC0Value[4];

uint32_t prev_x=0,prev_y=0;
void display_image(const unsigned char* image){
    int j=0,p=0,i=0;
    while(p<8){
        // Set the page
        glcd_setpage(p);

        for(i=0;i<128;i++){
            // Select columns from 0 to 127
            glcd_setcolumn(i);

            // Send the hex values to GLCD
            glcd_data(image[j]);
            j++;
        }

        // Increment page number
        p++;
    }
}
void display_box(uint32_t x, uint32_t y){

    int i=0;
    if(x== prev_x && y == prev_y) return;

    // clear prev box
    glcd_setpage(prev_y);
    glcd_setcolumn(prev_x); //Scale between 0 to 120 not 128

    //Print 8x8 box
    for(i=0;i<8;i++){
        glcd_data(0x00);
    }
    glcd_setpage(y);
    glcd_setcolumn(x); //Scale between 0 to 120 not 128

    //Print 8x8 box
    for(i=0;i<8;i++){
        glcd_data(0xFF);
    }
    prev_x=x;prev_y=y;
}
void pin_config(){

    SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_OSC_MAIN|SYSCTL_XTAL_16MHZ);

    /* Enable all the peripherals */
    /* PORTS A,E,F,C,D,B */
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);


    /* Unlock pin PF0 */
    HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK)= GPIO_LOCK_KEY;    // unlocking sw2 switch
    HWREG(GPIO_PORTF_BASE + GPIO_O_CR) |= 0x01;
    HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK)= 0;

    /* Configure Enable pin as output */
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_0);


    /*This ensures buzzer remains OFF, since PC4 when logic 0 turns ON buzzer */
    GPIOPinTypeGPIOOutput(GPIO_PORTC_BASE, GPIO_PIN_4);
    GPIOPinWrite(GPIO_PORTC_BASE,GPIO_PIN_4,16);

    /* Configure PE5 (RST), PE0 to PE3 (D0 to D3) and PB4 to PB7(D4 to D7) as output pins */
    GPIOPinTypeGPIOOutput(GPIO_PORTE_BASE, GPIO_PIN_5);

    GPIOPinTypeGPIOOutput(GPIO_PORTE_BASE, GPIO_PIN_0);
    GPIOPinTypeGPIOOutput(GPIO_PORTE_BASE, GPIO_PIN_1);
    GPIOPinTypeGPIOOutput(GPIO_PORTE_BASE, GPIO_PIN_2);
    GPIOPinTypeGPIOOutput(GPIO_PORTE_BASE, GPIO_PIN_3);

    GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE, GPIO_PIN_4);
    GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE, GPIO_PIN_5);
    GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE, GPIO_PIN_6);
    GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE, GPIO_PIN_7);

    /* Configure RS as output */
    GPIOPinTypeGPIOOutput(GPIO_PORTC_BASE, GPIO_PIN_6);


    /* Configure CS1 or CS2 as output */
    GPIOPinTypeGPIOOutput(GPIO_PORTD_BASE, GPIO_PIN_3);

    //ADC config
    SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);

    GPIOPinTypeADC(GPIO_PORTD_BASE, GPIO_PIN_0 | GPIO_PIN_1);
}
void part1(){
    pin_config();
    display_image(mickey);
}
void part2(){
    pin_config();
    //ADC stuff
    ADCSequenceConfigure(ADC0_BASE, 1, ADC_TRIGGER_PROCESSOR, 0);
    ADCSequenceStepConfigure(ADC0_BASE, 1, 0, ADC_CTL_CH7|ADC_CTL_IE);
    ADCSequenceStepConfigure(ADC0_BASE, 1, 1, ADC_CTL_CH6|ADC_CTL_IE|ADC_CTL_END);
    ADCSequenceEnable(ADC0_BASE, 1);

    /*initialize glcd*/
    glcd_init();
    glcd_cleardisplay();


    while(1)
    {


        ADCIntClear(ADC0_BASE, 1);
        ADCProcessorTrigger(ADC0_BASE, 1);

        while(!ADCIntStatus(ADC0_BASE, 1, false))
        {
        }
        ADCSequenceDataGet(ADC0_BASE, 1, ui32ADC0Value);
        ui32JoyStickValue[0] = ui32ADC0Value[1]/34;
        ui32JoyStickValue[1] = ui32ADC0Value[0]/512;
        display_box(ui32JoyStickValue[0], ui32JoyStickValue[1]);
        DELAY_MS(10);

    }
}
part3(){
    pin_config();
    while(1){
        display_image(one);
//        glcd_cleardisplay();
        display_image(two);
//        glcd_cleardisplay();
        display_image(three);
//        glcd_cleardisplay();
        display_image(four);
//        glcd_cleardisplay();
        display_image(five);
//        glcd_cleardisplay();
        display_image(six);
//        glcd_cleardisplay();
        display_image(seven);
//        glcd_cleardisplay();
        display_image(eight);
//        glcd_cleardisplay();
    }
}
int main()
{
    part3();

}
