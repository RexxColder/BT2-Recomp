#include "m2c_macros.h"

M2C_UNK sceVu0CopyMatrix(void *, s32);              /* extern */
extern void *D_00387A30;

void func_0025AA98(s32 arg0) {
    if (M2C_FIELD(D_00387A30, s32 *, 0x2B0) != 0) {
        sceVu0CopyMatrix(D_00387A30 + 0x250, arg0);
    }
}
