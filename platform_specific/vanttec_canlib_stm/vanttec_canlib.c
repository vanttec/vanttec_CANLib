#include "vanttec_canlib.h"
#include "utils.h"
#include <cmsis_os.h>

CAN_HandleTypeDef g_vanttec_hcan;
uint16_t g_vanttec_deviceId;
osMutexId_t g_can_lock;

void init_canlib(CAN_HandleTypeDef hcan, uint8_t deviceId){
	g_vanttec_hcan = hcan;
	g_vanttec_deviceId = 0x400 | deviceId;

	// Initialize can filters
	CAN_FilterTypeDef filter;
	filter.FilterBank = 0;
	filter.FilterMode = CAN_FILTERMODE_IDMASK;
	filter.FilterScale = CAN_FILTERSCALE_32BIT;
	filter.FilterFIFOAssignment = CAN_RX_FIFO0;
	filter.FilterActivation = CAN_FILTER_ENABLE;
	filter.FilterIdHigh = 0;
	filter.FilterIdLow = g_vanttec_deviceId;
	filter.FilterMaskIdHigh = 0;
	filter.FilterMaskIdLow = 0xffff;
	filter.SlaveStartFilterBank = 14;

	// TODO set vanttec can ID
	HAL_StatusTypeDef ret = HAL_CAN_ConfigFilter(&hcan, &filter);
	if(ret != HAL_OK) vanttec_canlib_error_handler();

	ret = HAL_CAN_ActivateNotification(&hcan, CAN_IT_RX_FIFO0_MSG_PENDING);
	if(ret != HAL_OK) vanttec_canlib_error_handler();

	ret = HAL_CAN_Start(&hcan);
	if(ret != HAL_OK) vanttec_canlib_error_handler();

	g_can_lock = osMutexNew(NULL);

}
