#include "m2c_macros.h"

M2C_UNK func_0026EA88(void *);                      /* extern */
M2C_UNK func_0026EAE0(void *, s32);                 /* extern */
extern void *D_003879B0;

void func_00251030(s32 arg0) {
    if (!(M2C_FIELD(D_003879B0, s32 *, 0x6C) & 4)) {
        M2C_FIELD(D_003879B0, s32 *, 0x6C) = 4;
        func_0026EAE0(D_003879B0 + 0x1C, arg0);
        func_0026EA88(D_003879B0 + 0x1C);
    }
}
