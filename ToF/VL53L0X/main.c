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

#include "vl53l0x_api.h"
#include "vl53l0x_platform.h"

VL53L0X_Error rangingTest(VL53L0X_Dev_t *pMyDevice)
{
    VL53L0X_Error Status = VL53L0X_ERROR_NONE;
    VL53L0X_RangingMeasurementData_t    RangingMeasurementData;
    int i;
    FixPoint1616_t LimitCheckCurrent;
    uint8_t VhvSettings;
    uint8_t PhaseCal;

    if(Status == VL53L0X_ERROR_NONE)
    {
        Status = VL53L0X_StaticInit(pMyDevice); // Device Initialization
    }

    if(Status == VL53L0X_ERROR_NONE)
    {
        Status = VL53L0X_PerformRefCalibration(pMyDevice,
                &VhvSettings, &PhaseCal); // Device Initialization
    }

    if(Status == VL53L0X_ERROR_NONE)
    {
        //Status = VL53L0X_PerformRefSpadManagement(pMyDevice,
         //       &refSpadCount, &isApertureSpads); // Device Initialization
    }

    if(Status == VL53L0X_ERROR_NONE)
    {

        // no need to do this when we use VL53L0X_PerformSingleRangingMeasurement
        Status = VL53L0X_SetDeviceMode(pMyDevice, VL53L0X_DEVICEMODE_SINGLE_RANGING); // Setup in single ranging mode
    }

    // Enable/Disable Sigma and Signal check
    if (Status == VL53L0X_ERROR_NONE) {
        Status = VL53L0X_SetLimitCheckEnable(pMyDevice,
                VL53L0X_CHECKENABLE_SIGMA_FINAL_RANGE, 1);
    }
    if (Status == VL53L0X_ERROR_NONE) {
        Status = VL53L0X_SetLimitCheckEnable(pMyDevice,
                VL53L0X_CHECKENABLE_SIGNAL_RATE_FINAL_RANGE, 1);
    }

    if (Status == VL53L0X_ERROR_NONE) {
        Status = VL53L0X_SetLimitCheckValue(pMyDevice,
                VL53L0X_CHECKENABLE_SIGNAL_RATE_FINAL_RANGE,
                (FixPoint1616_t)(0.25*65536));
    }
    if (Status == VL53L0X_ERROR_NONE) {
        Status = VL53L0X_SetLimitCheckValue(pMyDevice,
                VL53L0X_CHECKENABLE_SIGMA_FINAL_RANGE,
                (FixPoint1616_t)(32*65536));
    }
    if (Status == VL53L0X_ERROR_NONE) {
        Status = VL53L0X_SetMeasurementTimingBudgetMicroSeconds(pMyDevice,
                30000);
    }

    /*
     *  Step  4 : Test ranging mode
     */

    if(Status == VL53L0X_ERROR_NONE)
    {
        for(i=0;i<10;i++){
            Status = VL53L0X_PerformSingleRangingMeasurement(pMyDevice,
                    &RangingMeasurementData);


            VL53L0X_GetLimitCheckCurrent(pMyDevice,
                    VL53L0X_CHECKENABLE_RANGE_IGNORE_THRESHOLD, &LimitCheckCurrent);



            if (Status != VL53L0X_ERROR_NONE) break;



        }
    }
    return Status;
}

int main(void)
{

    static volatile VL53L0X_RangingMeasurementData_t rangingMeasurementData;

    uint8_t address = 0x52;

    VL53L0X_Dev_t device;
    VL53L0X_Dev_t *ptrDevice = &device;
    VL53L0X_Version_t version;
    VL53L0X_Version_t *ptrVersion = &version;
    VL53L0X_DeviceInfo_t deviceInfo;

    ptrDevice->I2cDevAddr = address >> 1;
    ptrDevice->comms_type = 1;
    ptrDevice->comms_speed_khz = 400;

    VL53L0X_i2c_init();

    VL53L0X_GetVersion(ptrVersion);
    VL53L0X_DataInit( &device ); // Data initialization
    VL53L0X_GetDeviceInfo(&device, &deviceInfo);

    /*
    address &= 0x7F;
    status = VL53L0X_SetDeviceAddress(ptrDevice, address * 2);// 7->8 bit
    ptrDevice->I2cDevAddr = address;
    */

    while(true)
    {
        rangingTest(ptrDevice);
        //status = VL53L0X_PerformSingleRangingMeasurement( ptrDevice, &rangingMeasurementData );
    }

	return 0;
}
