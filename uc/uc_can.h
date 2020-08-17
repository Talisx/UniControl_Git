/*
 * uc_can.h
 *
 *  Created on: 10.08.2017
 *      Author: grewenig
 */

#ifndef UC_UC_CAN_H_
#define UC_UC_CAN_H_

//hier stand vorher 1000000
#define CAN0_BAUDRATE	250000

//Can data buffers for RX and TX
uint8_t				pui8TxBuffer[8];
uint8_t             pui8RxBuffer[8];

//variables for ISR Can
uint8_t Data_Encoder;
uint8_t Data_WinkelEncoder;
//uint8_t ui8CAN_ID = 0b00000001; //CAN_ID on EPOS (DIP-Switch)
extern bool Data_ValidEnco;
extern bool Data_ValidWinkel;

// Can message object structures for RX and TX
tCANMsgObject		sMsgObjectDataTx0;
tCANMsgObject       sMsgObjectDataRx0;
tCANMsgObject       sMsgObjectDataRx1;
tCANMsgObject       sMsgObjectDataRx2;

//Message structure for Kimmer
tCANMsgObject        sMsgObjectDataTx;
tCANMsgObject        sMsgObjectDataRx;

extern uint32_t ui32SysClock;
extern uint32_t ui32CanRxFlags;

/* Function prototypes */

extern void InitCAN0(void);
extern void InitCAN0MsgObjects(void);
extern void CAN0IntHandler(void);

/*Funktionen für Kimmer Platine, speziell um Can Nachrichten zu sortieren*/
extern void pack(uint8_t SDO_Byte, uint16_t index, uint8_t sub_index, int32_t value);
extern uint32_t unpack(uint8_t *SDO_Byte, uint16_t *index, uint8_t *sub_index, int32_t *value);

#endif /* UC_UC_CAN_H_ */
