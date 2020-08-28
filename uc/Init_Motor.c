/*
 * Init_Motor.c
 *
 *  Created on: 26.08.2020
 *      Author: grewenig
 */

#include <stdbool.h>
#include <stdint.h>
#include "Init_Motor.h"
#include "uc/EPOS_command_send.h"
#include "driverlib/can.h"
#include "uc/uc_can.h"
#include "inc/hw_memmap.h"


void initMotor(void)
{
    //Fault reset
    pack(WRITING_SEND, CONTROL_WORD, 0,FAULT_RESET);
    CANMessageSet(CAN0_BASE, 5, &sMsgObjectDataTx, MSG_OBJ_TYPE_TX);


    //Shut down
    pack(WRITING_SEND, CONTROL_WORD, 0,SHUTDOWN);
    CANMessageSet(CAN0_BASE, 5, &sMsgObjectDataTx, MSG_OBJ_TYPE_TX);
    //damit es keinen Pointer Fehler gibt
    char ch[2];
    //printf("Epos enable\n");

    //Switch on
    pack(WRITING_SEND, CONTROL_WORD, 0,SWITCH_ON);
    CANMessageSet(CAN0_BASE, 5, &sMsgObjectDataTx, MSG_OBJ_TYPE_TX);

    //Enable operation
    pack(WRITING_SEND, CONTROL_WORD, 0,ENABLE_OPERATION);
    CANMessageSet(CAN0_BASE, 5, &sMsgObjectDataTx, MSG_OBJ_TYPE_TX);
   // printf("EPOS enabled\n");

    //Current Mode
    pack(WRITING_SEND, MODES_OF_OPERATION, 0,DIGITAL_CURRENT);
    CANMessageSet(CAN0_BASE, 5, &sMsgObjectDataTx, MSG_OBJ_TYPE_TX);

    //Send CurrentModeSettingValue
    //pack(WRITING_SEND, CURRENT_MODE_SETTING_VALUE,0,CurrentModeSettingValue);
    pack(WRITING_SEND, CURRENT_MODE_SETTING_VALUE,0,500);
    CANMessageSet(CAN0_BASE, 5, &sMsgObjectDataTx, MSG_OBJ_TYPE_TX);
    //printf("Current Mode activated\nCurrent value (mA): %d\n", CurrentModeSettingValue);
}
