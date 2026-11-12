#include "common.h"

void func_002C2658(s32 arg0);
void func_002C53D0(s32 arg0);
s32 func_002C53D8(s32 arg0, s32 arg1, s32 arg2);
u8 *func_002C5478(s32 arg0);

u8 *func_002C5328(u8 *arg0) {
    u8 *var_s0;
    u8 *var_s1;
    u8 *var_s2;
    u8 *var_s3;
    s32 var_v0;

    var_s1 = arg0;
    var_s0 = func_002C5478((s32)arg0);
    var_v0 = 0;
    if (var_s0 != NULL) {
        var_v0 = 0;
        if (*(s32 *)var_s0 != 0) {
            var_s2 = *(u8 **)(var_s1 + 0x1F7C);
            func_002C2658((s32)var_s1);
            func_002C53D0((s32)var_s1);
            var_s3 = var_s1 + 0xD30;
            var_v0 = func_002C53D8((s32)var_s1, (s32)var_s2, (s32)var_s0);
            if (var_v0 == 0) {
                *(s32 *)(var_s2 + 0x2C) = *(s32 *)(var_s0 + 0x28);
                *(s64 *)(var_s3 + 0x150) = *(s64 *)(var_s0 + 0x18);
                *(s32 *)(var_s2 + 0x30) = *(s32 *)(var_s0 + 0x2C);
                *(s64 *)(var_s2 + 0x10) = *(s64 *)(var_s0 + 0x20);
            }
        }
    }
    return (u8 *)var_v0;
}
