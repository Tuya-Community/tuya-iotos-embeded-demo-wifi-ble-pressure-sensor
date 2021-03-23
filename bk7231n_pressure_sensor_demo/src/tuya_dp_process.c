/**
 * @File: tuya_app_dp_process.c 
 * @Author: huanling.zhang@tuya.com 
 * @Last Modified time: 2021-03-13 
 * @Description: pressure detection demo 
 */

#include "tuya_dp_process.h"
#include "tuya_iot_com_api.h"
#include "uni_log.h"
//#include "integer.h"

//设备DPID
#define DPID_PRESSURE_STATE         1
#define DPID_PRESSURE_INTENSITY     101

//extern INT adc_value_get(VOID);

pressure_detection_S pressure_sensor_status = {
    .pressure_sta = NORMAL,
    .last_pressure_sta = ALARM,
    .pressure_val = LOW
};


 /***********************************************************
 *   Function:  dp_process
 *   Input:     none
 *   Output:    none
 *   Return:    none
 *   Notice:    处理 dp 数据 
 ***********************************************************/
VOID dp_process(IN CONST TY_OBJ_DP_S *root)
{
    UCHAR_T dpid;

    dpid = root->dpid;
    PR_DEBUG("dpid:%d",dpid);

    return;
}

 /***********************************************************
 *   Function:  updata_dp_all
 *   Input:     none
 *   Output:    none
 *   Return:    none
 *   Notice:    上报所有 dp 
 ***********************************************************/
VOID updata_dp_all(VOID)
{
    OPERATE_RET op_ret = OPRT_OK;

    INT_T dp_cnt = 0;
    dp_cnt = 2;
    INT_T press_val;
    press_val = adc_value_get();

    TY_OBJ_DP_S *dp_arr = (TY_OBJ_DP_S *)Malloc(dp_cnt*SIZEOF(TY_OBJ_DP_S));
    if(NULL == dp_arr) {
        PR_ERR("malloc failed");
        return;
    }

    memset(dp_arr, 0, dp_cnt*SIZEOF(TY_OBJ_DP_S));
    
    //过滤相同DP上报
    if (pressure_sensor_status.pressure_sta == pressure_sensor_status.last_pressure_sta) {
        Free(dp_arr);
        return;
    } else {
        pressure_sensor_status.last_pressure_sta = pressure_sensor_status.pressure_sta;
    }

    if(press_val >= 0 && press_val <= 0x274) {
        pressure_sensor_status.pressure_val = LOW;
    } else if(press_val > 0x274 && press_val <= 0x554) {
        pressure_sensor_status.pressure_val = MEDUIM;
    } else {
        pressure_sensor_status.pressure_val = HIGH;
    }
    dp_arr[0].dpid = DPID_PRESSURE_STATE;
    dp_arr[0].type = PROP_ENUM;
    dp_arr[0].time_stamp = 0;
    dp_arr[0].value.dp_enum = pressure_sensor_status.pressure_sta;

    dp_arr[1].dpid = DPID_PRESSURE_INTENSITY;
    dp_arr[1].type = PROP_ENUM;
    dp_arr[1].time_stamp = 0;
    dp_arr[1].value.dp_enum = pressure_sensor_status.pressure_val;
    op_ret = dev_report_dp_json_async(NULL ,dp_arr,dp_cnt);
    Free(dp_arr);
    if(OPRT_OK != op_ret) {
        PR_ERR("dev_report_dp_json_async relay_config data error,err_num",op_ret);
    }

    PR_DEBUG("dp_query report_all_dp_data");
    
    return;
}

