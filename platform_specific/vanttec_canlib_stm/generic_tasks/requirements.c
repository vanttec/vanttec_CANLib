/*
 * requirements.c
 *
 *  Created on: May 22, 2023
 *      Author: Z0180064
 */

#include "main.h"
#include "vanttec_canlib_generic_ids.h"
#include "vanttec_canlib_tx_task.h"
#include "vanttec_canlib_rx_task.h"
#include "cmsis_os.h"
#include <stddef.h>
osThreadId_t emergencystopTaskHandle;
const osThreadAttr_t emergencystopTaskAttributes = {
    .name = "emergencystop",
    .stack_size = 128 * 4};
osThreadId_t hbTaskHandle;
const osThreadAttr_t hbTaskAttributes = {
    .name = "canlib_hb",
    .stack_size = 128 * 1};
osThreadId_t drivemodeTaskHandle;
const osThreadAttr_t drivemodeTaskAttributes = {
    .name = "drivemode",
    .stack_size = 128 * 4};
osThreadId_t driverpresentTaskHandle;
const osThreadAttr_t driverpresentTaskAttributes = {
    .name = "driverpresent",
    .stack_size = 128 * 4};
osThreadId_t reverseTaskHandle;
const osThreadAttr_t reverseTaskAttributes = {
    .name = "reserve",
    .stack_size = 128 * 4};
osThreadId_t frenomanualTaskHandle;
const osThreadAttr_t frenomanualTaskAttributes = {
    .name = "frenomanual",
    .stack_size = 128 * 4};
osThreadId_t driverfaultTaskHandle;
const osThreadAttr_t driverfaultTaskAttributes = {
    .name = "driverfault",
    .stack_size = 128 * 4};

void emergencystop_task(void *args)
{
    uint8_t buf[8];
    uint8_t emergencystop_data = 0;
    uint8_t last_emergencystop_data = 0;
    register_canlib_rx(VANTTEC_CAN_ID_JETSON, VANTTEC_CAN_ID_ESTOP, VANTTEC_CANLIB_BYTE, &emergencystop_data, 1);
    for (;;)
    {
        if (emergencystop_data != last_emergencystop_data)
        {
            buf[0] = 0x07;
            buf[1] = 0x0;
            if (emergencystop_data == 1)
            {
                buf[1] = 0x1;
            }
            last_emergencystop_data = emergencystop_data;
            update_table(VANTTEC_CAN_ID_PANELRX, 0x07, buf, 2);
        }
        osDelay(10);
    }
}
void hb_task(void *args)
{
    uint8_t data = 0;
    for (;;)
    {
        canlib_send_debug_string("Hello");
        canlib_send_byte(VANTTEC_CAN_ID_HB, data);
        data++;
        osDelay(1000);
    }
}
void drivemode_task(void *args)
{
    uint8_t buf[8];
    uint8_t drivemode_data = 0;
    uint8_t last_drivemode_data = 0;
    register_canlib_rx(VANTTEC_CAN_ID_JETSON, VANTTEC_CAN_ID_DRIVE_MODE, VANTTEC_CANLIB_BYTE, &drivemode_data, 1);
    for (;;)
    {
        if (drivemode_data != last_drivemode_data)
        {
            buf[0] = 0x07;
            buf[1] = 0x0;
            if (drivemode_data == 1)
            {
                buf[1] = 0x1;
            }
            last_drivemode_data = drivemode_data;
            update_table(VANTTEC_CAN_ID_PANELRX, 0x07, buf, 2);
        }
        osDelay(10);
    }
}
void driverpresent_task(void *args)
{
    uint8_t buf[8];
    uint8_t driverpresent_data = 0;
    uint8_t last_driverpresent_data = 0;
    register_canlib_rx(VANTTEC_CAN_ID_JETSON, VANTTEC_CAN_ID_DRIVER_PRESENT, VANTTEC_CANLIB_BYTE, &driverpresent_data, 1);
    for (;;)
    {
        if (driverpresent_data != last_driverpresent_data)
        {
            buf[0] = 0x07;
            buf[1] = 0x0;
            if (driverpresent_data == 1)
            {
                buf[1] = 0x1;
            }
            last_driverpresent_data = driverpresent_data;
            update_table(VANTTEC_CAN_ID_PANELRX, 0x07, buf, 2);
        }
        osDelay(10);
    }
}
void reverse_task(void *args)
{
    uint8_t buf[8];
    uint8_t reverse_data = 0;
    uint8_t last_reverse_data = 0;
    register_canlib_rx(VANTTEC_CAN_ID_JETSON, VANTTEC_CAN_ID_REVERSE, VANTTEC_CANLIB_BYTE, &reverse_data, 1);
    for (;;)
    {
        if (reverse_data != last_reverse_data)
        {
            buf[0] = 0x07;
            buf[1] = 0x0;
            if (reverse_data == 1)
            {
                buf[1] = 0x1;
            }
            last_reverse_data = reverse_data;
            update_table(VANTTEC_CAN_ID_PANELRX, 0x07, buf, 2);
        }
        osDelay(10);
    }
}
void frenomanual_task(void *args)
{
    uint8_t buf[8];
    uint8_t frenomanual_data = 0;
    uint8_t last_frenomanual_data = 0;
    register_canlib_rx(VANTTEC_CAN_ID_JETSON, VANTTEC_CAN_ID_FRENO_MANUAL, VANTTEC_CANLIB_BYTE, &frenomanual_data, 1);
    for (;;)
    {
        if (frenomanual_data != last_frenomanual_data)
        {
            buf[0] = 0x07;
            buf[1] = 0x0;
            if (frenomanual_data == 1)
            {
                buf[1] = 0x1;
            }
            last_frenomanual_data = frenomanual_data;
            update_table(VANTTEC_CAN_ID_PANELRX, 0x07, buf, 2);
        }
        osDelay(10);
    }
}
void driverfault_task(void *args)
{
    uint8_t buf[8];
    uint8_t driverfault_data = 0;
    uint8_t last_driverfault_data = 0;
    register_canlib_rx(VANTTEC_CAN_ID_JETSON, VANTTEC_CAN_ID_DRIVER_FAULT, VANTTEC_CANLIB_BYTE, &driverfault_data, 1);
    for (;;)
    {
        if (driverfault_data != last_driverfault_data)
        {
            buf[0] = 0x07;
            buf[1] = 0x0;
            if (driverfault_data == 1)
            {
                buf[1] = 0x1;
            }
            last_driverfault_data = driverfault_data;
            update_table(VANTTEC_CAN_ID_PANELRX, 0x07, buf, 2);
        }
        osDelay(10);
    }
}

void init_requirements_task()
{
    emergencystopTaskHandle = osThreadNew(emergencystop_task, NULL, &emergencystopTaskAttributes);
    hbTaskHandle = osThreadNew(hb_task, NULL, &hbTaskAttributes);
    drivemodeTaskHandle = osThreadNew(drivemode_task, NULL, &drivemodeTaskAttributes);
    driverpresentTaskHandle = osThreadNew(driverpresent_task, NULL, &driverpresentTaskAttributes);
    reverseTaskHandle = osThreadNew(reverse_task, NULL, &reverseTaskAttributes);
    frenomanualTaskHandle = osThreadNew(frenomanual_task, NULL, &frenomanualTaskAttributes);
    driverfaultTaskHandle = osThreadNew(driverfault_task, NULL, &driverfaultTaskAttributes);
}