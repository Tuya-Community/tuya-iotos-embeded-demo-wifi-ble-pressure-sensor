/**
 * @File: tuya_pressure.h 
 * @Author: huanling.zhang@tuya.com 
 * @Last Modified time: 2021-03-13 
 * @Description: pressure detection demo 
 */
#ifndef __TUYA_PRESSURE_H__
#define __TUYA_PRESSURE_H__

#include "tuya_cloud_types.h"
#include "tuya_gpio.h"

#define PRESSURE_SENSOR_PIN    TY_GPIOA_20


VOID pressure_sensor_init(VOID);
INT_T adc_value_get(VOID);
VOID check_pressure_task(VOID);




#endif
