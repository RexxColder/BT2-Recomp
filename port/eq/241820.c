#include "m2c_macros.h"

s32 func_002411A0(s32 arg0, s32 arg1);

s32  func_00241820(void *arg0, s32 arg1) {
    u8 *a = (u8 *)arg0;
    s32 idx;
    u8 *base;
    u8 *temp_a1;
    u8 var_v0;

    idx = func_002411A0((s32)arg0, arg1) + 0x90;
    base = *(u8 **)(*(u8 **)(a + 0x1530) + 0x980);
    temp_a1 = base + idx;
    var_v0 = *(u8 *)(temp_a1 + 3);
    if (var_v0 == 0) {
        var_v0 = *(u8 *)temp_a1;
    }
    return (u8)(var_v0);
}
