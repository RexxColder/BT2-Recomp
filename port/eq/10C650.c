#include "common.h"

void Dma_AddData(s32 arg0, s32 arg1, s64 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7,
                 s32 arg8, s32 arg9, s32 arg10, s32 arg11, s32 arg12, s32 arg13, s32 arg14, s32 arg15);

void func_0010C650(s64 arg0) {
    s32 sp[16];
    s64 temp_a2;
    s32 hi;

    temp_a2 = (s64)(s32)arg0;
    hi = (s32)(arg0 >> 32);
    sp[0] = 0x10000003;
    sp[1] = 0;
    sp[2] = 0x10000000;
    sp[3] = 0x50000003;
    sp[4] = 0x8002;
    sp[5] = 0x10000000;
    sp[6] = 0xE;
    sp[7] = 0;
    sp[8] = (s32)temp_a2;
    sp[9] = hi;
    sp[10] = 6;
    sp[11] = 0;
    sp[12] = 0x54;
    sp[13] = 0;
    sp[14] = 0x42;
    sp[15] = 0;
    Dma_AddData((s32)sp, 0x40, temp_a2, 0x8002, sp[4], sp[5], sp[6], sp[7], sp[8], sp[9], sp[10], sp[11],
                sp[12], sp[13], sp[14], sp[15]);
}
