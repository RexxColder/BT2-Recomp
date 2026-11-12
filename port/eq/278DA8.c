#include "common.h"

extern u8 *gOt;
extern u8 *gOtFirst;
extern s32 D_00387AE0;
extern s32 D_00387AE4;
void Ot_ResetEntries(s32 arg0, s32 arg1);
void func_00278D98(void);

/* 0x00278DA8 Ot_Reset (BT3 exact): gOt->0x2C = 0; idx = gOt->0x2C; p = gOt + idx * 4; gOtFirst = p[0];
 * D_00387AE0 = p[1]; D_00387AE4 = p[2]; Ot_ResetEntries(p[0], 0x2004); func_00278D98(); return 1. */
s32 Ot_Reset(void) {
    u8 *p;
    s32 idx;
    s32 first;

    *(s32 *)(gOt + 0x2C) = 0;
    idx = *(s32 *)(gOt + 0x2C);
    p = gOt + idx * 4;
    first = *(s32 *)p;
    gOtFirst = (u8 *)first;
    D_00387AE0 = *(s32 *)(p + 0x4);
    D_00387AE4 = *(s32 *)(p + 0x8);
    Ot_ResetEntries(first, 0x2004);
    func_00278D98();
    return 1;
}
