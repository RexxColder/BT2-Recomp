#include "common.h"

void Tex_Upload(void *arg0, s32 arg1, s32 arg2);
extern u8 *gEftSurf;

void func_00138548(s64 arg0, s64 arg1) {
    s64 var_s1;
    s64 var_s2;
    s64 var_s5;
    s64 var_s6;
    s64 var_s7;
    s64 temp_v0;
    s32 var_s4;
    s32 temp_a0;
    s32 temp_v1;
    u8 *var_s3;
    u8 *var_s0;

    var_s1 = 0x2A00;
    var_s2 = 0x2A80;
    var_s4 = 0;
    var_s3 = *(u8 **)(gEftSurf + 4);
    var_s0 = *(u8 **)(var_s3 + 0x14);
    if (*(s32 *)(var_s3 + 0x10) > 0) {
        var_s6 = arg0 << 34;
        var_s5 = arg1 << 35;
        var_s7 = (s64)0xFFF80003FFFFC000ULL;
        do {
            temp_v0 = (*(s64 *)(var_s0 + 0x30) & var_s7) | (var_s1 << 37) | (var_s6 | (s64)(u32)var_s2) | var_s5;
            *(s64 *)(var_s0 + 0x28) = temp_v0;
            var_s4 += 1;
            *(s64 *)(var_s0 + 0x30) = temp_v0;
            Tex_Upload(var_s0, var_s2, var_s1);
            temp_a0 = *(s32 *)(var_s0 + 0x10);
            temp_v1 = *(s32 *)(var_s0 + 0x14);
            var_s0 += 0x40;
            var_s2 = (s64)(s32)((s32)var_s2 + temp_a0);
            var_s1 = (s64)(s32)((s32)var_s1 + temp_v1);
        } while (var_s4 < *(s32 *)(var_s3 + 0x10));
    }
}
