#include "common.h"

void *memset(void *arg0, s32 arg1, u32 arg2);
void func_001E0C80(void *arg0, void *arg1, s32 arg2, s32 *arg3, s32 *arg4, s32 *arg5, f32 farg6, f32 farg7);

void func_001DFA50(void *arg0, void *arg1, s32 arg2, f32 farg3) {
    s32 sp[4];
    u8 *a0;
    u8 *a1;
    s32 var_s1;
    s32 var_s3;

    a0 = (u8 *)arg0;
    a1 = (u8 *)arg1;
    var_s3 = 0;
    memset(arg0, 0, 0x21E0);
    *(f32 *)(a0 + 0x21C4) = *(f32 *)(a1 + 0x1A4);
    *(s32 *)(a0 + 0x21C8) = 0;
    *(u8 *)(a0 + 0x21CC) = *(u8 *)(a1 + 0x1A0);
    *(u8 *)(a0 + 0x21D9) = *(u8 *)(a1 + 0x19C);
    *(f32 *)(a0 + 0x21D0) = 1.0f;
    *(s8 *)(a0 + 0x21DA) = 1;
    *(s32 *)(a0 + 0x21C0) = 0;
    sp[0] = 0;
    sp[1] = 0;
    sp[2] = 0;
    sp[3] = 0;
    if (*(u8 *)(a0 + 0x21CC) != 0) {
        var_s1 = 0;
        do {
            func_001E0C80(a0 + var_s1, a1 + var_s1, arg2, sp, sp, sp, farg3, 0.0f);
            var_s1 += 0x1B0;
            var_s3 += 1;
        } while (var_s3 < *(u8 *)(a0 + 0x21CC));
    }
}
