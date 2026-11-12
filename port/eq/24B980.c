#include "common.h"

void FlushCache(s32 arg0);
void sceGsExecLoadImage(void *arg0, u8 *arg1);
void sceGsSetDefLoadImage(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 t0, s32 t1, s32 t2, s32 t3);
void sceGsSyncPath(s32 arg0, s32 arg1);

void func_0024B980(u8 *arg0, s32 arg1, s32 arg2) {
    s32 sp[24];
    s32 temp_a1;
    s32 temp_s2;
    s32 temp_s4;
    s32 temp_s5;
    s32 var_s1;
    s32 temp_a2;

    var_s1 = 0;
    temp_s2 = arg1 < 0;
    temp_s4 = (arg2 < 0x201) ? arg2 : 0x200;
    temp_s5 = arg1 + 0xF;
    while (var_s1 < (((temp_s2 != 0) ? (arg1 + 0xF) : arg1) >> 4)) {
        temp_a2 = (temp_s2 != 0) ? (arg1 + 0x3F) : arg1;
        sceGsSetDefLoadImage(sp, 0, (s32)((u32)temp_a2 << 10) >> 16, 0,
                             (s32)((u32)var_s1 << 20) >> 16, 0, 0x10, (s32)(s16)temp_s4);
        FlushCache(0);
        temp_a1 = var_s1 * arg2;
        var_s1 += 1;
        sceGsExecLoadImage(sp, arg0 + (temp_a1 << 6));
    }
    sceGsSyncPath(0, 0);
}
