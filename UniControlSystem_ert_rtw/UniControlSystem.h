/*
 * File: UniControlSystem.h
 *
 * Code generated for Simulink model 'UniControlSystem'.
 *
 * Model version                  : 1.59
 * Simulink Coder version         : 8.8 (R2015a) 09-Feb-2015
 * C/C++ source code generated on : Mon Sep 30 16:24:27 2019
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_UniControlSystem_h_
#define RTW_HEADER_UniControlSystem_h_
#include "rtwtypes.h"
#include <stddef.h>
#include <string.h>
#ifndef UniControlSystem_COMMON_INCLUDES_
# define UniControlSystem_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* UniControlSystem_COMMON_INCLUDES_ */

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

#define UniControlSystem_M             (rtM)

/* Forward declaration for rtModel */
typedef struct tag_RTM RT_MODEL;

/* Block states (auto storage) for system '<Root>' */
typedef struct {
  real_T Integrator_DSTATE;            /* '<S1>/Integrator' */
  real_T Filter_DSTATE;                /* '<S1>/Filter' */
} DW;

/* Parameters (auto storage) */
struct P_ {
  real_T PID1_N;                       /* Mask Parameter: PID1_N
                                        * Referenced by: '<S1>/Filter Coefficient'
                                        */
  real_T Integrator_gainval;           /* Computed Parameter: Integrator_gainval
                                        * Referenced by: '<S1>/Integrator'
                                        */
  real_T Integrator_IC;                /* Expression: InitialConditionForIntegrator
                                        * Referenced by: '<S1>/Integrator'
                                        */
  real_T Filter_gainval;               /* Computed Parameter: Filter_gainval
                                        * Referenced by: '<S1>/Filter'
                                        */
  real_T Filter_IC;                    /* Expression: InitialConditionForFilter
                                        * Referenced by: '<S1>/Filter'
                                        */
  real_T ZeroGain_Gain;                /* Expression: 0
                                        * Referenced by: '<S2>/ZeroGain'
                                        */
  real_T Constant_Value;               /* Expression: 0
                                        * Referenced by: '<S1>/Constant'
                                        */
  real_T Constant_Value_c;             /* Expression: 0
                                        * Referenced by: '<Root>/Constant'
                                        */
};

/* Parameters (auto storage) */
typedef struct P_ P;

/* Real-time Model Data Structure */
struct tag_RTM {
  const char_T *errorStatus;
};

/* Block parameters (auto storage) */
extern P rtP;

/* Block states (auto storage) */
extern DW rtDW;

/*
 * Exported Global Parameters
 *
 * Note: Exported global parameters are tunable parameters with an exported
 * global storage class designation.  Code generation will declare the memory for
 * these parameters and exports their symbols.
 *
 */
extern real_T PID_D;                   /* Variable: PID_D
                                        * Referenced by: '<S1>/Derivative Gain'
                                        */
extern real_T PID_HLIM;                /* Variable: PID_HLIM
                                        * Referenced by:
                                        *   '<S1>/Saturate'
                                        *   '<S2>/DeadZone'
                                        */
extern real_T PID_I;                   /* Variable: PID_I
                                        * Referenced by: '<S1>/Integral Gain'
                                        */
extern real_T PID_LLIM;                /* Variable: PID_LLIM
                                        * Referenced by:
                                        *   '<S1>/Saturate'
                                        *   '<S2>/DeadZone'
                                        */
extern real_T PID_P;                   /* Variable: PID_P
                                        * Referenced by: '<S1>/Proportional Gain'
                                        */
extern real_T Sollwert;                /* Variable: Sollwert
                                        * Referenced by: '<Root>/Constant1'
                                        */

/* Model entry point functions */
extern void UniControlSystem_Init(void);

/* Customized model step function */
extern void UniControlSystem_Step(real_T arg_In1, real_T arg_In2, real_T arg_In3,
  real_T arg_In4, real_T arg_In5, real_T arg_In6, real_T arg_In7, real_T arg_In8,
  real_T arg_In9, real_T arg_In10, real_T arg_In11, real_T arg_In12, real_T
  arg_In13, real_T arg_In14, real_T arg_In15, real_T arg_In16, real_T *arg_Out1,
  real_T *arg_Out2, real_T *arg_Out3, real_T *arg_Out4, real_T *arg_Out5, real_T
  *arg_Out6, real_T *arg_Out7, real_T *arg_Out8, real_T *arg_Out9, real_T
  *arg_Out10, real_T *arg_Out11, real_T *arg_Out12, real_T *arg_Out13, real_T
  *arg_Out14, real_T *arg_Out15, real_T *arg_Out16);

/* Real-time Model object */
extern RT_MODEL *const rtM;

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'UniControlSystem'
 * '<S1>'   : 'UniControlSystem/PID1 '
 * '<S2>'   : 'UniControlSystem/PID1 /Clamping circuit'
 */
#endif                                 /* RTW_HEADER_UniControlSystem_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
