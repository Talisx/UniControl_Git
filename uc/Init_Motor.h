/*
 * Init_Motor.h
 *
 *  Created on: 26.08.2020
 *      Author: grewenig
 */

#ifndef UC_INIT_MOTOR_H_
#define UC_INIT_MOTOR_H_

extern void initMotor(void);
extern bool initComplete;
extern enum state{ FAULTRESET, OUT, ON, ENABLEOP, CURRENTMODE, SETTINGCURRENT};
extern enum state machineState;



#endif /* UC_INIT_MOTOR_H_ */
