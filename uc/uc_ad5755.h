// UniControl MPU
//
// uc_ad5755.h -- Driver for MPU onboard DAC
//
// ----------------------------------------------------------------------------

#ifndef UC_AD5755_H
#define UC_AD5755_H

// -- Macros for TxWord[23..16]

#define AD5755_WRITE                  0b000000000000000000000000
#define AD5755_READ                   0b100000000000000000000000

#define AD5755_DUT_0                  0b000000000000000000000000
#define AD5755_DUT_1                  0b001000000000000000000000
#define AD5755_DUT_2                  0b010000000000000000000000
#define AD5755_DUT_3                  0b011000000000000000000000

#define AD5755_REG_DATA               0b000000000000000000000000
#define AD5755_REG_GAIN               0b000010000000000000000000
#define AD5755_REG_GAIN_ALL           0b000011000000000000000000
#define AD5755_REG_OFFS               0b000100000000000000000000
#define AD5755_REG_OFFS_ALL           0b000101000000000000000000
#define AD5755_REG_CLR                0b000110000000000000000000
#define AD5755_REG_CON                0b000111000000000000000000

#define AD5755_DAC_A                  0b000000000000000000000000
#define AD5755_DAC_B                  0b000000010000000000000000
#define AD5755_DAC_C                  0b000000100000000000000000
#define AD5755_DAC_D                  0b000000110000000000000000

// -- Macros for TxWord[15..0]

#define AD5755_CON_SLEW               0b000000000000000000000000
#define AD5755_CON_MAIN               0b000000000010000000000000
#define AD5755_CON_DAC                0b000000000100000000000000
#define AD5755_CON_DCDC               0b000000000110000000000000
#define AD5755_CON_SOFTWARE           0b000000001000000000000000

#define AD5755_CON_MAIN_POC           0b000000000001000000000000
#define AD5755_CON_MAIN_STATREAD      0b000000000000100000000000
#define AD5755_CON_MAIN_EWD           0b000000000000010000000000
#define AD5755_CON_MAIN_WD_5_MS       0b000000000000000000000000
#define AD5755_CON_MAIN_WD_10_MS      0b000000000000000100000000
#define AD5755_CON_MAIN_WD_100_MS     0b000000000000001000000000
#define AD5755_CON_MAIN_WD_200_MS     0b000000000000001100000000
#define AD5755_CON_MAIN_SHC_LIM_16MA  0b000000000000000000000000
#define AD5755_CON_MAIN_SHC_LIM_8MA   0b000000000000000001000000
#define AD5755_CON_MAIN_OUTEN_ALL     0b000000000000000000100000
#define AD5755_CON_MAIN_DCDC_ALL      0b000000000000000000010000

#define AD5755_CON_DAC_INT_ENABLE     0b000000000000000100000000
#define AD5755_CON_DAC_CLR_EN         0b000000000000000010000000
#define AD5755_CON_DAC_OUTEN          0b000000000000000001000000
#define AD5755_CON_DAC_RSET_INT       0b000000000000000000100000
#define AD5755_CON_DAC_RSET_EXT       0b000000000000000000000000
#define AD5755_CON_DAC_DCDC           0b000000000000000000010000
#define AD5755_CON_DAC_OVRNG          0b000000000000000000001000
#define AD5755_CON_DAC_RANGE_0V_5V    0b000000000000000000000000
#define AD5755_CON_DAC_RANGE_0V_10V   0b000000000000000000000001
#define AD5755_CON_DAC_RANGE_BIP_5V   0b000000000000000000000010
#define AD5755_CON_DAC_RANGE_BIP_10V  0b000000000000000000000011
#define AD5755_CON_DAC_RANGE_4MA_20MA 0b000000000000000000000100
#define AD5755_CON_DAC_RANGE_0MA_20MA 0b000000000000000000000101
#define AD5755_CON_DAC_RANGE_0MA_24MA 0b000000000000000000000110

#define AD5755_CON_DCDC_COMP          0b000000000000000001000000
#define AD5755_CON_DCDC_PHASE_ALL     0b000000000000000000000000
#define AD5755_CON_DCDC_PHASE_AB_CD   0b000000000000000000010000
#define AD5755_CON_DCDC_PHASE_AC_BD   0b000000000000000000100000
#define AD5755_CON_DCDC_PHASE_90_DEG  0b000000000000000000110000
#define AD5755_CON_DCDC_FREQ_250K     0b000000000000000000000000
#define AD5755_CON_DCDC_FREQ_410K     0b000000000000000000000100
#define AD5755_CON_DCDC_FREQ_650K     0b000000000000000000001000
#define AD5755_CON_DCDC_MAXV_23V      0b000000000000000000000000
#define AD5755_CON_DCDC_MAXV_24V5     0b000000000000000000000001
#define AD5755_CON_DCDC_MAXV_27V      0b000000000000000000000010
#define AD5755_CON_DCDC_MAXV_29V5     0b000000000000000000000011

#define AD5755_CON_SOFTWARE_RESET     0x555
#define AD5755_VALUE_MASK 			  0b000000001111111111111111

// -- Function prototypes

extern void AD5755_Put(uint32_t TxWord);
extern void AD5755_Cfg_Default(void);
extern void AD5755_Channel_Put(uint16_t ChA, uint16_t ChB, uint16_t ChC, uint16_t ChD);
extern void InitDAC(void);

extern uint32_t 		ui32SysClock;

#endif
