#include "common.h"

void func_002EA050(void *arg0);
s32 func_002F45C8(s32 arg0);
s32 func_002F4DA0(void *arg0);
s32 func_002F4E28(void *arg0);
extern u8 D_0037CB90[];

f32 func_002F5A80(void *arg0) {
    f32 var_f0;
    s32 temp_s0;
    s32 temp_s1;
    s32 temp_s2;
    u8 *obj;
    u8 *vt;
    s32 (*fn)(u8 *, s32);

    if (arg0 == NULL) {
        func_002EA050(D_0037CB90);
        return -1.0f;
    }
    var_f0 = 0.0f;
    if (func_002F45C8((s32)arg0) >= 2) {
        obj = *(u8 **)((u8 *)arg0 + 0x14);
        if (obj != NULL) {
            vt = *(u8 **)obj;
            fn = (s32 (*)(u8 *, s32))(u32) * (s32 *)(vt + 0x24);
            temp_s0 = fn(obj, 1);
            temp_s1 = func_002F4E28(arg0);
            temp_s2 = temp_s0 / (s32)(temp_s1 * 0x12);
            temp_s2 = temp_s2 << 5;
            var_f0 = (f32)temp_s2 / (f32)func_002F4DA0(arg0);
        }
    }
    return var_f0;
}
