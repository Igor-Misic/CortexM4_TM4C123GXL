#include <stdint.h>
#include <stdbool.h>

#include "inc/hw_i2c.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_gpio.h"
#include "driverlib/i2c.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"

#include "vl53l1_i2c_platform.h"
#include "vl53l1_def.h"

//initialize I2C module 0
int VL53L1_i2c_init(void)
{
    //enable I2C module 0
    SysCtlPeripheralEnable(SYSCTL_PERIPH_I2C0);

    //reset module
    SysCtlPeripheralReset(SYSCTL_PERIPH_I2C0);

    //enable GPIO peripheral that contains I2C 0
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);

    // Configure the pin muxing for I2C0 functions on port B2 and B3.
    GPIOPinConfigure(GPIO_PB2_I2C0SCL);
    GPIOPinConfigure(GPIO_PB3_I2C0SDA);

    // Select the I2C function for these pins.
    GPIOPinTypeI2CSCL(GPIO_PORTB_BASE, GPIO_PIN_2);
    GPIOPinTypeI2C(GPIO_PORTB_BASE, GPIO_PIN_3);

    // Enable and initialize the I2C0 master module.  Use the system clock for
    // the I2C0 module.  The last parameter sets the I2C data transfer rate.
    // If false the data rate is set to 100kbps and if true the data rate will
    // be set to 400kbps.
    I2CMasterInitExpClk(I2C0_BASE, SysCtlClockGet(), true);

    //clear I2C FIFOs
    HWREG(I2C0_BASE + I2C_O_FIFOCTL) = 80008000;

    return VL53L1_ERROR_NONE;
}

int VL53L1_write_multi(uint8_t deviceAddress, uint16_t index, uint8_t *pdata, uint32_t count) {

  // Tell the master module what address it will place on the bus when
  // communicating with the slave.
  I2CMasterSlaveAddrSet(I2C0_BASE, deviceAddress, false);

  //put data to be sent into FIFO
  I2CMasterDataPut(I2C0_BASE,  ((index >> 8) & 0xFF)); //index-> device register

  //Initiate send of data from the MCU
  I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_SEND_START);
  while(I2CMasterBusy(I2C0_BASE));

  //put data to be sent into FIFO
  I2CMasterDataPut(I2C0_BASE, index & 0xFF);

  //Initiate send of data from the MCU
  I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_SEND_CONT);
  while(I2CMasterBusy(I2C0_BASE));


  if( 1 == count)
  {
      //put data to be sent into FIFO
      I2CMasterDataPut(I2C0_BASE, pdata[0]);
      //send next data that was just placed into FIFO
      I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_SEND_FINISH);
      // Wait until MCU is done transferring.
      while(I2CMasterBusy(I2C0_BASE));
  }
  else
  {

      while(count > 1)
      {
          //put data to be sent into FIFO
          I2CMasterDataPut(I2C0_BASE, pdata[0]);

          //Initiate send of data from the MCU
          I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_SEND_CONT);
          while(I2CMasterBusy(I2C0_BASE));
          count--;
          pdata++;
      }

      I2CMasterDataPut(I2C0_BASE, pdata[0]);
      //send next data that was just placed into FIFO
      I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_SEND_FINISH);
      // Wait until MCU is done transferring.
      while(I2CMasterBusy(I2C0_BASE));
  }

  return VL53L1_ERROR_NONE;
}

int VL53L1_read_multi(uint8_t deviceAddress, uint16_t index, uint8_t *pdata, uint32_t count) {

    //specify that we are writing (a register address) to the
    //slave device
    I2CMasterSlaveAddrSet(I2C0_BASE, deviceAddress, false);

    //specify register to be read
    I2CMasterDataPut(I2C0_BASE, ((index >> 8) & 0xFF));

    I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_SEND_START);

    //wait for MCU to finish transaction
    while(I2CMasterBusy(I2C0_BASE));

    I2CMasterDataPut(I2C0_BASE, index & 0xFF);

    I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_SEND_FINISH);


    //wait for MCU to finish transaction
    while(I2CMasterBusy(I2C0_BASE));

    //specify that we are going to read from slave device
    I2CMasterSlaveAddrSet(I2C0_BASE, deviceAddress, true);

    if(1 == count)
    {
        I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_SINGLE_RECEIVE);
        while(I2CMasterBusy(I2C0_BASE));
        pdata[0] = I2CMasterDataGet(I2C0_BASE);
    }
    else
    {
        //send control byte and read from the register we
        //specified
        I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_RECEIVE_START);
        while(I2CMasterBusy(I2C0_BASE));
        pdata[0] = I2CMasterDataGet(I2C0_BASE);
        pdata++;

        while(count > 2)
        {
          I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_RECEIVE_CONT);
          while(I2CMasterBusy(I2C0_BASE));
          pdata[0] = I2CMasterDataGet(I2C0_BASE);
          pdata++;
          count--;
        }

        I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_RECEIVE_FINISH);

        while(I2CMasterBusy(I2C0_BASE));
        pdata[0] = I2CMasterDataGet(I2C0_BASE);
    }

    return VL53L1_ERROR_NONE;
}

int VL53L1_write_byte(uint8_t deviceAddress, uint16_t index, uint8_t data) {
  return VL53L1_write_multi(deviceAddress, index, &data, 1);
}

int VL53L1_write_word(uint8_t deviceAddress, uint16_t index, uint16_t data) {
  uint8_t buff[2];
  buff[1] = data & 0xFF;
  buff[0] = data >> 8;
  return VL53L1_write_multi(deviceAddress, index, buff, 2);
}

int VL53L1_write_dword(uint8_t deviceAddress, uint16_t index, uint32_t data) {
  uint8_t buff[4];

  buff[3] = data & 0xFF;
  buff[2] = data >> 8;
  buff[1] = data >> 16;
  buff[0] = data >> 24;

  return VL53L1_write_multi(deviceAddress, index, buff, 4);
}

int VL53L1_read_byte(uint8_t deviceAddress, uint16_t index, uint8_t *data) {
  return VL53L1_read_multi(deviceAddress, index, data, 1);
}

int VL53L1_read_word(uint8_t deviceAddress, uint16_t index, uint16_t *data) {
  uint8_t buff[2];
  int retValue = VL53L1_read_multi(deviceAddress, index, buff, 2);

  uint16_t tmp;
  tmp = buff[0];
  tmp <<= 8;
  tmp |= buff[1];
  *data = tmp;

  return retValue;
}

int VL53L1_read_dword(uint8_t deviceAddress, uint16_t index, uint32_t *data) {
  uint8_t buff[4];
  int retValue = VL53L1_read_multi(deviceAddress, index, buff, 4);

  uint32_t tmp;
  tmp = buff[0];
  tmp <<= 8;
  tmp |= buff[1];
  tmp <<= 8;
  tmp |= buff[2];
  tmp <<= 8;
  tmp |= buff[3];

  *data = tmp;

  return retValue;
}

void VL53L1_get_tick_count(uint32_t *ptick_count_ms)
{
    *ptick_count_ms = SysCtlClockGet();
}

void VL53L1_delay(uint32_t poll_delay_ms)
{
    SysCtlDelay(poll_delay_ms);
}

