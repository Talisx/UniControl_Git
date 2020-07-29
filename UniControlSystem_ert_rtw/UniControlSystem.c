/*
 * File: UniControlSystem.c
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

#include "UniControlSystem.h"

/* Exported block parameters */
real_T PID_D = 0.0;                    /* Variable: PID_D
                                        * Referenced by: '<S1>/Derivative Gain'
                                        */
real_T PID_HLIM = 9.0;                 /* Variable: PID_HLIM
                                        * Referenced by:
                                        *   '<S1>/Saturate'
                                        *   '<S2>/DeadZone'
                                        */
real_T PID_I = 0.0;                    /* Variable: PID_I
                                        * Referenced by: '<S1>/Integral Gain'
                                        */
real_T PID_LLIM = -9.0;                /* Variable: PID_LLIM
                                        * Referenced by:
                                        *   '<S1>/Saturate'
                                        *   '<S2>/DeadZone'
                                        */
real_T PID_P = 0.0;                    /* Variable: PID_P
                                        * Referenced by: '<S1>/Proportional Gain'
                                        */
real_T Sollwert = 0.0;                 /* Variable: Sollwert
                                        * Referenced by: '<Root>/Constant1'
                                        */

/* Block parameters (auto storage) */
P rtP = {
  1.0,                                 /* Mask Parameter: PID1_N
                                        * Referenced by: '<S1>/Filter Coefficient'
                                        */
  0.01,                                /* Computed Parameter: Integrator_gainval
                                        * Referenced by: '<S1>/Integrator'
                                        */
  0.0,                                 /* Expression: InitialConditionForIntegrator
                                        * Referenced by: '<S1>/Integrator'
                                        */
  0.01,                                /* Computed Parameter: Filter_gainval
                                        * Referenced by: '<S1>/Filter'
                                        */
  0.0,                                 /* Expression: InitialConditionForFilter
                                        * Referenced by: '<S1>/Filter'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S2>/ZeroGain'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S1>/Constant'
                                        */
  0.0                                  /* Expression: 0
                                        * Referenced by: '<Root>/Constant'
                                        */
};

/* Block states (auto storage) */
DW rtDW;

/* Real-time model */
RT_MODEL rtM_;
RT_MODEL *const rtM = &rtM_;

/*===========*
 * Constants *
 *===========*/
#define RT_PI                          3.14159265358979323846
#define RT_PIF                         3.1415927F
#define RT_LN_10                       2.30258509299404568402
#define RT_LN_10F                      2.3025851F
#define RT_LOG10E                      0.43429448190325182765
#define RT_LOG10EF                     0.43429449F
#define RT_E                           2.7182818284590452354
#define RT_EF                          2.7182817F

/*
 * UNUSED_PARAMETER(x)
 *   Used to specify that a function parameter (argument) is required but not
 *   accessed by the function body.
 */
#ifndef UNUSED_PARAMETER
# if defined(__LCC__)
#   define UNUSED_PARAMETER(x)                                   /* do nothing */
# else

/*
 * This is the semi-ANSI standard way of indicating that an
 * unused function parameter is required.
 */
#   define UNUSED_PARAMETER(x)         (void) (x)
# endif
#endif

/* Model step function */
void UniControlSystem_Step(real_T arg_In1, real_T arg_In2, real_T arg_In3,
  real_T arg_In4, real_T arg_In5, real_T arg_In6, real_T arg_In7, real_T arg_In8,
  real_T arg_In9, real_T arg_In10, real_T arg_In11, real_T arg_In12, real_T
  arg_In13, real_T arg_In14, real_T arg_In15, real_T arg_In16, real_T *arg_Out1,
  real_T *arg_Out2, real_T *arg_Out3, real_T *arg_Out4, real_T *arg_Out5, real_T
  *arg_Out6, real_T *arg_Out7, real_T *arg_Out8, real_T *arg_Out9, real_T
  *arg_Out10, real_T *arg_Out11, real_T *arg_Out12, real_T *arg_Out13, real_T
  *arg_Out14, real_T *arg_Out15, real_T *arg_Out16)
{
  real_T rtb_IntegralGain;
  real_T rtb_SignDeltaU;
  real_T rtb_FilterCoefficient;
  real_T rtb_ZeroGain;
  boolean_T rtb_NotEqual;
  int8_T rtb_SignDeltaU_0;
  UNUSED_PARAMETER(arg_In2);
  UNUSED_PARAMETER(arg_In3);
  UNUSED_PARAMETER(arg_In4);
  UNUSED_PARAMETER(arg_In5);
  UNUSED_PARAMETER(arg_In6);
  UNUSED_PARAMETER(arg_In7);
  UNUSED_PARAMETER(arg_In8);
  UNUSED_PARAMETER(arg_In9);
  UNUSED_PARAMETER(arg_In10);
  UNUSED_PARAMETER(arg_In11);
  UNUSED_PARAMETER(arg_In12);
  UNUSED_PARAMETER(arg_In13);
  UNUSED_PARAMETER(arg_In14);
  UNUSED_PARAMETER(arg_In15);
  UNUSED_PARAMETER(arg_In16);

  /* Sum: '<Root>/Sub1 ' incorporates:
   *  Constant: '<Root>/Constant1'
   *  Inport: '<Root>/In1'
   */
  rtb_IntegralGain = Sollwert - arg_In1;

  /* Gain: '<S1>/Filter Coefficient' incorporates:
   *  DiscreteIntegrator: '<S1>/Filter'
   *  Gain: '<S1>/Derivative Gain'
   *  Sum: '<S1>/SumD'
   */
  rtb_FilterCoefficient = (PID_D * rtb_IntegralGain - rtDW.Filter_DSTATE) *
    rtP.PID1_N;

  /* Sum: '<S1>/Sum' incorporates:
   *  DiscreteIntegrator: '<S1>/Integrator'
   *  Gain: '<S1>/Proportional Gain'
   */
  rtb_SignDeltaU = (PID_P * rtb_IntegralGain + rtDW.Integrator_DSTATE) +
    rtb_FilterCoefficient;

  /* Saturate: '<S1>/Saturate' */
  if (rtb_SignDeltaU > PID_HLIM) {
    /* Outport: '<Root>/Out1' */
    *arg_Out1 = PID_HLIM;
  } else if (rtb_SignDeltaU < PID_LLIM) {
    /* Outport: '<Root>/Out1' */
    *arg_Out1 = PID_LLIM;
  } else {
    /* Outport: '<Root>/Out1' */
    *arg_Out1 = rtb_SignDeltaU;
  }

  /* End of Saturate: '<S1>/Saturate' */

  /* Gain: '<S2>/ZeroGain' */
  rtb_ZeroGain = rtP.ZeroGain_Gain * rtb_SignDeltaU;

  /* DeadZone: '<S2>/DeadZone' */
  if (rtb_SignDeltaU > PID_HLIM) {
    rtb_SignDeltaU -= PID_HLIM;
  } else if (rtb_SignDeltaU >= PID_LLIM) {
    rtb_SignDeltaU = 0.0;
  } else {
    rtb_SignDeltaU -= PID_LLIM;
  }

  /* End of DeadZone: '<S2>/DeadZone' */

  /* RelationalOperator: '<S2>/NotEqual' */
  rtb_NotEqual = (rtb_ZeroGain != rtb_SignDeltaU);

  /* Signum: '<S2>/SignDeltaU' */
  if (rtb_SignDeltaU < 0.0) {
    rtb_SignDeltaU = -1.0;
  } else {
    if (rtb_SignDeltaU > 0.0) {
      rtb_SignDeltaU = 1.0;
    }
  }

  /* End of Signum: '<S2>/SignDeltaU' */

  /* Gain: '<S1>/Integral Gain' */
  rtb_IntegralGain *= PID_I;

  /* Outport: '<Root>/Out2' incorporates:
   *  Constant: '<Root>/Constant'
   */
  *arg_Out2 = rtP.Constant_Value_c;

  /* Outport: '<Root>/Out3' incorporates:
   *  Constant: '<Root>/Constant'
   */
  *arg_Out3 = rtP.Constant_Value_c;

  /* Outport: '<Root>/Out4' incorporates:
   *  Constant: '<Root>/Constant'
   */
  *arg_Out4 = rtP.Constant_Value_c;

  /* Outport: '<Root>/Out5' incorporates:
   *  Constant: '<Root>/Constant'
   */
  *arg_Out5 = rtP.Constant_Value_c;

  /* Outport: '<Root>/Out6' incorporates:
   *  Constant: '<Root>/Constant'
   */
  *arg_Out6 = rtP.Constant_Value_c;

  /* Outport: '<Root>/Out7' incorporates:
   *  Constant: '<Root>/Constant'
   */
  *arg_Out7 = rtP.Constant_Value_c;

  /* Outport: '<Root>/Out8' incorporates:
   *  Constant: '<Root>/Constant'
   */
  *arg_Out8 = rtP.Constant_Value_c;

  /* Outport: '<Root>/Out9' incorporates:
   *  Constant: '<Root>/Constant'
   */
  *arg_Out9 = rtP.Constant_Value_c;

  /* Outport: '<Root>/Out10' incorporates:
   *  Constant: '<Root>/Constant'
   */
  *arg_Out10 = rtP.Constant_Value_c;

  /* Outport: '<Root>/Out11' incorporates:
   *  Constant: '<Root>/Constant'
   */
  *arg_Out11 = rtP.Constant_Value_c;

  /* Outport: '<Root>/Out12' incorporates:
   *  Constant: '<Root>/Constant'
   */
  *arg_Out12 = rtP.Constant_Value_c;

  /* Outport: '<Root>/Out13' incorporates:
   *  Constant: '<Root>/Constant'
   */
  *arg_Out13 = rtP.Constant_Value_c;

  /* Outport: '<Root>/Out14' incorporates:
   *  Constant: '<Root>/Constant'
   */
  *arg_Out14 = rtP.Constant_Value_c;

  /* Outport: '<Root>/Out15' incorporates:
   *  Constant: '<Root>/Constant'
   */
  *arg_Out15 = rtP.Constant_Value_c;

  /* Outport: '<Root>/Out16' incorporates:
   *  Constant: '<Root>/Constant'
   */
  *arg_Out16 = rtP.Constant_Value_c;

  /* DataTypeConversion: '<S2>/DataTypeConv1' */
  if (rtb_SignDeltaU < 128.0) {
    rtb_SignDeltaU_0 = (int8_T)rtb_SignDeltaU;
  } else {
    rtb_SignDeltaU_0 = MAX_int8_T;
  }

  /* End of DataTypeConversion: '<S2>/DataTypeConv1' */

  /* Signum: '<S2>/SignPreIntegrator' */
  if (rtb_IntegralGain < 0.0) {
    rtb_SignDeltaU = -1.0;
  } else if (rtb_IntegralGain > 0.0) {
    rtb_SignDeltaU = 1.0;
  } else {
    rtb_SignDeltaU = rtb_IntegralGain;
  }

  /* Switch: '<S1>/Switch' incorporates:
   *  Constant: '<S1>/Constant'
   *  DataTypeConversion: '<S2>/DataTypeConv2'
   *  Logic: '<S2>/AND'
   *  RelationalOperator: '<S2>/Equal'
   *  Signum: '<S2>/SignPreIntegrator'
   */
  if (rtb_NotEqual && (rtb_SignDeltaU_0 == (int8_T)rtb_SignDeltaU)) {
    rtb_IntegralGain = rtP.Constant_Value;
  }

  /* End of Switch: '<S1>/Switch' */

  /* Update for DiscreteIntegrator: '<S1>/Integrator' */
  rtDW.Integrator_DSTATE += rtP.Integrator_gainval * rtb_IntegralGain;

  /* Update for DiscreteIntegrator: '<S1>/Filter' */
  rtDW.Filter_DSTATE += rtP.Filter_gainval * rtb_FilterCoefficient;
}

/* Model initialize function */
void UniControlSystem_Init(void)
{
  /* Registration code */

  /* initialize error status */
  rtmSetErrorStatus(rtM, (NULL));

  /* states (dwork) */
  (void) memset((void *)&rtDW, 0,
                sizeof(DW));

  /* InitializeConditions for DiscreteIntegrator: '<S1>/Integrator' */
  rtDW.Integrator_DSTATE = rtP.Integrator_IC;

  /* InitializeConditions for DiscreteIntegrator: '<S1>/Filter' */
  rtDW.Filter_DSTATE = rtP.Filter_IC;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
