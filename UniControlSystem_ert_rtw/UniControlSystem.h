/*
 * File: UniControlSystem.h
 *
 * Code generated for Simulink model 'UniControlSystem'.
 *
 * Model version                  : 1.56
 * Simulink Coder version         : 8.8 (R2015a) 09-Feb-2015
 * C/C++ source code generated on : Wed Aug 26 13:41:54 2020
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
  real_T Integrator_DSTATE;            /* '<S2>/Integrator' */
  real_T Filter_DSTATE;                /* '<S2>/Filter' */
  real_T Integrator_DSTATE_l;          /* '<S1>/Integrator' */
  real_T Filter_DSTATE_m;              /* '<S1>/Filter' */
} DW;

/* Parameters (auto storage) */
struct P_ {
  real_T PID1_LowerSaturationLimit;    /* Mask Parameter: PID1_LowerSaturationLimit
                                        * Referenced by:
                                        *   '<S1>/Saturate'
                                        *   '<S3>/DeadZone'
                                        */
  real_T PID2_N;                       /* Mask Parameter: PID2_N
                                        * Referenced by: '<S2>/Filter Coefficient'
                                        */
  real_T PID1_N;                       /* Mask Parameter: PID1_N
                                        * Referenced by: '<S1>/Filter Coefficient'
                                        */
  real_T PID1_UpperSaturationLimit;    /* Mask Parameter: PID1_UpperSaturationLimit
                                        * Referenced by:
                                        *   '<S1>/Saturate'
                                        *   '<S3>/DeadZone'
                                        */
  real_T Gain1_Gain;                   /* Expression: -1
                                        * Referenced by: '<Root>/Gain1'
                                        */
  real_T Gain_Gain;                    /* Expression: 1
                                        * Referenced by: '<Root>/Gain'
                                        */
  real_T Integrator_gainval;           /* Computed Parameter: Integrator_gainval
                                        * Referenced by: '<S2>/Integrator'
                                        */
  real_T Integrator_IC;                /* Expression: InitialConditionForIntegrator
                                        * Referenced by: '<S2>/Integrator'
                                        */
  real_T Filter_gainval;               /* Computed Parameter: Filter_gainval
                                        * Referenced by: '<S2>/Filter'
                                        */
  real_T Filter_IC;                    /* Expression: InitialConditionForFilter
                                        * Referenced by: '<S2>/Filter'
                                        */
  real_T Integrator_gainval_b;         /* Computed Parameter: Integrator_gainval_b
                                        * Referenced by: '<S1>/Integrator'
                                        */
  real_T Integrator_IC_m;              /* Expression: InitialConditionForIntegrator
                                        * Referenced by: '<S1>/Integrator'
                                        */
  real_T Filter_gainval_i;             /* Computed Parameter: Filter_gainval_i
                                        * Referenced by: '<S1>/Filter'
                                        */
  real_T Filter_IC_k;                  /* Expression: InitialConditionForFilter
                                        * Referenced by: '<S1>/Filter'
                                        */
  real_T ZeroGain_Gain;                /* Expression: 0
                                        * Referenced by: '<S3>/ZeroGain'
                                        */
  real_T Constant_Value;               /* Expression: 0
                                        * Referenced by: '<S1>/Constant'
                                        */
  real_T ZeroGain_Gain_c;              /* Expression: 0
                                        * Referenced by: '<S4>/ZeroGain'
                                        */
  real_T Constant_Value_i;             /* Expression: 0
                                        * Referenced by: '<S2>/Constant'
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
extern real_T Phi_PID_D;               /* Variable: Phi_PID_D
                                        * Referenced by: '<S1>/Derivative Gain'
                                        */
extern real_T Phi_PID_I;               /* Variable: Phi_PID_I
                                        * Referenced by: '<S1>/Integral Gain'
                                        */
extern real_T Phi_PID_P;               /* Variable: Phi_PID_P
                                        * Referenced by: '<S1>/Proportional Gain'
                                        */
extern real_T Position;                /* Variable: Position
                                        * Referenced by: '<Root>/Constant1'
                                        */
extern real_T Strom;                   /* Variable: Strom
                                        * Referenced by: '<Root>/Constant2'
                                        */
extern real_T x_PID_D;                 /* Variable: x_PID_D
                                        * Referenced by: '<S2>/Derivative Gain'
                                        */
extern real_T x_PID_HLIM;              /* Variable: x_PID_HLIM
                                        * Referenced by:
                                        *   '<S2>/Saturate'
                                        *   '<S4>/DeadZone'
                                        */
extern real_T x_PID_I;                 /* Variable: x_PID_I
                                        * Referenced by: '<S2>/Integral Gain'
                                        */
extern real_T x_PID_LLIM;              /* Variable: x_PID_LLIM
                                        * Referenced by:
                                        *   '<S2>/Saturate'
                                        *   '<S4>/DeadZone'
                                        */
extern real_T x_PID_P;                 /* Variable: x_PID_P
                                        * Referenced by: '<S2>/Proportional Gain'
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
 * '<S1>'   : 'UniControlSystem/PID1'
 * '<S2>'   : 'UniControlSystem/PID2'
 * '<S3>'   : 'UniControlSystem/PID1/Clamping circuit'
 * '<S4>'   : 'UniControlSystem/PID2/Clamping circuit'
 */
#endif                                 /* RTW_HEADER_UniControlSystem_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
