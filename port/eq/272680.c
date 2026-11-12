#include "common.h"

s32 func_002745F8(s32 arg0);
u8 *StgOfsTable_Get(s32 arg0, s32 arg1, u8 *arg2);
s32 rand(void);
extern f32 D_00386FC0;
extern s32 D_00387AB4;
extern u8 *gBtlStage;

void func_00272680(void) {
    u8 *s1;
    u8 *s2;
    u8 *s3;
    u8 *s0p;
    s32 s0;
    s32 s4;
    s32 v1;
    s32 cur;

    if (D_00387AB4 == 0) {
        return;
    }
    s3 = *(u8 **)(gBtlStage + 4);
    s2 = s3 + (*(s32 *)(s3 + 0xC) << 2);
    if (*(u16 *)(s3 + 6) == 0) {
        return;
    }
    s4 = 0;
    do {
        s0 = *(s32 *)(s2 + 8);
        if (s0 > 0 && ((*(s32 *)(s2 + 4) & 0x40000000) != 0 || func_002745F8(s4) == 0)) {
            v1 = *(s32 *)(s2 + 0xC);
            s2 += 0x10;
            cur = (v1 < 0) ? v1 + 3 : v1;
            s1 = *(u8 **)(gBtlStage + 4) + ((cur >> 2) * 4);
            s0p = StgOfsTable_Get(D_00387AB4, s0 * 3 - 1, gBtlStage);
            *(f32 *)(s1 + 0x20) = ((f32)rand() / D_00386FC0) * (f32)*(u16 *)(s0p + 0xC);
        } else {
            s2 += 0x10;
        }
        s4 += 1;
    } while (s4 < *(u16 *)(s3 + 6));
}
