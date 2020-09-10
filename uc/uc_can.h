/*
 * uc_can.h
 *
 *  Created on: 10.08.2017
 *      Author: grewenig
 */

#ifndef UC_UC_CAN_H_
#define UC_UC_CAN_H_
#include "canopenMsgHandler.h"
#include "Init_Motor.h"

//250000
//hier stand vorher 1000000
#define CAN0_BAUDRATE	1000000

//Can data buffers for RX and TX
uint8_t	pui8TxBuffer[8];
uint8_t pui8RxBuffer[8];

//variables for ISR Can
uint8_t Data_Encoder;
uint8_t Data_WinkelEncoder;
//Quintus Variablen
extern bool Data_ValidEnco;
extern bool Data_ValidWinkel;

//Kimmer Variablen
extern unsigned int display;
extern uint8_t SDO_Byte;
extern uint16_t index;
extern uint8_t sub_index;
extern int32_t value;

// Can message object structures for RX and TX
tCANMsgObject sMsgObjectDataTx0;
tCANMsgObject sMsgObjectDataTx1;
tCANMsgObject sMsgObjectDataRx0;
tCANMsgObject sMsgObjectDataRx1;
tCANMsgObject sMsgObjectDataRx2;
tCANMsgObject sMsgObjectDataRx3;

//Message structure for Kimmer
tCANMsgObject sMsgObjectDataTx;
tCANMsgObject sMsgObjectDataRx;

extern uint32_t ui32SysClock;
extern uint32_t ui32CanRxFlags;

/* Function prototypes */

extern void InitCAN0(void);
extern void InitCAN0MsgObjects(void);
extern void CAN0IntHandler(void);

#endif /* UC_UC_CAN_H_ */
