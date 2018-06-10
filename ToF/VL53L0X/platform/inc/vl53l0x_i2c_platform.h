/*
 * COPYRIGHT (C) STMicroelectronics 2014. All rights reserved.
 *
 * This software is the confidential and proprietary information of
 * STMicroelectronics ("Confidential Information").  You shall not
 * disclose such Confidential Information and shall use it only in
 * accordance with the terms of the license agreement you entered into
 * with STMicroelectronics
 *
 * Programming Golden Rule: Keep it Simple!
 *
 */

/**
 * @file   VL53L0X_platform.h
 * @brief  Function prototype definitions for Ewok Platform layer.
 *
 */


#ifndef _VL53L0X_I2C_PLATFORM_H_
#define _VL53L0X_I2C_PLATFORM_H_

#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_i2c.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_gpio.h"
#include "driverlib/i2c.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"

#include "vl53l0x_def.h"

#ifdef __cplusplus
extern "C" {
#endif

#define	   I2C                0x01
#define	   SPI                0x00


// initialize I2C
int VL53L0X_i2c_init(void);
int VL53L0X_write_multi(uint8_t deviceAddress, uint8_t index, uint8_t *pdata, uint32_t count);
int VL53L0X_read_multi(uint8_t deviceAddress, uint8_t index, uint8_t *pdata, uint32_t count);
int VL53L0X_write_byte(uint8_t deviceAddress, uint8_t index, uint8_t data);
int VL53L0X_write_word(uint8_t deviceAddress, uint8_t index, uint16_t data);
int VL53L0X_write_dword(uint8_t deviceAddress, uint8_t index, uint32_t data);
int VL53L0X_read_byte(uint8_t deviceAddress, uint8_t index, uint8_t *data);
int VL53L0X_read_word(uint8_t deviceAddress, uint8_t index, uint16_t *data);
int VL53L0X_read_dword(uint8_t deviceAddress, uint8_t index, uint32_t *data);


#ifdef __cplusplus
}
#endif

#endif //_VL53L0X_I2C_PLATFORM_H_

