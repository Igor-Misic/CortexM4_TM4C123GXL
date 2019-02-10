#ifndef ARM_MATH_H_
#define ARM_MATH_H_

#include <stdint.h>
typedef float float32_t;

/**
 * @brief Instance structure for the floating-point Biquad cascade filter.
 */
typedef struct
{
  uint32_t numStages;      /**< number of 2nd order stages in the filter.  Overall order is 2*numStages. */
  float32_t *pState;       /**< Points to the array of state coefficients.  The array is of length 4*numStages. */
  float32_t *pCoeffs;      /**< Points to the array of coefficients.  The array is of length 5*numStages. */
} arm_biquad_casd_df1_inst_f32;

void arm_biquad_cascade_df1_init_f32(
  arm_biquad_casd_df1_inst_f32 * S,
  uint8_t numStages,
  float32_t * pCoeffs,
  float32_t * pState);

void arm_biquad_cascade_df1_f32(
  const arm_biquad_casd_df1_inst_f32 * S,
  float32_t * pSrc,
  float32_t * pDst,
  uint32_t blockSize);


#endif //#define ARM_MATH_H_
