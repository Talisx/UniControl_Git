/*
 * uc_tasks.c
 *
 *  Created on: 10.08.2017
 *      Author: grewenig
 */

#include <stdbool.h>
#include <xdc/runtime/System.h>
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
#include "Init_Motor.h"
#include "canopenMsgHandler.h"

#include <stdio.h>
#include <string.h>

/*
 * Globlae Variablen hier einfügen
 */
//Torstens Variablen(Quintus Teil)
bool Data_ValidEnco = true;
bool Data_ValidWinkel = true;
int Nachricht_prüfer = 0;
int Nachrichten_prüfer1 = 0;
int8_t _500ms= 0;

//Torstens Variablen(Kimmer Teil)
int32_t vorherigerStrom = 0;
int32_t aktuellerStrom = 0;
int start_Motor = 0;
//bool initComplete = true;
bool testCD1 = true;
bool testCD2;
bool initComplete = true;

static char ui8State = 0;    //User state machine
uint8_t SDO_Byte;            //externVar in uc_can.h
uint16_t index;              // ""
uint8_t sub_index;           // ""
int32_t value;               // ""
unsigned int display;        // ""

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

	/*Teil für die Funktion bei Task 100ms */
	aktuellerStrom = (int32_t)Strom;


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
	/*Hier wird erstmal der Motor initialisiert, bevor etwas anderes gemacht wird*/
	if(initComplete == true && testCD1 == true)
	{
	    initMotor();
	    //Damit bei reconnect, wieder versucht wird die Verbindung zur Quintus Platine zu checken
	    Data_ValidEnco = true;
	    Data_ValidWinkel = true;
	}
	else if(initComplete == false && testCD1 == true)
	{
	    //Hier wird geprüft ob die Verbindung überhaupt noch besteht zur Quintus Platine
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
            //wenn 2 Nachrichten nicht richtig an kamen schalte Motor aus.
            else
            {
                pack(WRITING_SEND, CURRENT_MODE_SETTING_VALUE,0,0);
                CANMessageSet(CAN0_BASE, 5, &sMsgObjectDataTx, MSG_OBJ_TYPE_TX);
                initComplete = true;
            }
        }
        /*Hier der Teil, verschickt eine Can Nachricht, sobald der Strom in ControlDesk geändert wird*/
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
            else if(aktuellerStrom > 1000)
            {
                aktuellerStrom = 1000;
            }
            // neg Value left, pos Value right rotation
            /*
             *
             * Hier muss noch etwas dazu, damit es überhaupt Sinn macht, den neuen Strom Wert einzustellen
             * Außerdem muss hier etwas dazu, was schaut, welches Vorzeichen der Strom bekommen soll
             *
             *
             */

            pack(WRITING_SEND, CURRENT_MODE_SETTING_VALUE,0,aktuellerStrom);
            CANMessageSet(CAN0_BASE, 5, &sMsgObjectDataTx, MSG_OBJ_TYPE_TX);
            vorherigerStrom = aktuellerStrom;
            //printf("Current Mode activated\nCurrent value (mA): %d\n", CurrentModeSettingValue);
        }
	}
	else if(initComplete == false && testCD1 == false)
	{
	    initComplete = true;
	}
	else
	{
	    // tue nichts, da in CD ausgeschaltet und nicht initialisiert durch die switch Case in Init_Motor.
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
	// Hier ist die Fehlerabfrage, weil es sich ja um Master Slave System handelt, muss immer abgefragt werden
	switch(ui8State)
	    {
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
	                ui8State=0;
	                break;
	                        */
	    }
	// selbst erzeugter Task 500 ms
	//dient der überprüfung ob Verbindung zu Steuergerät noch besteht.
	if(_500ms == 5)
	{
	    if(connectionCheck == true)
	    {
	        connectionCheck = false;
	    }
	    else
	    {
	        // hier soll am besten Button nachher Rot in ControlDesk Leuchten
	        // Zeichen das nicht verbunden
	    }
	    _500ms = 0;
	}
	else
	{
	    _500ms++;
	}

	return;
}
