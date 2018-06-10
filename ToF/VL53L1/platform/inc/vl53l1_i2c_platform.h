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
 * @file   VL53L1_platform.h
 * @brief  Function prototype definitions for Ewok Platform layer.
 *
 */


#ifndef _VL53L1_I2C_PLATFORM_H_
#define _VL53L1_I2C_PLATFORM_H_

#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>

#include "vl53l1_def.h"

#ifdef __cplusplus
extern "C" {
#endif

#define	   I2C                0x01
#define	   SPI                0x00


// initialize I2C
int VL53L1_i2c_init(void);
int VL53L1_write_multi(uint8_t deviceAddress, uint16_t index, uint8_t *pdata, uint32_t count);
int VL53L1_read_multi(uint8_t deviceAddress, uint16_t index, uint8_t *pdata, uint32_t count);
int VL53L1_write_byte(uint8_t deviceAddress, uint16_t index, uint8_t data);
int VL53L1_write_word(uint8_t deviceAddress, uint16_t index, uint16_t data);
int VL53L1_write_dword(uint8_t deviceAddress, uint16_t index, uint32_t data);
int VL53L1_read_byte(uint8_t deviceAddress, uint16_t index, uint8_t *data);
int VL53L1_read_word(uint8_t deviceAddress, uint16_t index, uint16_t *data);
int VL53L1_read_dword(uint8_t deviceAddress, uint16_t index, uint32_t *data);
void VL53L1_get_tick_count(uint32_t *ptick_count_ms);
void VL53L1_delay(uint32_t poll_delay_ms);



#ifdef __cplusplus
}
#endif

#endif //_VL53L1_I2C_PLATFORM_H_

