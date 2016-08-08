/*
 * position.h
 *
 * Code generation for function 'position'
 *
 */

#ifndef __POSITION_H__
#define __POSITION_H__

/* Include files */
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "tmwtypes.h"
#include "mex.h"
#include "emlrt.h"
#include "blas.h"
#include "rtwtypes.h"
#include "position_types.h"

/* Function Declarations */
extern real_T position(real_T location);

#ifdef __WATCOMC__

#pragma aux position value [8087];

#endif
#endif

/* End of code generation (position.h) */
