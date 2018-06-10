#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>


#include "vl53l1_api.h"
#include "vl53l1_platform.h"

int main(void)
{
    VL53L1_Error status = VL53L1_ERROR_NOT_SUPPORTED;

    uint8_t address = 0x52;

    VL53L1_Dev_t device;
    VL53L1_Dev_t *ptrDevice = &device;

    ptrDevice->I2cDevAddr = address >> 1;
    ptrDevice->comms_type = 1;
    ptrDevice->comms_speed_khz = 400;

    VL53L1_i2c_init();

    status = VL53L1_WaitDeviceBooted(ptrDevice);
    status = VL53L1_DataInit(ptrDevice);
    status = VL53L1_StaticInit(ptrDevice);
    status = VL53L1_SetDistanceMode(ptrDevice, VL53L1_DISTANCEMODE_LONG);
    status = VL53L1_SetMeasurementTimingBudgetMicroSeconds(ptrDevice, 50000);
    status = VL53L1_SetInterMeasurementPeriodMilliSeconds(ptrDevice, 500);
    status = VL53L1_StartMeasurement(ptrDevice);

    while(true)
    {
        static VL53L1_RangingMeasurementData_t RangingData;

        status = VL53L1_WaitMeasurementDataReady(ptrDevice);
        if(!status)
        {
          status = VL53L1_GetRangingMeasurementData(ptrDevice, &RangingData);
          if(status==0)
          {
              printf("%d", &(RangingData.RangeMilliMeter));
          }
          status = VL53L1_ClearInterruptAndStartMeasurement(ptrDevice);
        }
    }
    return 0;
}
