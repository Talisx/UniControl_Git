/*
 * uc_can.c
 *
 *  Created on: 10.08.2017
 *      Author: grewenig
 */

#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_gpio.h"
#include "inc/hw_can.h"
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "driverlib/can.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"


#include "inc/hw_qei.h" // Macros for usage with the quadrature
#include "driverlib/sysctl.h" // Prototypes for the SysCtl driver.
#include "driverlib/qei.h" // Macros for usage with the quadrature

#include "uc_can.h"

//*****************************************************************************
//
// Initialize the CAN0 module.
//
// CAN0 is routed to pins PA0, PA1 and configured for 1 MBit operation.
// Interrupts are enabled for the CAN controller.
//
// CAN0 is used for process communication.
//
//*****************************************************************************

void InitCAN0(void)
{
    //Test Nachricht, welche gelöscht werden kann
	/* Enable port A and wait until ready */
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
	while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOA));
	/* Set PA0 and PA1 to be CAN0 RX and TX */
	GPIOPinConfigure(GPIO_PA0_CAN0RX);
	GPIOPinConfigure(GPIO_PA1_CAN0TX);
	GPIOPinTypeCAN(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);
	/* Enable CAN0 peripheral */
	SysCtlPeripheralEnable(SYSCTL_PERIPH_CAN0);
	/* Initialize the CAN to a known state*/
	CANInit(CAN0_BASE);
	/* Set up the CAN fpr 1 MBit operation */
	CANBitRateSet(CAN0_BASE, ui32SysClock, CAN0_BAUDRATE);
	/* Set auto-retry to off */
	CANRetrySet(CAN0_BASE, 0);
	/* Interrupts */
	CANIntEnable(CAN0_BASE, CAN_INT_MASTER);
	IntEnable(INT_CAN0);
	/* Take CAN0 out of INIT state*/
	CANEnable(CAN0_BASE);
	return;
}

//*****************************************************************************
//
// Configure the CAN0 message objects.
//
// TX and RX interrupts are configured.
//
//*****************************************************************************

void InitCAN0MsgObjects(void)
{
	/* Initialize data request message object (TX direction) */
	sMsgObjectDataTx.ui32MsgID 	= 0x0600 + 0b00000001;
	sMsgObjectDataTx.ui32Flags 	= MSG_OBJ_TX_INT_ENABLE;
	sMsgObjectDataTx.ui32MsgIDMask = 0x0000;
	sMsgObjectDataTx.ui32MsgLen 	= 8;
	sMsgObjectDataTx.pui8MsgData 	= pui8TxBuffer;
	CANMessageSet(CAN0_BASE, 1, &sMsgObjectDataTx, MSG_OBJ_TYPE_TX);

	/* Initialize data receive message objects (RX direction ) */
	sMsgObjectDataRx.ui32MsgID = 0x0580+0b00000001;
	sMsgObjectDataRx.ui32MsgIDMask = 0xFFFF;
	sMsgObjectDataRx.ui32Flags = (MSG_OBJ_RX_INT_ENABLE | MSG_OBJ_USE_ID_FILTER);
	sMsgObjectDataRx.ui32MsgLen = 8;
	CANMessageSet ( CAN0_BASE , 2, &sMsgObjectDataRx ,MSG_OBJ_TYPE_RX );



	return;
}

//*****************************************************************************
//
// CAN0 interrupt handler.
//
// Upon a CAN0 interrupt, the controller status is checked and saved.
// The status changes depending on which message object caused the interrupt.
//
// A 'receive mask' is used to store the receive event of each RX message.
// The processing task is suspended until the receive mask is complete, i.e.
// all new data has been received and updated.
//
// The TX handler is called for TX message objects. In case of a data request
// the interrupt flag is cleared by software and the receive mask is cleared.
//
// The RX handler is called for RX message objects. The interrupt flags are
// cleared accordingly by software. The messaged object data pointer is set to
// the first element of the global data variable (array). Data is then stored
// in the global data variable and the receive mask is added to.
//
//*****************************************************************************

void CAN0IntHandler(void)
{
	static uint32_t ui32Status 		= 0;

	ui32Status = CANIntStatus(CAN0_BASE, CAN_INT_STS_CAUSE);
	/* Switch for message object */
	switch(ui32Status)
	{
		/* TX handler */
		case 1:		CANIntClear(CAN0_BASE, 1);
		            break;

		/* RX handler */
		case 2:     CANIntClear(CAN0_BASE, 2);
		            ui32CanRxFlags = (ui32CanRxFlags | 0b10);
		            break;
		/*pending status error */
		case 32768: CANIntClear(CAN0_BASE, CAN_INT_INTID_STATUS);
		          //  printf("Status Error \n");
		            break;

		/* Unused message objects: These should never trigger */
		default:	break;
	}
	return;
}
