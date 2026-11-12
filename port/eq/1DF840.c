#include "common.h"

void func_001E0C80(f32 farg0, u8 *arg0, u8 *arg1, s32 arg2, u8 *arg3, u8 *t0, u8 *t1, f32 farg1);
void *memset(void *arg0, s32 arg1, u32 arg2);

void func_001DF840(u8 *arg0, u8 *arg1, s32 arg2, f32 farg0, f32 farg1) {
    s32 sp[4];
    s32 var_s1;
    s32 var_s3;
    u8 temp_v0;

    var_s3 = 0;
    memset(sp, 0, 0x10);
    memset(arg0, 0, 0x21E0);
    *(f32 *)(arg0 + 0x21C4) = *(f32 *)(arg1 + 0x1A4);
    temp_v0 = *(u8 *)(arg1 + 0x1A0);
    *(s32 *)(arg0 + 0x21C8) = 0;
    *(u8 *)(arg0 + 0x21CC) = temp_v0;
    *(f32 *)(arg0 + 0x21D0) = 1.0f;
    *(u8 *)(arg0 + 0x21D9) = *(u8 *)(arg1 + 0x19C);
    *(s8 *)(arg0 + 0x21DA) = 1;
    *(s32 *)(arg0 + 0x21C0) = 0;
    if (temp_v0 & 0xFF) {
        var_s1 = 0;
        do {
            func_001E0C80(farg0, arg0 + var_s1, arg1 + var_s1, arg2, (u8 *)sp, (u8 *)sp, (u8 *)sp, farg1);
            var_s3 += 1;
            var_s1 += 0x1B0;
        } while (var_s3 < (s32)*(u8 *)(arg0 + 0x21CC));
    }
}
