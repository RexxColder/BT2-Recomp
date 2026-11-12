#include "common.h"

s64 EftVram_AddClut(void *arg0);
s64 EftVram_AddImage(void *arg0, s32 arg1, s32 arg2);
extern u8 *gEftRibbonMgr;

void func_001C6B28(void *arg0, u8 *arg1, u8 *arg2) {
    u8 *temp_s5;
    u8 *temp_s0;
    u8 *temp_a0;
    u8 *var_s1;
    s64 *var_s0;
    s64 img;
    s64 clut;
    s64 val;
    s32 var_s2;
    s32 temp_v0;
    s32 temp_v1;
    s32 q30;
    s32 q58;

    temp_s5 = gEftRibbonMgr + 8;
    q30 = *(s32 *)(arg2 + 0x30);
    if (!(*(s32 *)(*(u8 **)(arg2 + 0x34) + 0x104) & ((s32)1 << (q30 & 31)))) {
        var_s2 = 0;
        if (*(s32 *)(arg1 + 0xC0) > 0) {
            var_s0 = (s64 *)(arg1 + 0x148);
            var_s1 = arg1;
            do {
                temp_a0 = var_s1 + 0xD8;
                img = EftVram_AddImage(var_s1 + 0xC8, 1, 0);
                *var_s0 = img;
                clut = EftVram_AddClut(temp_a0);
                var_s1 += 0x20;
                val = *var_s0 | (clut << 37);
                *var_s0 = val;
                temp_v0 = *(s32 *)(arg2 + 0x30) + var_s2;
                var_s2 += 1;
                *(s64 *)(*(u8 **)(arg2 + 0x34) + (temp_v0 * 0x10)) = val;
                var_s0 += 1;
            } while (var_s2 < *(s32 *)(arg1 + 0xC0));
        }
        *(s32 *)(*(u8 **)(arg2 + 0x34) + 0x104) =
            *(s32 *)(*(u8 **)(arg2 + 0x34) + 0x104) | ((s32)1 << ((*(s32 *)(arg2 + 0x30)) & 31));
    } else {
        var_s2 = 0;
        if (*(s32 *)(arg1 + 0xC0) > 0) {
            do {
                s64 *dst;
                s64 *src;
                dst = (s64 *)(arg1 + 8 + (var_s2 * 8) + 0x140);
                src = (s64 *)(*(u8 **)(arg2 + 0x34) + ((*(s32 *)(arg2 + 0x30) + var_s2) * 0x10));
                var_s2 += 1;
                *dst = *src;
            } while (var_s2 < *(s32 *)(arg1 + 0xC0));
        }
    }

    temp_v1 = *(s32 *)(temp_s5 + 0x10C);
    q58 = *(s32 *)(arg1 + 0x58);
    if (!(temp_v1 & q58)) {
        temp_s0 = temp_s5 + 8;
        if (temp_v1 == 0) {
            *(s64 *)(temp_s5 + 0x118) = EftVram_AddImage(temp_s0, 1, 0);
        }
        clut = EftVram_AddClut(temp_s5 + (q58 * 16) + 8);
        *(s64 *)(temp_s0 + (*(s32 *)(arg1 + 0x58) * 16)) = *(s64 *)(temp_s5 + 0x118) | (clut << 37);
        *(s32 *)(temp_s5 + 0x10C) = *(s32 *)(temp_s5 + 0x10C) | ((s32)1 << (q58 & 31));
    }
}
