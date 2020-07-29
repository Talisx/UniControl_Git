/*
 * uc_can.h
 *
 *  Created on: 10.08.2017
 *      Author: grewenig
 */

#ifndef UC_UC_CAN_H_
#define UC_UC_CAN_H_

#define CAN0_BAUDRATE	1000000

//Can data buffers for RX and TX
uint8_t				pui8TxBuffer[8];
uint8_t             pui8RxBuffer[8];

// Can message object structures for RX and TX
tCANMsgObject		sMsgObjectDataTx;
tCANMsgObject       sMsgObjectDataRx;

extern uint32_t ui32SysClock;
extern uint32_t ui32CanRxFlags;

/* Function prototypes */

extern void InitCAN0(void);
extern void InitCAN0MsgObjects(void);
extern void CAN0IntHandler(void);

extern void pack(uint8_t SDO_Byte, uint16_t index, uint8_t sub_index, int32_t value);
extern uint32_t unpack(uint8_t *SDO_Byte, uint16_t *index, uint8_t *sub_index, int32_t *value);

#endif /* UC_UC_CAN_H_ */
