#include "common.h"

s64 EftVram_AddClut(u8 *arg0);
s64 EftVram_AddImage(u8 *arg0, s32 arg1, s32 arg2);

void func_001EA518(u8 *arg0) {
    s32 temp_s3;
    s32 var_s4;
    s64 *var_s0;
    s64 temp_v1;
    s64 clut;
    u8 *var_s1;
    u8 *temp_a0;

    var_s4 = 0;
    if (*(s32 *)(*(u8 **)(arg0 + 0x128) + 0x100) > 0) {
        var_s0 = (s64 *)(arg0 + 0x170);
        var_s1 = arg0;
        do {
            temp_s3 = 1 << var_s4;
            if (*(s32 *)(*(u8 **)(arg0 + 0x128) + 0x104) & temp_s3) {
                *var_s0 = *(s64 *)(*(u8 **)(arg0 + 0x128) + var_s4 * 0x10);
            } else {
                *var_s0 = EftVram_AddImage(var_s1 + 0x130, 1, 0);
                clut = EftVram_AddClut(var_s1 + 0x140);
                temp_v1 = *var_s0 | (clut << 0x25);
                *var_s0 = temp_v1;
                *(s64 *)(*(u8 **)(arg0 + 0x128) + var_s4 * 0x10) = temp_v1;
                temp_a0 = *(u8 **)(arg0 + 0x128);
                *(s32 *)(temp_a0 + 0x104) = *(s32 *)(temp_a0 + 0x104) | temp_s3;
            }
            var_s4 += 1;
            var_s0 += 1;
            var_s1 += 0x20;
        } while (var_s4 < *(s32 *)(*(u8 **)(arg0 + 0x128) + 0x100));
    }
}
