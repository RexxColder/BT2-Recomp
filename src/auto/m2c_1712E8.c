#include "m2c_macros.h"

M2C_UNK func_0012D3A0(s32, s32, s32);               /* extern */
extern f32 D_003848BC;

void func_001712E8(void *arg0) {
    void *temp_s0;

    temp_s0 = M2C_FIELD(arg0, void **, 0xB0);
    func_0012D3A0(arg0 + 0x30, arg0 + 0x80, M2C_FIELD(temp_s0, s32 *, 0));
    if (*M2C_FIELD(temp_s0, s32 **, 0x20) == 0x174) {
        M2C_FIELD(arg0, f32 *, 0x34) = (f32) (M2C_FIELD(arg0, f32 *, 0x34) - D_003848BC);
    }
}
