/*
 * uc_tasks.c
 *
 *  Created on: 10.08.2017
 *      Author: grewenig
 */

#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_can.h"
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/can.h"
#include "driverlib/gpio.h"
#include "driverlib/timer.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/systick.h"

#include "xcp/xcp_prot.h"
#include "xcp/can_if.h"

#include "UniControlSystem_ert_rtw/UniControlSystem.h"

#include "uc_functions.h"
#include "uc/uc_ad5755.h"
#include "uc/uc_ad7656.h"
#include "uc_tasks.h"

#include "uc/EPOS_command_send.h"

/*My includes
 */
/* UniControl header files */
#include "uc/uc_globals.h"
#include "uc/uc_periph.h"
#include "uc/uc_ad5755.h"
#include "uc/uc_ad7656.h"
#include "uc/uc_can.h"
#include "uc/uc_tasks.h"

#include <stdio.h>
#include <string.h>

//Torstens Variablen(Quintus Teil)
bool Data_ValidEnco = true;
bool Data_ValidWinkel = true;
int Nachricht_prüfer = 0;
int Nachrichten_prüfer1 = 0;

//Torstens Variablen(Kimmer Teil)
int32_t vorherigerStrom = 0;
int32_t aktuellerStrom = 0;


/* Global variables */
static char cUser_State = 0; //User state machine
static char ui8State = 0;    //User state machine
uint8_t SDO_Byte;
uint16_t index;
uint8_t sub_index;
int32_t value;
unsigned int display;
//System variables
const char *ErrorHistory1;
const char *ErrorHistory2;
const char *ErrorHistory3;
const char *ErrorHistory4;
const char *ErrorHistory5;
const char *Status;
const char *Mode_of_Operation;
const char *Can_Bitrate;

unsigned int ui32MaxFollowingError;
int16_t i16CurrentRegulator_PGain;
int16_t i16CurrentRegulator_IGain;
int16_t i16SpeedRegulator_PGain;
int16_t i16SpeedRegulator_IGain;
int16_t i16PositionRegulator_PGain;
int16_t i16PositionRegulator_IGain;
int16_t i16PositionRegulator_DGain;
uint16_t ui16VelocityFeedforwardFactor;
uint16_t ui16AccelerationFeedforwardFactor;
uint16_t ui16EncoderCounter;
uint16_t ui16EncoderCounterAtIndexPulse;
uint16_t ui16HallsensorPattern;
int16_t i16CurrentActualValueAveraged;
int32_t i32VelocityActualValueAveraged;
int16_t i16CurrentModeSettingValue;
int16_t i16FollowingErrorActualValue;
int32_t i32PositionDemandValue;
int32_t i32PositionActualValue;
int32_t i32VelocityDemandValue;
int32_t i32VelocityActualValue;
int16_t i16CurrentActualValue;

//check if there is new data
uint32_t ui32CanRxFlags = 0;

//*****************************************************************************
//
// The RTOS Idle task.
//
//*****************************************************************************

void TaskIdle(void)
{
	static uint8_t SysTickTimerEnabled = 1;

	/* During the first call of TaskIdle(), disable the SysTick Timer (Timer0) */
	if (SysTickTimerEnabled)
	{
		TimerDisable(TIMER0_BASE, TIMER_BOTH);
		SysTickTimerEnabled = 0;
	}

	DSXCP_background();


	//Teil von Kimmer!!!

	int16_t CurrentModeSettingValue = 500;
	//User State to enable EPOS

	switch(cUser_State)
	    {
	    // EPOS disables
	        case 0:
	            //Fault reset
	            pack(WRITING_SEND, CONTROL_WORD, 0,FAULT_RESET);
	            CANMessageSet(CAN0_BASE, 5, &sMsgObjectDataTx, MSG_OBJ_TYPE_TX);
	            cUser_State = 1;
	            break;
	        case 1:
	            //Shut down
	            pack(WRITING_SEND, CONTROL_WORD, 0,SHUTDOWN);
	            CANMessageSet(CAN0_BASE, 5, &sMsgObjectDataTx, MSG_OBJ_TYPE_TX);
	            //damit es keinen Pointer Fehler gibt
	            char ch[2];
	            printf("EPOS disabled\nPress 1 to enable\n");
	           // fgets(&cUser_State, 2, stdin);
	            //muss rein, der obere teil jedoch nicht
	           // fgets(&ch, 2, stdin);
	            ch[0] = '1';
	            cUser_State = ch[0];
	            //console input state machine
	            break;
	        case '1':
	            //Switch on
	            pack(WRITING_SEND, CONTROL_WORD, 0,SWITCH_ON);
	            CANMessageSet(CAN0_BASE, 5, &sMsgObjectDataTx, MSG_OBJ_TYPE_TX);
	            cUser_State = 2;
	            break;
	        case 2:
	            //Enable operation
	            pack(WRITING_SEND, CONTROL_WORD, 0,ENABLE_OPERATION);
	            CANMessageSet(CAN0_BASE, 5, &sMsgObjectDataTx, MSG_OBJ_TYPE_TX);
	            printf("EPOS enabled\n");
	            cUser_State++;
	            break;
	        case 3:
	            //Current Mode
	            pack(WRITING_SEND, MODES_OF_OPERATION, 0,DIGITAL_CURRENT);
	            CANMessageSet(CAN0_BASE, 5, &sMsgObjectDataTx, MSG_OBJ_TYPE_TX);
	            cUser_State++;
	            break;
	        case 4:
	            //Send CurrentModeSettingValue
	            pack(WRITING_SEND, CURRENT_MODE_SETTING_VALUE,0,CurrentModeSettingValue);
	            CANMessageSet(CAN0_BASE, 5, &sMsgObjectDataTx, MSG_OBJ_TYPE_TX);
	            printf("Current Mode activated\nCurrent value (mA): %d\n", CurrentModeSettingValue);
	            cUser_State++;
	            break;
	    }

	// Check if CAN message object 2 has new data.
	/*
	if(ui32CanRxFlags & 0b10)
	{
	    sMsgObjectDataRx.pui8MsgData = pui8RxBuffer;
	    // Set a pointer to the message object's data storage buffer.
	    CANMessageGet(CAN0_BASE, 6, &sMsgObjectDataRx, 0);
	    // Get the data content of message object 32.
	    ui32CanRxFlags &= ~0b10;
	    // Reset message object 32 in the flag register.
	    // System_printf("CAN message received in message object.\n");
	    // Print receive event in the console.
	    display=unpack(&SDO_Byte, &index, &sub_index, &value);
	    //Error history 1
	    if(display == 0x43100301){
	        if(value == 0x1000){
	            ErrorHistory1="Generic Error";
	        }
	        else if(value == 0x2310){
	            ErrorHistory1="Over Current Error";
	        }
	        else if(value == 0x3210){
	            ErrorHistory1="Over Voltage Error";
	        }
	        else if(value == 0x3220){
	            ErrorHistory1="Under Voltage Error";
	        }
	        else if(value == 0x4210){
	            ErrorHistory1="Over Temperature Error";
	        }
	        else if(value == 0x5113){
	            ErrorHistory1="Supply Voltage (5V) too Low Error";
	        }
	        else if(value == 0x6100){
	            ErrorHistory1="Internal Software Error";
	        }
	        else if(value == 0x6320){
	            ErrorHistory1="Software Parameter Error";
	        }
	        else if(value == 0x7320){
	            ErrorHistory1="Sensor Position Error";
	        }
	        else if(value == 0x8110){
	            ErrorHistory1="CAN Overrun Error (Objects Lost)";
	        }
	        else if(value == 0x8111){
	            ErrorHistory1="CAN Overrun Error";
	        }
	        else if(value == 0x8120){
	            ErrorHistory1="CAN Passive Mode Error";
	        }
	        else if(value == 0x8130){
	            ErrorHistory1="CAN Life Guard Error";
	        }
	        else if(value == 0x8150){
	            ErrorHistory1="CAN Transmit COB-ID Collision";
	        }
	        else if(value == 0x81FD){
	            ErrorHistory1="CAN-BUS Of";
	        }
	        else if(value == 0x81FE){
	            ErrorHistory1="CAN-RX Queue Overrun";
	        }
	        else if(value == 0x81FF){
	            ErrorHistory1="CAN-TX Queue Overrun";
	        }
	        else if(value == 0x8210){
	            ErrorHistory1="CAN-PDO Length Error";
	        }
	        else if(value == 0x8611){
	            ErrorHistory1="Following Error";
	        }
	        else if(value == 0xFF01){
	            ErrorHistory1="Hallsensor Error";
	        }
	        else if(value == 0xFF02){
	            ErrorHistory1="Index Processing Error";
	        }
	        else if(value == 0xFF03){
	            ErrorHistory1="Encoder Resolution Error";
	        }
	        else if(value == 0xFF04){
	            ErrorHistory1="Hallsensor Not Found Error";
	        }
	        else if(value == 0xFF06){
	            ErrorHistory1="Negative Limit Error";
	        }
	        else if(value == 0xFF07){
	            ErrorHistory1="Positive Limit Error";
	        }
	        else if(value == 0xFF08){
	            ErrorHistory1="Hall Angle Detection Error";
	        }
	        else if(value == 0xFF09){
	            ErrorHistory1="Software Position Limit Error";
	        }
	        else if(value == 0xFF0A){
	            ErrorHistory1="Position Sensor Breach";
	        }
	        else if(value == 0xFF0B){
	            ErrorHistory1="System Overload";
	        }
	        else if(value == 0x0000){
	            ErrorHistory1="";
	        }
	    }
	    //Error history 2
	    if(display == 0x43100302){
	        if(value == 0x1000){
	            ErrorHistory2="Generic Error";
	        }
	        else if(value == 0x2310){
	            ErrorHistory2="Over Current Error";
	        }
	        else if(value == 0x3210){
	            ErrorHistory2="Over Voltage Error";
	        }
	        else if(value == 0x3220){
	            ErrorHistory2="Under Voltage Error";
	        }
	        else if(value == 0x4210){
	            ErrorHistory2="Over Temperature Error";
	        }
	        else if(value == 0x5113){
	            ErrorHistory2="Supply Voltage (5V) too Low Error";
            }
            else if(value == 0x6100){
                ErrorHistory2="Internal Software Error";
            }
            else if(value == 0x6320){
                ErrorHistory2="Software Parameter Error";
            }
            else if(value == 0x7320){
                ErrorHistory2="Sensor Position Error";
            }
            else if(value == 0x8110){
                ErrorHistory2="CAN Overrun Error (Objects Lost)";
            }
            else if(value == 0x8111){
                ErrorHistory2="CAN Overrun Error";
            }
            else if(value == 0x8120){
                ErrorHistory2="CAN Passive Mode Error";
            }
            else if(value == 0x8130){
                ErrorHistory2="CAN Life Guard Error";
            }
            else if(value == 0x8150){
                ErrorHistory2="CAN Transmit COB-ID Collision";
            }
            else if(value == 0x81FD){
                ErrorHistory2="CAN-BUS Of";
            }
            else if(value == 0x81FE){
                ErrorHistory2="CAN-RX Queue Overrun";
            }
            else if(value == 0x81FF){
                ErrorHistory2="CAN-TX Queue Overrun";
            }
            else if(value == 0x8210){
                ErrorHistory2="CAN-PDO Length Error";
            }
            else if(value == 0x8611){
                ErrorHistory2="Following Error";
            }
            else if(value == 0xFF01){
                ErrorHistory2="Hallsensor Error";
            }
            else if(value == 0xFF02){
                ErrorHistory2="Index Processing Error";
            }
            else if(value == 0xFF03){
                ErrorHistory2="Encoder Resolution Error";
            }
            else if(value == 0xFF04){
                ErrorHistory2="Hallsensor Not Found Error";
            }
            else if(value == 0xFF06){
                ErrorHistory2="Negative Limit Error";
            }
            else if(value == 0xFF07){
                ErrorHistory2="Positive Limit Error";
            }
            else if(value == 0xFF08){
                ErrorHistory2="Hall Angle Detection Error";
            }
            else if(value == 0xFF09){
                ErrorHistory2="Software Position Limit Error";
            }
            else if(value == 0xFF0A){
                ErrorHistory2="Position Sensor Breach";
            }
            else if(value == 0xFF0B){
            ErrorHistory2="System Overload";
            }
            else if(value == 0x0000){
            ErrorHistory2="";
            }
            }
            //Error history 3
            if(display == 0x43100303){
                if(value == 0x1000){
                    ErrorHistory3="Generic Error";
                }
                else if(value == 0x2310){
                    ErrorHistory3="Over Current Error";
                }
                else if(value == 0x3210){
                    ErrorHistory3="Over Voltage Error";
                }
                else if(value == 0x3220){
                    ErrorHistory3="Under Voltage Error";
                }
                else if(value == 0x4210){
                    ErrorHistory3="Over Temperature Error";
                }
                else if(value == 0x5113){
                    ErrorHistory3="Supply Voltage (5V) too Low Error";
                }
                else if(value == 0x6100){
                    ErrorHistory3="Internal Software Error";
                }
                else if(value == 0x6320){
                    ErrorHistory3="Software Parameter Error";
                }
                else if(value == 0x7320){
                    ErrorHistory3="Sensor Position Error";
                }
                else if(value == 0x8110){
                    ErrorHistory3="CAN Overrun Error (Objects Lost)";
                }
                else if(value == 0x8111){
                    ErrorHistory3="CAN Overrun Error";
                }
                else if(value == 0x8120){
                    ErrorHistory3="CAN Passive Mode Error";
                }
                else if(value == 0x8130){
                    ErrorHistory3="CAN Life Guard Error";
                }
                else if(value == 0x8150){
                    ErrorHistory3="CAN Transmit COB-ID Collision";
                }
                else if(value == 0x81FD){
                    ErrorHistory3="CAN-BUS Of";
                }
                else if(value == 0x81FE){
                    ErrorHistory3="CAN-RX Queue Overrun";
                }
                else if(value == 0x81FF){
                    ErrorHistory3="CAN-TX Queue Overrun";
                }
                else if(value == 0x8210){
                    ErrorHistory3="CAN-PDO Length Error";
                }
                else if(value == 0x8611){
                    ErrorHistory3="Following Error";
                }
                else if(value == 0xFF01){
                    ErrorHistory3="Hallsensor Error";
                }
                else if(value == 0xFF02){
                    ErrorHistory3="Index Processing Error";
                }
                else if(value == 0xFF03){
                    ErrorHistory3="Encoder Resolution Error";
                }
                else if(value == 0xFF04){
                    ErrorHistory3="Hallsensor Not Found Error";
                }
                else if(value == 0xFF06){
                    ErrorHistory3="Negative Limit Error";
                }
                else if(value == 0xFF07){
                    ErrorHistory3="Positive Limit Error";
                }
                else if(value == 0xFF08){
                    ErrorHistory3="Hall Angle Detection Error";
                }
                else if(value == 0xFF09){
                    ErrorHistory3="Software Position Limit Error";
                }
                else if(value == 0xFF0A){
                    ErrorHistory3="Position Sensor Breach";
                }
                else if(value == 0xFF0B){
                    ErrorHistory3="System Overload";
                }
                else if(value == 0x0000){
                    ErrorHistory3="";
                }
            }

            //Error history 4
            if(display == 0x43100304){
                if(value == 0x1000){
                    ErrorHistory4="Generic Error";
                }
                else if(value == 0x2310){
                    ErrorHistory4="Over Current Error";
                }
                else if(value == 0x3210){
                    ErrorHistory4="Over Voltage Error";
                }
                else if(value == 0x3220){
                    ErrorHistory4="Under Voltage Error";
                }
                else if(value == 0x4210){
                    ErrorHistory4="Over Temperature Error";
                }
                else if(value == 0x5113){
                    ErrorHistory4="Supply Voltage (5V) too Low Error";
                }
                else if(value == 0x6100){
                    ErrorHistory4="Internal Software Error";
                }
                else if(value == 0x6320){
                    ErrorHistory4="Software Parameter Error";
                }
                else if(value == 0x7320){
                ErrorHistory4="Sensor Position Error";
                }
                else if(value == 0x8110){
                    ErrorHistory4="CAN Overrun Error (Objects Lost)";
                }
                else if(value == 0x8111){
                    ErrorHistory4="CAN Overrun Error";
                }
                else if(value == 0x8120){
                    ErrorHistory4="CAN Passive Mode Error";
                }
                else if(value == 0x8130){
                    ErrorHistory4="CAN Life Guard Error";
                }
                else if(value == 0x8150){
                    ErrorHistory4="CAN Transmit COB-ID Collision";
                }
                else if(value == 0x81FD){
                    ErrorHistory4="CAN-BUS Of";
                }
                else if(value == 0x81FE){
                    ErrorHistory4="CAN-RX Queue Overrun";
                }
                else if(value == 0x81FF){
                    ErrorHistory4="CAN-TX Queue Overrun";
                }
                else if(value == 0x8210){
                    ErrorHistory4="CAN-PDO Length Error";
                }
                else if(value == 0x8611){
                    ErrorHistory4="Following Error";
                }
                else if(value == 0xFF01){
                    ErrorHistory4="Hallsensor Error";
                }
                else if(value == 0xFF02){
                    ErrorHistory4="Index Processing Error";
                }
                else if(value == 0xFF03){
                    ErrorHistory4="Encoder Resolution Error";
                }
                else if(value == 0xFF04){
                    ErrorHistory4="Hallsensor Not Found Error";
                }
                else if(value == 0xFF06){
                    ErrorHistory4="Negative Limit Error";
                }
                else if(value == 0xFF07){
                    ErrorHistory4="Positive Limit Error";
                }
                else if(value == 0xFF08){
                    ErrorHistory4="Hall Angle Detection Error";
                }
                else if(value == 0xFF09){
                    ErrorHistory4="Software Position Limit Error";
                }

                else if(value == 0xFF0A){
                ErrorHistory4="Position Sensor Breach";
                }
                else if(value == 0xFF0B){
                ErrorHistory4="System Overload";
                }
                else if(value == 0x0000){
                ErrorHistory4="";
                }
            }
            //Error history 5
            if(display == 0x43100305){
                if(value == 0x1000){
                    ErrorHistory5="Generic Error";
                }
                else if(value == 0x2310){
                    ErrorHistory5="Over Current Error";
                }
                else if(value == 0x3210){
                    ErrorHistory5="Over Voltage Error";
                }
                else if(value == 0x3220){
                    ErrorHistory5="Under Voltage Error";
                }
                else if(value == 0x4210){
                    ErrorHistory5="Over Temperature Error";
                }
                else if(value == 0x5113){
                    ErrorHistory5="Supply Voltage (5V) too Low Error";
                }
                else if(value == 0x6100){
                    ErrorHistory5="Internal Software Error";
                }
                else if(value == 0x6320){
                    ErrorHistory5="Software Parameter Error";
                }
                else if(value == 0x7320){
                    ErrorHistory5="Sensor Position Error";
                }
                else if(value == 0x8110){
                    ErrorHistory5="CAN Overrun Error (Objects Lost)";
                }
                else if(value == 0x8111){
                    ErrorHistory5="CAN Overrun Error";
                }
                else if(value == 0x8120){
                    ErrorHistory5="CAN Passive Mode Error";
                }
                else if(value == 0x8130){
                    ErrorHistory5="CAN Life Guard Error";
                }
                else if(value == 0x8150){
                    ErrorHistory5="CAN Transmit COB-ID Collision";
                }
                else if(value == 0x81FD){
                    ErrorHistory5="CAN-BUS Of";
                }
                else if(value == 0x81FE){
                    ErrorHistory5="CAN-RX Queue Overrun";
                }
                else if(value == 0x81FF){
                    ErrorHistory5="CAN-TX Queue Overrun";
                }
                else if(value == 0x8210){
                    ErrorHistory5="CAN-PDO Length Error";
                }
                else if(value == 0x8611){
                    ErrorHistory5="Following Error";
                }
                else if(value == 0xFF01){
                    ErrorHistory5="Hallsensor Error";
                }
                else if(value == 0xFF02){
                    ErrorHistory5="Index Processing Error";
                }
                else if(value == 0xFF03){
                    ErrorHistory5="Encoder Resolution Error";
                }
                else if(value == 0xFF04){
                    ErrorHistory5="Hallsensor Not Found Error";
                }
                else if(value == 0xFF06){
                    ErrorHistory5="Negative Limit Error";
                }
                else if(value == 0xFF07){
                    ErrorHistory5="Positive Limit Error";
                }
                else if(value == 0xFF08){
                    ErrorHistory5="Hall Angle Detection Error";
                }
                else if(value == 0xFF09){
                    ErrorHistory5="Software Position Limit Error";
                }
                else if(value == 0xFF0A){
                    ErrorHistory5="Position Sensor Breach";
                }
                else if(value == 0xFF0B){
                    ErrorHistory5="System Overload";
                }
                else if(value == 0x0000){
                    ErrorHistory5="";
                }
            }
            //STATUS_WORD
            if(display == 0x4B604100){
                if(value==0x508){
                    Status="FAULT";
                }
                else if(value==0x500){
                    Status="NOT_READY_TO_SWITCH_ON";
                }
                else if(value==0x540){
                    Status="SWITCH_ON_DISABLED";
                }
                else if(value==0x521){
                    Status="READY_TO_SWITCH_ON";
                }
                else if(value==0x523){
                    Status="SWITCHED_ON";
                }
                else if(value==0x537){
                    Status="OPERATION_ENABLED";
                }
                else if(value==0x517){
                    Status="QUICK_STOP_ACTIVATE";
                }
                else {
                    Status="UNKNOWN";
                }
            }
            //MODES OF OPERATION
            if(display == 0x4F606100){
                if(value==0xF7){
                    Mode_of_Operation="ELECTRICAL_GEARING";
                }
                else if(value==0xF8){
                    Mode_of_Operation="JOGGING";
                }
                else if(value==0xF9){
                    Mode_of_Operation="HOMING";
                }
                else if(value==0xFA){
                    Mode_of_Operation="TRAJECTORY";
                }
                else if(value==0xFB){
                    Mode_of_Operation="ANALOG_CURRENT";
                }
                else if(value==0xFC){
                    Mode_of_Operation="ANALOG_SPEED";
                }
                else if(value==0xFD){
                    Mode_of_Operation="DIGITAL_CURRENT";
                }
                else if(value==0xFE){
                    Mode_of_Operation="DIGITAL_SPEED";
                }
                else if(value==0xFF){
                    Mode_of_Operation="POSITION";
                }
                else if(value==0x01){
                    Mode_of_Operation="POSITIONING_PP";
                }
                else if(value==0x02){
                    Mode_of_Operation="SPEED_VL";
                }
                else if(value==0x03){
                    Mode_of_Operation="SPEED_PV";
                }
                else if(value==0x04){
                    Mode_of_Operation="TORQUE_TQ";
                }
                else if(value==0x06){
                    Mode_of_Operation="HOMING_HM";
                }
                else if(value==0x07){
                    Mode_of_Operation="INTERPOLATION";
                }
                else {
                    Mode_of_Operation="UNKNOWN";
                }
            }
            // Objects
            if(display == 0x4B200100){
                if(value==0){
                    Can_Bitrate="1MBit/s";
                }
                else if(value==1){
                    Can_Bitrate="800kBit/s";
                }
                else if(value==2){
                    Can_Bitrate="500kBit/s";
                }
                else if(value==3){
                    Can_Bitrate="250kBit/s";
                }
                else if(value==4){
                Can_Bitrate="125kBit/s";
                }
                else if(value==5){
                    Can_Bitrate="50kBit/s";
                }
                else if(value==6){
                    Can_Bitrate="20kMBit/s";
                }
                else {
                    Can_Bitrate="UNKNOWN BITRATE";
                }
            }
            if(display == 0x43606500){
                ui32MaxFollowingError=value;
            }
            if(display == 0x4B60F601){
                i16CurrentRegulator_PGain=value;
                printf("Ausgabe P-Gain %d \n", i16CurrentRegulator_PGain);
            }
            if(display == 0x4B60F602){
                i16CurrentRegulator_IGain=value;
            }
            if(display == 0x4B60F901){
                i16SpeedRegulator_PGain=value;
            }
            if(display == 0x4B60F902){
                i16SpeedRegulator_IGain=value;
            }
            if(display == 0x4B60FB01){
                i16PositionRegulator_PGain=value;
            }
            if(display == 0x4B60FB02){
                i16PositionRegulator_IGain=value;
            }
            if(display == 0x4B60FB03){
                i16PositionRegulator_DGain=value;
            }
            if(display == 0x4B60FB04){
                ui16VelocityFeedforwardFactor=value;
            }
            if(display == 0x4B60FB05){
                ui16AccelerationFeedforwardFactor=value;
            }
            if(display == 0x4B202000){
                ui16EncoderCounter=value;
            }
            if(display == 0x4B202100){
                ui16EncoderCounterAtIndexPulse=value;
            }
            if(display == 0x4B202200){
                ui16HallsensorPattern=value;
            }
            if(display == 0x4B202700){
                i16CurrentActualValueAveraged=value;
            }
            if(display == 0x43202800){
                i32VelocityActualValueAveraged=value;
            }
            if(display == 0x4B203000){
                i16CurrentModeSettingValue=value;
            }
            if(display == 0x4B20F400){
                i16FollowingErrorActualValue=value;
            }
            if(display == 0x43606200){
                i32PositionDemandValue=value;
            }
            if(display == 0x43606400){
                i32PositionActualValue=value;
            }
            if(display == 0x43606B00){
                i32VelocityDemandValue=value;
            }
            if(display == 0x43606C00){
                i32VelocityActualValue=value;
            }
            if(display == 0x4B607800){
                i16CurrentActualValue=value;
            }
        }
        */
           // System_flush(); // Flush the IO-Buffer to display console content.

            return;
}


//*****************************************************************************
//
// The RTOS 100us task.
//
//*****************************************************************************

void Task100us(void)
{
	TimerIntClear(TIMER1_BASE, TIMER_TIMA_TIMEOUT);
	/* Read the ADC and store the resulting samples in signed integer format*/
	AD7656_Read(i16AdcValue);

	return;
}

//*****************************************************************************
//
// The RTOS 10ms task.
//
//*****************************************************************************

void Task10ms(void)
{
	static uint8_t i;

	/* Clear the interrupt flag */
	TimerIntClear(TIMER2_BASE, TIMER_TIMA_TIMEOUT);

	/* Convert ADC value to double using the respective dynamic range*/
	for(i=0; i<6; i++)
	{
		 dAdcValue[i] = (real_T)(i16AdcValue[i]) * 10.0 / 32768;
	}

	/* Copy values to the model input vector */

	/*
	for(i=0; i<6; i++)
	{
		ModelInput[i] = dAdcValue[i];
	}
    */

	ModelInput[4] = Data_WinkelEncoder;

	/* Step the Simulink model */
	UniControlSystem_Step(	ModelInput[0],  ModelInput[1],  ModelInput[2],  ModelInput[3],
							ModelInput[4],  ModelInput[5],  ModelInput[6],  ModelInput[7],
							ModelInput[8],  ModelInput[9],  ModelInput[10], ModelInput[11],
							ModelInput[12], ModelInput[13], ModelInput[14], ModelInput[15],
							&ModelOutput[0],  &ModelOutput[1],  &ModelOutput[2],  &ModelOutput[3],
							&ModelOutput[4],  &ModelOutput[5],  &ModelOutput[6],  &ModelOutput[7],
							&ModelOutput[8],  &ModelOutput[9],  &ModelOutput[10], &ModelOutput[11],
							&ModelOutput[12], &ModelOutput[13], &ModelOutput[14], &ModelOutput[15]);


	aktuellerStrom = (int32_t)Strom;
	/*
	if (aktuellerStrom == vorherigerStrom)
	{
	    // nix ändern
	}
	else
	{
	    if(aktuellerStrom < 0)
	    {
	        aktuellerStrom = 0;
	    }
	    elseif(aktuellerStrom > 1000)
	    {
	        aktuellerStrom = 1000;
	    }
	    // wert neu senden
	    vorherigerStrom = aktuellerStrom;
	    //printf("Current Mode activated\nCurrent value (mA): %d\n", CurrentModeSettingValue);
	}
    */
	/* Copy values from model output vector to DAC values using the respective dynamic range */

	/* Raus weil keine Ausgänge benötigt
	for(i=0; i<4; i++)
	{
		ui16DacValue[i] = (uint16_t) ((ModelOutput[i]-dDacVcal[i]) / 10.0 * 32768 + 32768);
	}
	*/

	/* Update the DAC registers*/
	AD5755_Channel_Put(ui16DacValue[0], ui16DacValue[1], ui16DacValue[2], ui16DacValue[3]);

	DSXCP_service(0);
	return;
}

//*****************************************************************************
//
// The RTOS 100ms task.
//
//*****************************************************************************

void Task100ms(void)
{
	static uint8_t i = 0;
	static uint8_t k = 0;

	/* Clear the interrupt flag */
	TimerIntClear(TIMER3_BASE, TIMER_TIMA_TIMEOUT);

	//--------------------------------------------------------------------------------------------------------------------------
	/*Request for all Data*/
	//Hier wird geprüft ob die Verbindung überhaupt noch besteht
    if(Data_ValidEnco == true && Data_ValidWinkel == true)
    {
        Data_ValidEnco = false;
        Data_ValidWinkel = false;
        pui8TxBuffer[0] = 200;
        CANMessageSet(CAN0_BASE, 1, &sMsgObjectDataTx0, MSG_OBJ_TYPE_TX);
        Nachrichten_prüfer1++;
        //alle 50 Nachrichten, kann mal eine Fehlerhafte message ignoriert werden
        if(Nachrichten_prüfer1 == 50)
        {
            Nachricht_prüfer = 0;
            Nachrichten_prüfer1 = 0;
        }
    }
    else
    {
        // man könnte eine if schleife hoch zählen, die ab bestimmten wert dann einfach alles ab schaltet
        // zum vermeiden, das alles abkratzt wenn mal eine Nachricht zwischen drin falsch ist
        if(Nachricht_prüfer == 0)
        {
            Data_ValidEnco = true;
            Data_ValidWinkel = true;
            Nachricht_prüfer++;
        }
        //Nachricht hier einfügen, das Fehler entstanden ist
        // kamen mehr als 2 Nachrichten nicht richtig an
        else
        {

        }
    }
    //--------------------------------------------------------------------------------------------------------------------------


	if(i == 7)
	{
		i = 0;
		ToggleLED();

		if(k < 7)
		{
			k++;
			ModelInput[6]  = dStimulus[k];
		}
		else
		{
			k = 0;
			ModelInput[6]  = dStimulus[k];
		}
	}
	else
	{
		i++;
	}

	switch(ui8State)
	    {
	    /*
	        case 0: pack(0x40, 0x60F6 ,0x01 , 0);
	                CANMessageSet(CAN0_BASE, 5, &sMsgObjectDataTx, MSG_OBJ_TYPE_TX);
	                break;
	                */
	/*
	        case 0: pack(READING_SEND, NUMBER_OF_ERRORS,ERROR_HISTORY_1, 0);
	                CANMessageSet(CAN0_BASE, 5, &sMsgObjectDataTx,MSG_OBJ_TYPE_TX);
	                ui8State++;
	                break;
	        case 1: pack(READING_SEND, NUMBER_OF_ERRORS,ERROR_HISTORY_2, 0);
	                CANMessageSet(CAN0_BASE, 5, &sMsgObjectDataTx,MSG_OBJ_TYPE_TX);
	                ui8State++;
	                break;
	        case 2: pack(READING_SEND, NUMBER_OF_ERRORS,ERROR_HISTORY_3, 0);
	                CANMessageSet(CAN0_BASE, 5, &sMsgObjectDataTx,MSG_OBJ_TYPE_TX);
	                ui8State++;
	                break;
	        case 3: pack(READING_SEND, NUMBER_OF_ERRORS,ERROR_HISTORY_4, 0);
	                CANMessageSet(CAN0_BASE, 5, &sMsgObjectDataTx,MSG_OBJ_TYPE_TX);
	                ui8State++;
	                break;
	        case 4: pack(READING_SEND, NUMBER_OF_ERRORS,ERROR_HISTORY_5, 0);
	                CANMessageSet(CAN0_BASE, 5, &sMsgObjectDataTx,MSG_OBJ_TYPE_TX);
	                ui8State++;
	                break;
	        case 5: pack(READING_SEND, CONTROL_WORD, 0, 0);
	                CANMessageSet(CAN0_BASE, 5, &sMsgObjectDataTx,MSG_OBJ_TYPE_TX);
	                ui8State++;
	                break;
	        case 6: pack(READING_SEND, STATUS_WORD, 0, 0);
	                CANMessageSet(CAN0_BASE, 5, &sMsgObjectDataTx,MSG_OBJ_TYPE_TX);
	                ui8State++;
	                break;
	        case 7: pack(READING_SEND, MODES_OF_OPERATION_DISPLAY, 0,0);
	                CANMessageSet(CAN0_BASE, 5, &sMsgObjectDataTx,MSG_OBJ_TYPE_TX);
	                ui8State++;
	                break;
	        case 8: pack(READING_SEND, CAN_BITRATE, 0, 0);
	                CANMessageSet(CAN0_BASE, 5, &sMsgObjectDataTx,MSG_OBJ_TYPE_TX);
	                ui8State++;
	                break;
	        case 9: pack(READING_SEND, MAX_FOLLOWING_ERROR, 0, 0);
	                CANMessageSet(CAN0_BASE, 5, &sMsgObjectDataTx,MSG_OBJ_TYPE_TX);
	                ui8State++;
	                break;
	        case 10: pack(READING_SEND, CURRENT_REGULATOR, P_GAIN, 0);
	                 CANMessageSet(CAN0_BASE, 5, &sMsgObjectDataTx,MSG_OBJ_TYPE_TX);
	                 ui8State++;
	                 break;
	        case 11: pack(READING_SEND, CURRENT_REGULATOR, I_GAIN, 0);
	                 CANMessageSet(CAN0_BASE, 5, &sMsgObjectDataTx,MSG_OBJ_TYPE_TX);
	                 ui8State++;
	                 break;
	        case 12: pack(READING_SEND, SPEED_REGULATOR, P_GAIN, 0);
	                 CANMessageSet(CAN0_BASE, 5, &sMsgObjectDataTx,MSG_OBJ_TYPE_TX);
	                 ui8State++;
	                 break;
	        case 13: pack(READING_SEND, SPEED_REGULATOR, I_GAIN, 0);
	                 CANMessageSet(CAN0_BASE, 5, &sMsgObjectDataTx,MSG_OBJ_TYPE_TX);
	                 ui8State++;
	                 break;
	        case 14: pack(READING_SEND, POSITION_REGULATOR, P_GAIN, 0);
	                 CANMessageSet(CAN0_BASE, 5, &sMsgObjectDataTx,MSG_OBJ_TYPE_TX);
	                 ui8State++;
	                 break;
	        case 15: pack(READING_SEND, POSITION_REGULATOR, I_GAIN, 0);
	                 CANMessageSet(CAN0_BASE, 5, &sMsgObjectDataTx,MSG_OBJ_TYPE_TX);
	                 ui8State++;
	                 break;
	        case 16: pack(READING_SEND, POSITION_REGULATOR, D_GAIN, 0);
	                 CANMessageSet(CAN0_BASE, 5, &sMsgObjectDataTx,MSG_OBJ_TYPE_TX);
	                 ui8State++;
	                 break;
	        case 17: pack(READING_SEND, POSITION_REGULATOR,VELOCITY_FEEDFORWARD_FACTOR, 0);
	                 CANMessageSet(CAN0_BASE, 5, &sMsgObjectDataTx,MSG_OBJ_TYPE_TX);
	                 ui8State++;
	                 break;
	        case 18: pack(READING_SEND, POSITION_REGULATOR,ACCELERATION_FEEDFORWARD_FACTOR, 0);
	                 CANMessageSet(CAN0_BASE, 5, &sMsgObjectDataTx,MSG_OBJ_TYPE_TX);
	                 ui8State++;
	                 break;
	        case 19: pack(READING_SEND, ENCODER_COUNTER, 0, 0);
	                 CANMessageSet(CAN0_BASE, 5, &sMsgObjectDataTx,MSG_OBJ_TYPE_TX);
	                 ui8State++;
	                 break;
	        case 20: pack(READING_SEND, ENCODER_COUNTER_INDEX_PULSE, 0,0);
	                 CANMessageSet(CAN0_BASE, 5, &sMsgObjectDataTx,MSG_OBJ_TYPE_TX);
	                 ui8State++;
	                 break;
	        case 21: pack(READING_SEND, HALLSENSOR_PATTERN, 0, 0);
	                 CANMessageSet(CAN0_BASE, 5, &sMsgObjectDataTx,MSG_OBJ_TYPE_TX);
	                 ui8State++;
	                 break;
	        case 22: pack(READING_SEND, CURRENT_ACTUAL_VALUE_AVERAGED,0, 0);
	                 CANMessageSet(CAN0_BASE, 5, &sMsgObjectDataTx,MSG_OBJ_TYPE_TX);
	                 ui8State++;
	                 break;
	        case 23: pack(READING_SEND, VELOCITY_ACTUAL_VALUE_AVERAGED,0, 0);
	                 CANMessageSet(CAN0_BASE, 5, &sMsgObjectDataTx,MSG_OBJ_TYPE_TX);
	                 ui8State++;
	                 break;
	        case 24: pack(READING_SEND, CURRENT_MODE_SETTING_VALUE, 0,0);
	                 CANMessageSet(CAN0_BASE, 5, &sMsgObjectDataTx,MSG_OBJ_TYPE_TX);
	                 ui8State++;
	                 break;
	        case 25: pack(READING_SEND, FOLLOWING_ERROR_ACTUAL_VALUE, 0,0);
	                 CANMessageSet(CAN0_BASE, 5, &sMsgObjectDataTx,MSG_OBJ_TYPE_TX);
	                 ui8State++;
	                 break;
	        case 26: pack(READING_SEND, POSITION_DEMAND_VALUE, 0, 0);
	                 CANMessageSet(CAN0_BASE, 5, &sMsgObjectDataTx,MSG_OBJ_TYPE_TX);
	                 ui8State++;
	                 break;
	        case 27: pack(READING_SEND, POSITION_ACTUAL_VALUE, 0, 0);
	                 CANMessageSet(CAN0_BASE, 5, &sMsgObjectDataTx,MSG_OBJ_TYPE_TX);
	                 ui8State++;
	                 break;
	        case 28: pack(READING_SEND, VELOCITY_DEMAND_VALUE, 0, 0);
	                 CANMessageSet(CAN0_BASE, 5, &sMsgObjectDataTx,MSG_OBJ_TYPE_TX);
	                 ui8State++;
	                 break;
	        case 29: pack(READING_SEND, VELOCITY_ACTUAL_VALUE, 0, 0);
	                 CANMessageSet(CAN0_BASE, 5, &sMsgObjectDataTx,MSG_OBJ_TYPE_TX);
	                 ui8State++;
	                 break;
	        case 30: pack(READING_SEND, CURRENT_ACTUAL_VALUE, 0, 0);
	                 CANMessageSet(CAN0_BASE, 5, &sMsgObjectDataTx,MSG_OBJ_TYPE_TX);
	                 ui8State=0;
	                 break;
	                        */
	    }
	return;
}

// This function packs the different communication objects and the value in CANopen format.
void pack(uint8_t SDO_Byte, uint16_t index, uint8_t sub_index, int32_t value)
{
    uint8_t *pointer_index_Tx = &index;
    int8_t *pointer_value_Tx = &value;
    pui8TxBuffer [0] = SDO_Byte;
    pui8TxBuffer [1] = *pointer_index_Tx;
    pui8TxBuffer [2] = *(pointer_index_Tx+1);
    pui8TxBuffer [3] = sub_index;
    pui8TxBuffer [4] = *pointer_value_Tx;
    pui8TxBuffer [5] = *(pointer_value_Tx+1);
    pui8TxBuffer [6] = *(pointer_value_Tx+2);
    pui8TxBuffer [7] = *(pointer_value_Tx+3);
    return;
}
// This function unpacks the incoming CANopen massage and hand the received communication objects to global variables.
uint32_t unpack(uint8_t *SDO_Byte, uint16_t *index, uint8_t *sub_index, int32_t *value)
{
    uint16_t *pointer_index_Rx;
    int32_t *pointer_value_Rx;
    uint32_t *pointer_display;
    uint8_t index_array_Rx [2];
    int8_t value_array_Rx [4];
    uint8_t display_array [4];
    *SDO_Byte = pui8RxBuffer [0];
    index_array_Rx [0] = pui8RxBuffer [1];
    index_array_Rx [1]= pui8RxBuffer [2];
    *sub_index = pui8RxBuffer [3];
    value_array_Rx [0] = pui8RxBuffer [4];
    value_array_Rx [1] = pui8RxBuffer [5];
    value_array_Rx [2] = pui8RxBuffer [6];
    value_array_Rx [3] = pui8RxBuffer [7];
    display_array [0] = pui8RxBuffer [3];
    display_array [1] = pui8RxBuffer [1];
    display_array [2] = pui8RxBuffer [2];
    display_array [3] = pui8RxBuffer [0];
    pointer_index_Rx = index_array_Rx;
    pointer_value_Rx = value_array_Rx;
    pointer_display = display_array;
    *index = *pointer_index_Rx;
    *value = *pointer_value_Rx;
    return(*pointer_display);
}







