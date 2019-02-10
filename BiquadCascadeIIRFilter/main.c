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
#include "driverlib/systick.h"
#include "utils/uartstdio.h"

#include "arm_math.h"

#include "math.h"

#include "stdio.h"

#define PI          (3.14159265)
#define NUM_STAGES  (2u)


/*============================================================================*/
/* SECTION: Static variables                                                   */
/*============================================================================*/
static arm_biquad_casd_df1_inst_f32 filter;
static float32_t state[4U * NUM_STAGES * sizeof(float32_t)] = {0.0};
static const uint32_t blockSize = 1u;


/* Coefficients from  Iowa Hills IIR Filter Designer



Sect 0
a0   1.000000000000000000       //this is not going to be used
a1   -1.994200154319587750      //reverse polarity
a2   0.998018324583265337       //reverse polarity
b0   -0.001424095246338581
b1   0.000000000000000000
b2   0.001424095246338581

Sect 1
a0   1.000000000000000000       //this is not going to be used
a1   -1.993882842053027240      //reverse polarity
a2   0.997953858972972396       //reverse polarity
b0   -0.001424003258880126
b1   0.000000000000000000
b2   0.001424003258880126
*/

static float32_t coeffs[] = { -0.001424095246338581, 0.000000000000000000, 0.001424095246338581, 1.994200154319587750, -0.998018324583265337,
                              -0.001424003258880126, 0.000000000000000000, 0.001424003258880126, 1.993882842053027240, -0.997953858972972396};

static uint32_t volatile s_timeMillisec = 0;

/*============================================================================*/
/* SECTION: Interrupt handler  functions                                      */
/*============================================================================*/

/** This is the interrupt handler for the SysTick */

void SycTickCallback()
{
    s_timeMillisec++;


    static float sinus1, sinus2, sinusIn, sinusOut, dcOffset, amplifier;
    static uint32_t i = 0;

    dcOffset = 10;
    amplifier = 10;

    sinus1 = dcOffset+amplifier*sin(3.6*i*PI/180);      // 1 Hz
    sinus2= sin(i*10000*PI/180);                        // 2777 Hz
    sinusIn = sinus1+sinus2;

    arm_biquad_cascade_df1_f32(&filter, &sinusIn, &sinusOut, blockSize);

    UARTprintf("%d,%d\n", (int)(1000*sinusIn), (int)(1000*sinusOut));
    i++;
}

/** This configures the Systick to interrupt every 10 millisecond */
void SysTickInit()
{
    SysTickPeriodSet(80000*10);
    SysTickIntRegister(SycTickCallback);
    SysTickIntEnable();
    SysTickEnable();
}

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
/* SECTION: Main function                                                     */
/*============================================================================*/

void main(void)
{
    // Enable processor interrupts.
    IntMasterEnable();

    SysCtlClockSet(SYSCTL_SYSDIV_2_5|SYSCTL_USE_PLL|SYSCTL_OSC_MAIN|SYSCTL_XTAL_16MHZ);

    SysTickInit();
    Uart_Init();

    arm_biquad_cascade_df1_init_f32(&filter, NUM_STAGES, coeffs, state);

    while(1)
    {
    }
}
