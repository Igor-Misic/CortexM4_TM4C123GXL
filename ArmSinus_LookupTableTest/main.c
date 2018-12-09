/*==============================================================================
\file
            This file contains the implementation of the \ref UART, ADC, Timer and SPI
            functionality.
            This program is written for ARM CortexM4 (TM4C123GH6PM) microcontroller.
\ingroup    Task
\par        COPYRIGHT (c) 2018-2018 by Igor Misic
            All rights reserved.
\par        File History
\code
Date        Author Scope
--------------------------------------------------------------------------------
2018-12-08  Igor Misic -  Initial version.
===HEADER END=================================================================*/

/*============================================================================*/
/* SECTION: INCLUDES                                                          */
/*============================================================================*/

#include <stdint.h>
#include <stdbool.h>

#include <string.h>
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/debug.h"
#include "driverlib/fpu.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"
#include "driverlib/sysctl.h"
#include "driverlib/timer.h"
#include "driverlib/uart.h"
#include "driverlib/adc.h"
#include "driverlib/ssi.h"
#include "driverlib/systick.h"
#include "utils/uartstdio.h"

#include "math.h"
#include "arm_math.h"

#include "stdio.h"

#define PI 3.14159265

float32_t arm_sin_f32(float32_t);


/*============================================================================*/
/* SECTION: Static variables                                                   */
/*============================================================================*/

static uint32_t volatile s_timeMillisec = 0;
char pstring[sizeof(float)*2+2];


/*============================================================================*/
/* SECTION: Local functions                                                   */
/*============================================================================*/

/*============================================================================*/
/* SECTION: Initialization functions                                          */
/*============================================================================*/

void Uart_Init(void)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);
    UARTClockSourceSet(UART0_BASE, UART_CLOCK_PIOSC);
    UARTStdioConfig(0, 115200, 16000000);
}

/*============================================================================*/
/* SECTION: Interrupt handler  functions                                      */
/*============================================================================*/

/** This is the interrupt handler for the SysTick */

void SycTickCallback()
{
    s_timeMillisec++;
    //UARTprintf("%d\n\r", s_timeMillisec);
}
/** This configures the Systick to interrupt every millisecond */

void SysTickInit()
{
    SysTickPeriodSet(80000);
    SysTickIntRegister(SycTickCallback);
    SysTickIntEnable();
    SysTickEnable();
}


/*============================================================================*/
/* SECTION: Main function                                                     */
/*============================================================================*/

int main(void)
{

    uint32_t timeStart1 = 0;
    uint32_t timeStop1 = 0;

    uint32_t timeStart2 = 0;
    uint32_t timeStop2 = 0;

    uint32_t i = 0;
    float volatile result1 = 0;
    float volatile result2 = 0;

    // Enable processor interrupts.
    IntMasterEnable();

    SysCtlClockSet(SYSCTL_SYSDIV_2_5|SYSCTL_USE_PLL|SYSCTL_OSC_MAIN|SYSCTL_XTAL_16MHZ);

    SysTickInit();
    Uart_Init();

    timeStart1 = s_timeMillisec;

    for(i = 0; i < 100000; i++) {
        result1 = sin(i*PI/180);
        //result2 = arm_sin_f32(i*PI/180);
    }

    timeStop1 = s_timeMillisec;

    timeStart2 = s_timeMillisec;
    for(i = 0; i < 100000; i++) {
        result2 = arm_sin_f32(i*PI/180);
    }
    timeStop2 = s_timeMillisec;

    UARTprintf("Time1:%d\n",timeStop1 - timeStart1);
    UARTprintf("Time2:%d\n",timeStop2 - timeStart2);
    while(1)
    {

        //UARTprintf("Test");
    }

    return result1;
}
