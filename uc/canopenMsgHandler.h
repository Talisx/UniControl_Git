/*
 * canopenMsgHandler.h
 *
 *  Created on: 09.09.2020
 *      Author: grewenig
 */

#ifndef UC_CANOPENMSGHANDLER_H_
#define UC_CANOPENMSGHANDLER_H_

#include <stdint.h>

extern uint8_t pui8TxBuffer[8];
extern uint8_t pui8RxBuffer[8];

/*Funktionen für Kimmer Platine, speziell um Can Nachrichten zu sortieren*/
/*Variablen Namen sind egal wie die gewählt werden*/
extern void pack(uint8_t SDO_Byte, uint16_t index, uint8_t sub_index, int32_t value);
extern uint32_t unpack(uint8_t *SDO_Byte, uint16_t *index, uint8_t *sub_index, int32_t *value);

#endif /* UC_CANOPENMSGHANDLER_H_ */
