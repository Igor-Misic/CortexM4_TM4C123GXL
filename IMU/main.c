/*==============================================================================
\file
            This file contains the implementation of the \ref UART, ADC, Timer and SPI
            functionality.

            This program is written for ARM CortexM4 (TM4C123GH6PM) microcontroller.

\ingroup    Task
\par        COPYRIGHT (c) 2017-2017 by imisic
            All rights reserved.

\par        File History
\code
Date        Author Scope
--------------------------------------------------------------------------------
2017-01-21  imisic -  Initial version.

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
#include "utils/uartstdio.h"

#include "api.h"
#include "mpu_9250.h"
#include "KX022.h"

/*============================================================================*/
/* SECTION: define                                                            */
/*============================================================================*/
#define KX022       0
#define MPU_9250    1

//Choose accelerometer module
//#define ACCELEROMETR_MODULE KX022
#define ACCELEROMETR_MODULE MPU_9250

#ifdef ACCELEROMETR_MODULE
    #define SPI_FREQ 1000000     // 1  MHz for MPU_9250
#elif
    #define SPI_FREQ 10000000    // 10 MHz for KX022
#endif

#define ASSERT(x,y) //TODO: add assert functionality

/*============================================================================*/
/* SECTION: Static variables                                                   */
/*============================================================================*/

static uint32_t s_timer             = 0;
static uint32_t volatile s_millisec = 0;

static uint32_t s_chargingVoltage   = 0;
static uint32_t s_quiteMinTime      = 0;
static uint32_t s_quietMinMovement  = 0;

static bool     s_isCharging        = false;

/*============================================================================*/
/* SECTION: Local functions                                                   */
/*============================================================================*/

void StartBatteryCharging()
{
    s_isCharging = true;

    //Turn LED On when start charging
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, GPIO_PIN_2);
    //TODO: implement battery start charging
}

void StopBatteryCharging()
{
    s_isCharging = false;

    //Turn LED Off when stop charging
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, 0x0);
    //TODO: implement battery stop charging
}


/** This function will return true if accelerometer is not moving for zz time received from UART*/

bool IsQuiet(uint32_t accelValue)
{
    bool success = false;

    if(accelValue > s_quietMinMovement)
    {
        // if movement detected, reset timer
        s_timer = 0;

        //send voltage and accelerometer value
        UARTprintf("battery:%d, accelerometer:%d\n\r", GetVoltage(), GetAccelValue());
    }

    if(s_timer > s_quiteMinTime)
    {
        //if timer time is bigger then set minimal time, then is quiet
        success = true;
    }

    return success;
}


/** This function looking for commands (keywords) in string */

bool FindCommand(char *string, char *command)
{
    bool success = true;

    uint32_t i = 0;

    if(string[0] == '\0')
    {
        success = false;
    }
    else
    {
        while((string[i] != '\0') && (string[i] != '='))
        {
            if(string[i] != command[i])
            {
                success = false;
            }
            i++;
        }
    }

    return success;
}


/** This function will pars xxxx voltage from "batt=xxxx" command received from UART */

bool ParsingBatteryCommand(char *string, uint32_t *integerVoltage)
{

    bool success = true;
    uint32_t i;

    *integerVoltage = 0;

    // xxxx conversation
    for(i = 0; (i < 4) && (success); i++)
    {
        //protection from non number characters
        if((string[5 + i] >= '0') && (string[5 + i] <= '9'))
        {
            //conversation char to integer
            int32_t digit = string[5 + i] - '0';
            *integerVoltage = *integerVoltage * 10 + digit;
        }
        else
        {
            success = false;
        }
    }

    return success;
}


/** This function will pars yyyy position and zz time from "quiet=yyyy.zz" command received from UART */

bool ParsingAccelerometerCommand(char *string, uint32_t *integerAcceleValue, uint32_t *integerTime)
{
    bool success = true;
    uint32_t i;

    *integerAcceleValue = 0;
    *integerTime        = 0;

    // yyyy conversation
    for(i = 0; (i < 4) && (success); i++)
    {
        //protection from non number characters
        if((string[6 + i] >= '0') && (string[6 + i] <= '9'))
        {
            //conversation from char to integer
            int32_t digit = string[6 + i] - '0';
            *integerAcceleValue = *integerAcceleValue * 10 + digit;
        }
        else
        {
            success = false;
        }
    }

    // zz conversation
    for(i = 0; (i < 2) && (success); i++)
    {
        //protection from non number characters
        if((string[11 + i] >= '0') && (string[11 + i] <= '9'))
        {
            //conversation
            int32_t digit = string[11 + i] - '0';
            *integerTime = *integerTime * 10 + digit;
        }
        else
        {
            success = false;
        }
    }

    return success;
}


/** SPI Write function */

void SPIWriteData(uint8_t address, uint8_t value)
{
    address = address & ~0x80; // Set MSB to 0. It set Read/Write bit to Write.
    SSIDataPut(SSI0_BASE, address);
    SSIDataPut(SSI0_BASE, value);
}


/** SPI Read function */

void SPIReadData(uint8_t address, uint32_t *value)
{
    address = address | 0x80; // Set MSB to 1. It set Read/Write bit to Read.
    SSIDataPut(SSI0_BASE, address);
    SSIDataGet(SSI0_BASE, value);
}


/**  This function works as a delay. It stops the code for the millisecond specified by parameter */

void Delay(uint32_t millisec)
{
    uint32_t temp = s_millisec;
    while( (s_millisec - temp) < millisec)
    {
        //do nothing
    }
}

/*============================================================================*/
/* SECTION: Initialization functions                                          */
/*============================================================================*/

void Uart_Init(void)
{
    // Enable the GPIO Peripheral used by the UART.
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

    // Enable UART0
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);

    // Configure GPIO Pins for UART mode.
    ROM_GPIOPinConfigure(GPIO_PA0_U0RX);
    ROM_GPIOPinConfigure(GPIO_PA1_U0TX);
    ROM_GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    // Use the internal 16MHz oscillator as the UART clock source.
    UARTClockSourceSet(UART0_BASE, UART_CLOCK_PIOSC);

    // Initialize the UART for console I/O.
    UARTStdioConfig(0, 115200, 16000000);

    // Enable the UART interrupt.
    ROM_IntEnable(INT_UART0);
    ROM_UARTIntEnable(UART0_BASE, UART_INT_RX | UART_INT_RT);
}

/** Initialization for 1 second timer */

void Timer_Init(void)
{
    // Enable the peripherals for timer 0.
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);

    // Configure 32-bit periodic timer.
    ROM_TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC);
    ROM_TimerLoadSet(TIMER0_BASE, TIMER_A, ROM_SysCtlClockGet());

    // Setup the interrupts for the timer timeouts for 1 second.
    ROM_IntEnable(INT_TIMER0A);
    ROM_TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);

    // Enable the timers.
    ROM_TimerEnable(TIMER0_BASE, TIMER_A);

}

/** ADC Initialization for analog input 0 */

void Adc_Init(void)
{
    // Enable ADC0 peripheral.
    SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);

    // Enable sample sequence 3 with a processor signal trigger
    ADCSequenceConfigure(ADC0_BASE, 3, ADC_TRIGGER_PROCESSOR, 0);

    // Configure step 0 on sequence 3.  Sample the voltage on analog input
    ADCSequenceStepConfigure(ADC0_BASE, 3, 0, ADC_CTL_CH1 | ADC_CTL_IE | ADC_CTL_END);

    // Enable sequence 3
    ADCSequenceEnable(ADC0_BASE, 3);

    // Clear interrupt status flag
    ADCIntClear(ADC0_BASE, 3);
}

/** Led for charging indication initialization */

void Led_Init(void)
{
    // Enable the GPIO port that is used for the on-board LED.
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);

    // Enable the GPIO pins for the LED (PF2).
    ROM_GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_2);
}

/**
 *  This configures the SSI.
 *  SSI work at 10MHz for KX022 or 1MHz for MPU-9250.
 */

void SPIInit(void)
{
  SysCtlPeripheralEnable(SYSCTL_PERIPH_SSI0);
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

  GPIOPinConfigure(GPIO_PA2_SSI0CLK);   //SPI CLK         - clock
  GPIOPinConfigure(GPIO_PA3_SSI0FSS);   //SPI CS          - chip select
  GPIOPinConfigure(GPIO_PA4_SSI0RX);    //SPI MISO (SDO)  - slave to master
  GPIOPinConfigure(GPIO_PA5_SSI0TX);    //SPI MOSI (SDI)  - master to slave

  GPIOPinTypeSSI(GPIO_PORTA_BASE, GPIO_PIN_5 | GPIO_PIN_4 | GPIO_PIN_3 | GPIO_PIN_2);

  //System clock 80 MHz
  SSIConfigSetExpClk(SSI0_BASE, 80000000, SSI_FRF_MOTO_MODE_0, SSI_MODE_MASTER, SPI_FREQ, 8);

  SSIEnable(SSI0_BASE);
}

/** Initialization of MPU-9250 accelerometer */

void MPU_9250Init(void)
{
    uint8_t     ascale = AFS_2G;
    uint32_t    config = 0;

    // wake up device
    SPIWriteData(PWR_MGMT_1, 0x00); // Clear sleep mode bit (6), enable all sensors
    Delay(100);

    SPIWriteData(PWR_MGMT_1, 0x01); // Auto select clock source to be PLL gyroscope reference if ready else
    Delay(200);

    SPIWriteData(CONFIG, 0x03);
    SPIReadData(CONFIG, &config);

    // Set accelerometer full-scale range configuration


    SPIReadData(ACCEL_CONFIG, &config);             // get current ACCEL_CONFIG register value
    config = config & ~0x18;                        // Clear AFS bits [4:3]
    config = config | ascale << 3;                  // Set full scale range for the accelerometer
    SPIWriteData(ACCEL_CONFIG, config);             // Write new ACCEL_CONFIG register value

    // Set accelerometer sample rate configuration
    // It is possible to get a 4 kHz sample rate from the accelerometer by choosing 1 for
    // accel_fchoice_b bit [3]; in this case the bandwidth is 1.13 kHz
    SPIReadData(ACCEL_CONFIG2, &config); // get current ACCEL_CONFIG2 register value
    config = config & ~0x0F; // Clear accel_fchoice_b (bit 3) and A_DLPFG (bits [2:0])
    config = config | 0x03;  // Set accelerometer rate to 1 kHz and bandwidth to 41 Hz
    SPIWriteData(ACCEL_CONFIG2, config); // Write new ACCEL_CONFIG2 register value

    SPIWriteData(INT_PIN_CFG, 0x22);
    SPIWriteData(INT_ENABLE, 0x01);  // Enable data ready (bit 0) interrupt
}

void KX022Init(void)
{
    uint32_t value;
    SPIReadData(COTR, &value)
    ASSERT(value, 0x55); //check proper integrated circuit functionality.

    SPIWriteData(CNTL1, 0x80); // Set PC1 to 1 to start operating mode.
    Delay(200);
}

/*============================================================================*/
/* SECTION: Interrupt handler  functions                                      */
/*============================================================================*/

/** This is the interrupt handler for the SysTick */

void SycTickCallback()
{
    s_millisec++;
}
/** This configures the Systick to interrupt every millisecond */

void SysTickInit()
{
    SysTickPeriodSet(80000);
    SysTickIntRegister(SycTickCallback);
    SysTickIntEnable();
    SysTickEnable();
}

/** The UART interrupt handler. */

void UARTIntHandler(void)
{
    char battCompString[] = "batt";
    char accelCompString[] = "quiet";

    uint32_t bufferLength   = 20U;
    char buffer[20];

    // Get command from serial port.
    UARTgets(buffer, bufferLength);

    if(('s' == buffer[0] || 'S' == buffer[0]) && (strlen(buffer) == 1))
    {
        UARTprintf("battery:%d, accelerometer:%d\n\r", GetVoltage(), GetAccelValue());
    }
    else if(FindCommand(buffer, battCompString) && (strlen(buffer) < 10)) //check if can find the keyword "batt"
    {
        uint32_t voltage;

        if(ParsingBatteryCommand(buffer, &voltage))
        {
            s_chargingVoltage = voltage;
            //UARTprintf("voltage=%d\n\r", voltage);
        }
    }
    else if(FindCommand(buffer, accelCompString) && (strlen(buffer) < 14)) //check if can find the keyword "quiet"
    {
        uint32_t acceleValue;
        uint32_t time;

        if(ParsingAccelerometerCommand(buffer, &acceleValue, &time))
        {
            //set value to zero. Interrupt will increase it every second by one.
            s_timer = 0;

            s_quiteMinTime     = time;
            s_quietMinMovement = acceleValue;

            //UARTprintf("position=%d, time=%d\n\r", acceleValue, time);
        }
    }
}

/** The Timer interrupt handler. */

void Timer0IntHandler(void)
{
    s_timer++;
    // Clear the timer interrupt.
    ROM_TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
}

/*============================================================================*/
/* SECTION: API functions                                                     */
/*============================================================================*/

/** This function return voltage in digital format from Analog input 0. */

uint32_t GetVoltage()
{
    uint32_t ADCValue;

    // Trigger the ADC conversion.
    ADCProcessorTrigger(ADC0_BASE, 3);

    // Clear the ADC interrupt flag.
    ADCIntClear(ADC0_BASE, 3);

    // Read ADC Value.
    ADCSequenceDataGet(ADC0_BASE, 3, &ADCValue);

    //ADC signal resolution is 4096
    //uint32_t voltage = 4096/ADCValue;
    uint32_t voltage = ADCValue;

    return voltage;
}

/** This function return value from accelerometer */

uint32_t GetAccelValue()
{
    uint32_t valueH;
    uint32_t valueL;
    uint32_t value = 0;

#ifdef ACCELEROMETR_MODULE
    SPIReadData(ACCEL_XOUT_H, &valueH);
    SPIReadData(ACCEL_XOUT_L, &valueL);
#elif
    SPIReadData(XOUTH, &valueH);
    SPIReadData(XOUTL, &valueL);
#endif

    value = valueH << 8;
    value |= valueL;

    // max 16 bit value 65536, we have for digits to compare or MAX value 9999
    // 65536/9999 = 6.55 ~ 7
    return (value/7);
}

/*============================================================================*/
/* SECTION: Main function                                                     */
/*============================================================================*/

int main(void)
{
    // Enable processor interrupts.
    ROM_IntMasterEnable();

    SysCtlClockSet(SYSCTL_SYSDIV_2_5|SYSCTL_USE_PLL|SYSCTL_OSC_MAIN|SYSCTL_XTAL_16MHZ);

    SysTickInit();
    Uart_Init();
    Timer_Init();
    Adc_Init();
    Led_Init();
    SPIInit();

#ifdef ACCELEROMETR_MODULE
    MPU_9250Init();
#elif
    KX022Init();
#endif

    while(1)
    {
        uint32_t accelValue = GetAccelValue();

        //UARTprintf("acell:%d\n\r", accelXoutValue);


        if((!s_isCharging) && (s_chargingVoltage > GetVoltage()) && IsQuiet(accelValue))
        {
            StartBatteryCharging();
        }
        else if(s_isCharging && ((s_chargingVoltage <= GetVoltage()) || !(IsQuiet(accelValue))))
        {
            StopBatteryCharging();
        }
    }
}
