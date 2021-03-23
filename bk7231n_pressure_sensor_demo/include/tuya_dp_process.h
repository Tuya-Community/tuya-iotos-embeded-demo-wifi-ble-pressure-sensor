/**
 * @File: tuya_dp_process.h 
 * @Author: huanling.zhang@tuya.com 
 * @Last Modified time: 2021-03-13 
 * @Description: pressure detection demo 
 */

#ifndef __TUYA_DP_PROCESS_H_
#define __TUYA_DP_PROCESS_H_

#include "tuya_cloud_com_defs.h"
#include "tuya_cloud_types.h"

#define         NORMAL          1
#define         ALARM           0

#define         LOW             2
#define         MEDUIM          1
#define         HIGH            0

/*压力状态*/
typedef enum {
    alarm = 0,
    normal,
}PRESS_STA_E;

/*压力强度*/
typedef enum {
    high = 0,
    meduim,
    low
}PRESS_VAL;

//设备状态结构体
typedef struct {
    UCHAR_T pressure_sta;
    UCHAR_T last_pressure_sta;
    UCHAR_T pressure_val;
}pressure_detection_S;


extern pressure_detection_S pressure_sensor_status;

VOID updata_dp_all(VOID);
VOID dp_process(IN CONST TY_OBJ_DP_S *root);


#endif




