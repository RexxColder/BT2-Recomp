#include "common.h"

s64 EftVram_AddClut(s32 a0);
s64 EftVram_AddImage(s32 a0, s32 a1, s32 a2);
s64 EftVram_AddTex(s32 a0, s32 a1, s32 a2);
void func_001DBAE0(s32 a0);
void *memset(void *arg0, s32 arg1, u32 arg2);
extern u8 *D_00387E9C;

s32 func_001DB940(s32 arg0, s32 arg1) {
    u8 sp[8];
    u8 *G;
    u8 *s0;
    u8 *s1;
    u8 *s3;
    s64 s6;
    s32 i;
    s64 v;
    u32 sum;

    G = D_00387E9C;
    sum = (u32)*(s32 *)(G + 0x1424) + (u32)*(s32 *)(G + 0x1440)
        + ((u32)*(s32 *)(G + 0x1430) + (u32)*(s32 *)(G + 0x1438))
        + ((u32)*(s32 *)(G + 0x1428) + (u32)*(s32 *)(G + 0x142C)
           + ((u32)*(s32 *)(G + 0x1434) + (u32)*(s32 *)(G + 0x143C)))
        + (u32)*(s32 *)(G + 0x1444);
    if (sum == 0) {
        *(u8 *)(G + 0x1490) = 0;
        return 1;
    }
    *(u8 *)(G + 0x1490) = 1;
    memset(sp, 0, 7);
    s1 = G + 0x14C0;
    s0 = s1;
    s6 = EftVram_AddImage((s32)(G + 0x14C0), arg0, arg1);
    func_001DBAE0((s32)sp);
    for (i = 0; i < 7; i++) {
        if (sp[i] != 0) {
            v = EftVram_AddClut((s32)s0);
            *(s64 *)s1 = s6 | (v << 37);
        }
        s1 += 0x10;
        s0 += 0x10;
    }
    s3 = G + 0x14B0;
    *(s64 *)s3 = EftVram_AddTex((s32)s3, arg0, arg1);
    *(s64 *)(s3 + 0x80) = EftVram_AddTex((s32)(s3 + 0x80), arg0, arg1);
    *(s64 *)(s3 + 0x90) = EftVram_AddTex((s32)(s3 + 0x90), arg0, arg1);
    *(s64 *)(s3 + 0xA0) = EftVram_AddTex((s32)(s3 + 0xA0), arg0, arg1);
    v = EftVram_AddTex((s32)(s3 + 0xB0), arg0, arg1);
    *(s64 *)(s3 + 0xB0) = v;
    return (s32)v;
}
