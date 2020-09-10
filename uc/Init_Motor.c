/*
 * Init_Motor.c
 *
 *  Created on: 26.08.2020
 *      Author: grewenig
 */

#include "Init_Motor.h"
#include "canopenMsgHandler.h"
#include <stdbool.h>
#include <stdint.h>
#include "Init_Motor.h"
#include "uc/EPOS_command_send.h"
#include "driverlib/can.h"
#include "uc/uc_can.h"
#include "inc/hw_memmap.h"

enum state{ FAULTRESET, OUT, ON, ENABLEOP, CURRENTMODE, SETTINGCURRENT};
enum state machineState;

/*
 * Hier wird auch jedes mal wieder der Error ausgebügelt !!!
 */
void initMotor(void)
{
        switch(machineState)
        {
            case FAULTRESET:
                //Fault reset
                pack(WRITING_SEND, CONTROL_WORD, 0,FAULT_RESET);
                CANMessageSet(CAN0_BASE, 5, &sMsgObjectDataTx, MSG_OBJ_TYPE_TX);
                machineState = OUT;
                break;
            case OUT:
                //Shut down
                pack(WRITING_SEND, CONTROL_WORD, 0,SHUTDOWN);
                CANMessageSet(CAN0_BASE, 5, &sMsgObjectDataTx, MSG_OBJ_TYPE_TX);
                //damit es keinen Pointer Fehler gibt
                char ch[2];
                //printf("Epos enable\n");
                machineState = ON;
                break;
            case ON:
                //Enable operation
                pack(WRITING_SEND, CONTROL_WORD, 0,ENABLE_OPERATION);
                CANMessageSet(CAN0_BASE, 5, &sMsgObjectDataTx, MSG_OBJ_TYPE_TX);
                // printf("EPOS enabled\n");
                machineState = ENABLEOP;
                break;
            case ENABLEOP:
                pack(WRITING_SEND, CONTROL_WORD, 0,ENABLE_OPERATION);
                CANMessageSet(CAN0_BASE, 5, &sMsgObjectDataTx, MSG_OBJ_TYPE_TX);
                // printf("EPOS enabled\n");
                machineState = CURRENTMODE;
                break;
            case CURRENTMODE:
                //Current Mode
                pack(WRITING_SEND, MODES_OF_OPERATION, 0,DIGITAL_CURRENT);
                CANMessageSet(CAN0_BASE, 5, &sMsgObjectDataTx, MSG_OBJ_TYPE_TX);
                initComplete = false;
                /*
                 *
                 * hier gehört abfrage rein ob alles funktioniert hat.
                 *
                 */
                break;
        }
}
