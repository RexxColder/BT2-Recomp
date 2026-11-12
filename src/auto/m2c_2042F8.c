#include "m2c_macros.h"

void *BtlChar_GetPos();                       /* extern */
M2C_UNK func_001768A8();                         /* extern */
f32 func_0029DFD0();                             /* extern */
extern f32 D_00385908;

void func_002042F8(void *arg0) {
    f32 temp_f20;

    if ((M2C_FIELD(arg0, s64 *, 0x338) & 0x1000) && (D_00385908 < M2C_FIELD(BtlChar_GetPos(arg0), f32 *, 0xC0))) {
        temp_f20 = func_0029DFD0(BtlChar_GetPos(arg0) + 0x50);
        if ((temp_f20 / M2C_FIELD(BtlChar_GetPos(arg0), f32 *, 0xC0)) > 0.5f) {
            func_001768A8(M2C_FIELD(arg0, s32 *, 0x1534));
        }
    }
}
