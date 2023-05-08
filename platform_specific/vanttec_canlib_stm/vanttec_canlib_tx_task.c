#include "vanttec_canlib_tx_task.h"

#include "cmsis_os.h"
#include "utils.h"
#include "stm32l4xx_hal.h"
#include <stddef.h>
#include <string.h>
#include "CANMessage.h"

// Globals
osMessageQueueId_t g_txMessageQueue;

extern uint32_t g_vanttec_deviceId;
extern CAN_HandleTypeDef g_vanttec_hcan;

osThreadId_t canTxTaskHandle;
const osThreadAttr_t canTxTask_attributes = {
		.name = "canlib_tx",
		.stack_size = 128 * 2
};

void canlib_tx_task();

void init_canlib_tx(){
	g_txMessageQueue = osMessageQueueNew(64, sizeof(CAN_TX_QUEUE_OBJ), NULL);
	if(g_txMessageQueue == NULL){
		vanttec_canlib_error_handler();
	}

	canTxTaskHandle = osThreadNew(canlib_tx_task, NULL, &canTxTask_attributes);
}

void canlib_tx_update(){
	CAN_TxHeaderTypeDef txHeader;
	uint32_t txMailbox;
	txHeader.IDE = CAN_ID_STD;
	txHeader.StdId = g_vanttec_deviceId;
	txHeader.RTR = CAN_RTR_DATA;

	CAN_TX_QUEUE_OBJ txOut;
	while(osMessageQueueGet(g_txMessageQueue, &txOut, NULL, 1) == osOK){
		txHeader.DLC = txOut.msg_size;
		HAL_StatusTypeDef ret = HAL_CAN_AddTxMessage(&g_vanttec_hcan, &txHeader, txOut.buf, &txMailbox);
		if(ret != HAL_OK){
			txHeader.DLC++;
			//TODO do something on error
		}
	}
}

void canlib_tx_task(void *data){
	uint8_t buf[8];
	for(;;){
		canlib_tx_update();
		osDelay(10);
	}
}

void canlib_queue_tx(const uint8_t *data, uint8_t len){
	CAN_TX_QUEUE_OBJ obj;
	if(len < 0 || len > 8){
		vanttec_canlib_error_handler();
	}

	obj.msg_size = len;
	memcpy(obj.buf, data, len);

	osMessageQueuePut(g_txMessageQueue, &obj, 0, 10);
}

void canlib_send_byte(uint8_t id, const uint8_t data){
	uint8_t buf[2];
	can_pack_byte(id, data, buf, 2);
	canlib_queue_tx(buf, 2);
}

void canlib_send_short(uint8_t id, uint16_t data){
	uint8_t buf[3];
	can_pack_short(id, data, buf, 3);
	canlib_queue_tx(buf, 3);
}

void canlib_send_long(uint8_t id, uint32_t data){
	uint8_t buf[4];
	can_pack_long(id, data, buf, 4);
	canlib_queue_tx(buf, 4);
}

void canlib_send_float(uint8_t id, float data){
	uint8_t buf[4];
	can_pack_float(id, data, buf, 4);
	canlib_queue_tx(buf, 4);
}
