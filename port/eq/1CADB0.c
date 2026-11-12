#include "common.h"

s64 EftVram_AddImage(u8 *arg0, s32 arg1, s32 arg2);
s64 EftVram_AddClut(u8 *arg0, s32 arg1, s32 arg2);
s64 EftVram_AddTex(u8 *arg0, s32 arg1, s32 arg2);
extern u8 *gEftMod1CBMgr;

void func_001CADB0(u8 *arg0, u8 *arg1) {
    u8 *p34;
    u8 *mgr;
    u8 *s0;
    u8 *s1;
    u8 *s2;
    s32 a0;
    s32 a1;
    s32 cnt;
    s64 v;

    p34 = *(u8 **)(arg1 + 0x34);
    if (p34 != 0) {
        a0 = *(s32 *)(arg1 + 0x30);
        if ((*(s32 *)(p34 + 0x104) & (1 << (a0 & 31))) == 0) {
            v = EftVram_AddTex(p34 + a0 * 0x10, 1, 0);
            *(s64 *)(*(u8 **)(arg1 + 0x34) + *(s32 *)(arg1 + 0x30) * 0x10) = v;
            v = EftVram_AddTex(*(u8 **)(arg1 + 0x34) + *(s32 *)(arg1 + 0x30) * 0x10 + 0x10, 1, 0);
            *(s64 *)(*(u8 **)(arg1 + 0x34) + *(s32 *)(arg1 + 0x30) * 0x10 + 0x10) = v;
            *(s32 *)(*(u8 **)(arg1 + 0x34) + 0x104) = (s32)(1 << (*(s32 *)(arg1 + 0x30) & 31));
        }
        return;
    }

    mgr = gEftMod1CBMgr;
    s1 = mgr + 0x38;
    s2 = mgr + 0x10;
    a1 = *(s32 *)(s1 + 0x104);
    if (a1 == 0) {
        *(s64 *)(s2 + 0x10) = EftVram_AddImage(s1, 1, 0);
        v = ((s64 (*)(u8 *))EftVram_AddClut)(s1 + *(s32 *)(arg1 + 4) * 0x10);
        *(s64 *)(s1 + *(s32 *)(arg1 + 4) * 0x10) = *(s64 *)(s2 + 0x10) | (v << 37);
        *(s32 *)(s1 + 0x104) = *(s32 *)(s1 + 0x104) | (1 << (*(s32 *)(arg1 + 4) & 31));
    } else {
        a0 = *(s32 *)(arg1 + 4);
        if ((a1 & (1 << (a0 & 31))) == 0) {
            v = EftVram_AddClut(s1 + a0 * 0x10, a1, 0);
            *(s64 *)(s1 + *(s32 *)(arg1 + 4) * 0x10) = *(s64 *)(s2 + 0x10) | (v << 37);
            *(s32 *)(s1 + 0x104) = *(s32 *)(s1 + 0x104) | (1 << (*(s32 *)(arg1 + 4) & 31));
        }
    }

    s1 = mgr + 0x168;
    if (*(s32 *)(s1 + 0x104) == 0) {
        if (*(s32 *)(s1 + 0x100) > 0) {
            cnt = 0;
            s0 = s1;
            do {
                cnt += 1;
                *(s64 *)s0 = EftVram_AddTex(s0, 1, 0);
                s0 += 0x10;
            } while (cnt < *(s32 *)(s1 + 0x100));
        }
        *(s32 *)(s1 + 0x104) = 1;
    }
}
