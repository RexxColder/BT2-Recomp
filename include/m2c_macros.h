#ifndef M2C_MACROS_H
#define M2C_MACROS_H

/* What m2c --valid-syntax output needs to compile (scripts/m2c_sweep.py); no game headers, so its own
   prototypes are the only ones. */
#include "common.h"

typedef s32 M2C_UNK;
typedef s8 M2C_UNK8;
typedef s16 M2C_UNK16;
typedef s32 M2C_UNK32;
typedef s64 M2C_UNK64;

#define M2C_FIELD(expr, type, offset) (*(type)((u8 *)(expr) + (offset)))
#define M2C_BITWISE(type, expr) ({ union { __typeof__(expr) a; type b; } m2c_u_; m2c_u_.a = (expr); m2c_u_.b; })

#endif
