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
		.stack_size = 128 * 1
};
osThreadId_t drivemodeTaskHandle;
const osThreadAttr_t drivemodeTaskAttributes = {
	.name = "drivemode",
	.stack_size = 128 * 4};
osThreadId_t driverpresentTaskHandle;
const osThreadAttr_t driverpresentTaskAttributes = {
	.name = "driverpresent",
	.stack_size = 128 * 4};
const osThreadAttr_t reverseTaskAttributes = {
	.name = "reserve",
	.stack_size = 128 * 4};
const osThreadAttr_t frenomanualTaskAttributes = {
.name = "frenomanual",
.stack_size = 128 * 4};
const osThreadAttr_t driverfaultTaskAttributes = {
.name = "driverfault",
.stack_size = 128 * 4};

void emergencystop_task(void *args){
    for (;;)
    {
        osDelay(10);
    }
    
}
void hb_task(void *args){
	uint8_t data = 0;
	for(;;){
		canlib_send_debug_string("Hello");
		canlib_send_byte(VANTTEC_CAN_ID_HB, data);
		data++;
		osDelay(1000);
	}
}
void drivemode_task(void *args){
    for (;;)
    {
        osDelay(10);
    }
    
}
void driverpresent_task(void *args){
    for (;;)
    {
        osDelay(10);
    }
    
}
void reverse_task(void *args){
    for (;;)
    {
        osDelay(10);
    }
    
}
void frenomanual_task(void *args){
    for (;;)
    {
        osDelay(10);
    }
    
}
void driverfault_task(void *args){
    for (;;)
    {
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