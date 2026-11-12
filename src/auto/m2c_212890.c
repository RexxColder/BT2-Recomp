#include "m2c_macros.h"

extern void *D_003876A0;
extern void *D_00387930;

void func_00212890(s32 arg0) {
    if ((M2C_FIELD(D_003876A0, s32 *, 0xD4) == 4) && (D_00387930 != NULL)) {
        M2C_FIELD(D_00387930, s32 *, 0x24) = (s32) (M2C_FIELD(D_00387930, s32 *, 0x24) + arg0);
        if (M2C_FIELD(D_00387930, s32 *, 0x24) >= 0x97) {
            M2C_FIELD(D_00387930, s32 *, 0x24) = 0x96;
        }
    }
}
