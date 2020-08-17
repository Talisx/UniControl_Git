/*
 * File: UniControlSystem.c
 *
 * Code generated for Simulink model 'UniControlSystem'.
 *
 * Model version                  : 1.55
 * Simulink Coder version         : 8.8 (R2015a) 09-Feb-2015
 * C/C++ source code generated on : Thu Aug 06 11:54:25 2020
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "UniControlSystem.h"

/* Exported block parameters */
real_T Phi_PID_D = 0.0;                /* Variable: Phi_PID_D
                                        * Referenced by: '<S1>/Derivative Gain'
                                        */
real_T Phi_PID_I = 0.0;                /* Variable: Phi_PID_I
                                        * Referenced by: '<S1>/Integral Gain'
                                        */
real_T Phi_PID_P = 0.0;                /* Variable: Phi_PID_P
                                        * Referenced by: '<S1>/Proportional Gain'
                                        */
real_T Position = 0.0;                 /* Variable: Position
                                        * Referenced by: '<Root>/Constant1'
                                        */
real_T x_PID_D = 0.0;                  /* Variable: x_PID_D
                                        * Referenced by: '<S2>/Derivative Gain'
                                        */
real_T x_PID_HLIM = 9.0;               /* Variable: x_PID_HLIM
                                        * Referenced by:
                                        *   '<S2>/Saturate'
                                        *   '<S4>/DeadZone'
                                        */
real_T x_PID_I = 0.0;                  /* Variable: x_PID_I
                                        * Referenced by: '<S2>/Integral Gain'
                                        */
real_T x_PID_LLIM = -9.0;              /* Variable: x_PID_LLIM
                                        * Referenced by:
                                        *   '<S2>/Saturate'
                                        *   '<S4>/DeadZone'
                                        */
real_T x_PID_P = 0.0;                  /* Variable: x_PID_P
                                        * Referenced by: '<S2>/Proportional Gain'
                                        */

/* Block parameters (auto storage) */
P rtP = {
  -2.0,                                /* Mask Parameter: PID1_LowerSaturationLimit
                                        * Referenced by:
                                        *   '<S1>/Saturate'
                                        *   '<S3>/DeadZone'
                                        */
  1.0,                                 /* Mask Parameter: PID2_N
                                        * Referenced by: '<S2>/Filter Coefficient'
                                        */
  10.0,                                /* Mask Parameter: PID1_N
                                        * Referenced by: '<S1>/Filter Coefficient'
                                        */
  2.0,                                 /* Mask Parameter: PID1_UpperSaturationLimit
                                        * Referenced by:
                                        *   '<S1>/Saturate'
                                        *   '<S3>/DeadZone'
                                        */
  -1.0,                                /* Expression: -1
                                        * Referenced by: '<Root>/Gain1'
                                        */
  1.0,                                 /* Expression: 1
                                        * Referenced by: '<Root>/Gain'
                                        */
  0.01,                                /* Computed Parameter: Integrator_gainval
                                        * Referenced by: '<S2>/Integrator'
                                        */
  0.0,                                 /* Expression: InitialConditionForIntegrator
                                        * Referenced by: '<S2>/Integrator'
                                        */
  0.01,                                /* Computed Parameter: Filter_gainval
                                        * Referenced by: '<S2>/Filter'
                                        */
  0.0,                                 /* Expression: InitialConditionForFilter
                                        * Referenced by: '<S2>/Filter'
                                        */
  0.01,                                /* Computed Parameter: Integrator_gainval_b
                                        * Referenced by: '<S1>/Integrator'
                                        */
  0.0,                                 /* Expression: InitialConditionForIntegrator
                                        * Referenced by: '<S1>/Integrator'
                                        */
  0.01,                                /* Computed Parameter: Filter_gainval_i
                                        * Referenced by: '<S1>/Filter'
                                        */
  0.0,                                 /* Expression: InitialConditionForFilter
                                        * Referenced by: '<S1>/Filter'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S3>/ZeroGain'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S1>/Constant'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S4>/ZeroGain'
                                        */
  0.0,                                 /* Expression: 0
                                        * Referenced by: '<S2>/Constant'
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
  real_T rtb_IntegralGain_a;
  real_T rtb_FilterCoefficient;
  real_T rtb_SignDeltaU_o;
  real_T rtb_FilterCoefficient_n;
  real_T rtb_ZeroGain;
  boolean_T rtb_NotEqual;
  boolean_T rtb_NotEqual_f;
  int8_T rtb_SignDeltaU_1;
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

  /* Sum: '<Root>/Sub2' incorporates:
   *  Constant: '<Root>/Constant1'
   *  Gain: '<Root>/Gain'
   *  Gain: '<Root>/Gain1'
   *  Inport: '<Root>/In2'
   */
  rtb_IntegralGain = rtP.Gain1_Gain * Position - rtP.Gain_Gain * arg_In2;

  /* Gain: '<S2>/Filter Coefficient' incorporates:
   *  DiscreteIntegrator: '<S2>/Filter'
   *  Gain: '<S2>/Derivative Gain'
   *  Sum: '<S2>/SumD'
   */
  rtb_FilterCoefficient = (x_PID_D * rtb_IntegralGain - rtDW.Filter_DSTATE) *
    rtP.PID2_N;

  /* Sum: '<S2>/Sum' incorporates:
   *  DiscreteIntegrator: '<S2>/Integrator'
   *  Gain: '<S2>/Proportional Gain'
   */
  rtb_SignDeltaU = (x_PID_P * rtb_IntegralGain + rtDW.Integrator_DSTATE) +
    rtb_FilterCoefficient;

  /* Saturate: '<S2>/Saturate' */
  if (rtb_SignDeltaU > x_PID_HLIM) {
    rtb_ZeroGain = x_PID_HLIM;
  } else if (rtb_SignDeltaU < x_PID_LLIM) {
    rtb_ZeroGain = x_PID_LLIM;
  } else {
    rtb_ZeroGain = rtb_SignDeltaU;
  }

  /* Sum: '<Root>/Sub1' incorporates:
   *  Inport: '<Root>/In1'
   *  Saturate: '<S2>/Saturate'
   */
  rtb_IntegralGain_a = rtb_ZeroGain - arg_In1;

  /* Gain: '<S1>/Filter Coefficient' incorporates:
   *  DiscreteIntegrator: '<S1>/Filter'
   *  Gain: '<S1>/Derivative Gain'
   *  Sum: '<S1>/SumD'
   */
  rtb_FilterCoefficient_n = (Phi_PID_D * rtb_IntegralGain_a -
    rtDW.Filter_DSTATE_m) * rtP.PID1_N;

  /* Sum: '<S1>/Sum' incorporates:
   *  DiscreteIntegrator: '<S1>/Integrator'
   *  Gain: '<S1>/Proportional Gain'
   */
  rtb_SignDeltaU_o = (Phi_PID_P * rtb_IntegralGain_a + rtDW.Integrator_DSTATE_l)
    + rtb_FilterCoefficient_n;

  /* Saturate: '<S1>/Saturate' */
  if (rtb_SignDeltaU_o > rtP.PID1_UpperSaturationLimit) {
    /* Outport: '<Root>/Out1' */
    *arg_Out1 = rtP.PID1_UpperSaturationLimit;
  } else if (rtb_SignDeltaU_o < rtP.PID1_LowerSaturationLimit) {
    /* Outport: '<Root>/Out1' */
    *arg_Out1 = rtP.PID1_LowerSaturationLimit;
  } else {
    /* Outport: '<Root>/Out1' */
    *arg_Out1 = rtb_SignDeltaU_o;
  }

  /* End of Saturate: '<S1>/Saturate' */

  /* Gain: '<S3>/ZeroGain' */
  rtb_ZeroGain = rtP.ZeroGain_Gain * rtb_SignDeltaU_o;

  /* DeadZone: '<S3>/DeadZone' */
  if (rtb_SignDeltaU_o > rtP.PID1_UpperSaturationLimit) {
    rtb_SignDeltaU_o -= rtP.PID1_UpperSaturationLimit;
  } else if (rtb_SignDeltaU_o >= rtP.PID1_LowerSaturationLimit) {
    rtb_SignDeltaU_o = 0.0;
  } else {
    rtb_SignDeltaU_o -= rtP.PID1_LowerSaturationLimit;
  }

  /* End of DeadZone: '<S3>/DeadZone' */

  /* RelationalOperator: '<S3>/NotEqual' */
  rtb_NotEqual = (rtb_ZeroGain != rtb_SignDeltaU_o);

  /* Signum: '<S3>/SignDeltaU' */
  if (rtb_SignDeltaU_o < 0.0) {
    rtb_SignDeltaU_o = -1.0;
  } else {
    if (rtb_SignDeltaU_o > 0.0) {
      rtb_SignDeltaU_o = 1.0;
    }
  }

  /* End of Signum: '<S3>/SignDeltaU' */

  /* Gain: '<S1>/Integral Gain' */
  rtb_IntegralGain_a *= Phi_PID_I;

  /* Gain: '<S4>/ZeroGain' */
  rtb_ZeroGain = rtP.ZeroGain_Gain_c * rtb_SignDeltaU;

  /* DeadZone: '<S4>/DeadZone' */
  if (rtb_SignDeltaU > x_PID_HLIM) {
    rtb_SignDeltaU -= x_PID_HLIM;
  } else if (rtb_SignDeltaU >= x_PID_LLIM) {
    rtb_SignDeltaU = 0.0;
  } else {
    rtb_SignDeltaU -= x_PID_LLIM;
  }

  /* End of DeadZone: '<S4>/DeadZone' */

  /* RelationalOperator: '<S4>/NotEqual' */
  rtb_NotEqual_f = (rtb_ZeroGain != rtb_SignDeltaU);

  /* Signum: '<S4>/SignDeltaU' */
  if (rtb_SignDeltaU < 0.0) {
    rtb_SignDeltaU = -1.0;
  } else {
    if (rtb_SignDeltaU > 0.0) {
      rtb_SignDeltaU = 1.0;
    }
  }

  /* End of Signum: '<S4>/SignDeltaU' */

  /* Gain: '<S2>/Integral Gain' */
  rtb_IntegralGain *= x_PID_I;

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

  /* DataTypeConversion: '<S4>/DataTypeConv1' */
  if (rtb_SignDeltaU < 128.0) {
    rtb_SignDeltaU_1 = (int8_T)rtb_SignDeltaU;
  } else {
    rtb_SignDeltaU_1 = MAX_int8_T;
  }

  /* End of DataTypeConversion: '<S4>/DataTypeConv1' */

  /* Signum: '<S4>/SignPreIntegrator' */
  if (rtb_IntegralGain < 0.0) {
    rtb_ZeroGain = -1.0;
  } else if (rtb_IntegralGain > 0.0) {
    rtb_ZeroGain = 1.0;
  } else {
    rtb_ZeroGain = rtb_IntegralGain;
  }

  /* Switch: '<S2>/Switch' incorporates:
   *  Constant: '<S2>/Constant'
   *  DataTypeConversion: '<S4>/DataTypeConv2'
   *  Logic: '<S4>/AND'
   *  RelationalOperator: '<S4>/Equal'
   *  Signum: '<S4>/SignPreIntegrator'
   */
  if (rtb_NotEqual_f && (rtb_SignDeltaU_1 == (int8_T)rtb_ZeroGain)) {
    rtb_IntegralGain = rtP.Constant_Value_i;
  }

  /* End of Switch: '<S2>/Switch' */

  /* Update for DiscreteIntegrator: '<S2>/Integrator' */
  rtDW.Integrator_DSTATE += rtP.Integrator_gainval * rtb_IntegralGain;

  /* Update for DiscreteIntegrator: '<S2>/Filter' */
  rtDW.Filter_DSTATE += rtP.Filter_gainval * rtb_FilterCoefficient;

  /* DataTypeConversion: '<S3>/DataTypeConv1' */
  if (rtb_SignDeltaU_o < 128.0) {
    rtb_SignDeltaU_1 = (int8_T)rtb_SignDeltaU_o;
  } else {
    rtb_SignDeltaU_1 = MAX_int8_T;
  }

  /* End of DataTypeConversion: '<S3>/DataTypeConv1' */

  /* Signum: '<S3>/SignPreIntegrator' */
  if (rtb_IntegralGain_a < 0.0) {
    rtb_ZeroGain = -1.0;
  } else if (rtb_IntegralGain_a > 0.0) {
    rtb_ZeroGain = 1.0;
  } else {
    rtb_ZeroGain = rtb_IntegralGain_a;
  }

  /* Switch: '<S1>/Switch' incorporates:
   *  Constant: '<S1>/Constant'
   *  DataTypeConversion: '<S3>/DataTypeConv2'
   *  Logic: '<S3>/AND'
   *  RelationalOperator: '<S3>/Equal'
   *  Signum: '<S3>/SignPreIntegrator'
   */
  if (rtb_NotEqual && (rtb_SignDeltaU_1 == (int8_T)rtb_ZeroGain)) {
    rtb_IntegralGain_a = rtP.Constant_Value;
  }

  /* End of Switch: '<S1>/Switch' */

  /* Update for DiscreteIntegrator: '<S1>/Integrator' */
  rtDW.Integrator_DSTATE_l += rtP.Integrator_gainval_b * rtb_IntegralGain_a;

  /* Update for DiscreteIntegrator: '<S1>/Filter' */
  rtDW.Filter_DSTATE_m += rtP.Filter_gainval_i * rtb_FilterCoefficient_n;
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

  /* InitializeConditions for DiscreteIntegrator: '<S2>/Integrator' */
  rtDW.Integrator_DSTATE = rtP.Integrator_IC;

  /* InitializeConditions for DiscreteIntegrator: '<S2>/Filter' */
  rtDW.Filter_DSTATE = rtP.Filter_IC;

  /* InitializeConditions for DiscreteIntegrator: '<S1>/Integrator' */
  rtDW.Integrator_DSTATE_l = rtP.Integrator_IC_m;

  /* InitializeConditions for DiscreteIntegrator: '<S1>/Filter' */
  rtDW.Filter_DSTATE_m = rtP.Filter_IC_k;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
