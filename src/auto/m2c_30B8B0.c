#include "m2c_macros.h"

M2C_UNK func_002EFA40(M2C_UNK *);                   /* extern */
M2C_UNK func_002FC550(M2C_UNK);                     /* extern */
s32 func_002FC8C8(s32);                             /* extern */
M2C_UNK func_0030B718(void *);                      /* extern */
M2C_UNK func_0030BBB0();                            /* extern */
extern M2C_UNK D_003801A8 __attribute__((section(".data")));

void func_0030B8B0(void *arg0) {
    s32 temp_s0;

    if (arg0 != NULL) {
        if ((u8) M2C_FIELD(arg0, u8 *, 2) >= 2U) {
            func_0030BBB0(arg0);
        }
        if (M2C_FIELD(arg0, s8 *, 1) == 0) {
            func_002FC550(0x5000);
            temp_s0 = func_002FC8C8(M2C_FIELD(arg0, s32 *, 0x18));
            func_002FC550(0x5001);
            if (temp_s0 < 0) {
                func_002EFA40(&D_003801A8);
            }
        }
        M2C_FIELD(arg0, s8 *, 0) = 0;
        func_0030B718(arg0);
    }
}
