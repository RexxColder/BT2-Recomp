#include "common.h"

s32 func_00217488(u8 *arg0);
void BattleSide_SetChara(u8 *arg0, s32 arg1);
void func_00217CB8(u8 *arg0);
void func_0020FC38(u8 *arg0, s32 arg1);

/* 0x00219128: v = func_00217488(obj) - 0x4A; 0..5 bump a counter (+0x1504, +0x1508, +0x14FC, +0x1500, +0x150C twice) and
 * pick the code a1 (0x62, 0x65, 0x5C, 0x5F, 0x56, 0x59), else a1 = 0. Then BattleSide_SetChara(obj, a1), func_00217CB8(obj),
 * func_0020FC38(obj, 0x2E), obj+0x149C++. */
void func_00219128(u8 *arg0) {
    s32 v;
    s32 a1;

    v = func_00217488(arg0) - 0x4A;
    a1 = 0;
    if ((u32)v < 6) {
        switch (v) {
        case 0:
            *(s32 *)(arg0 + 0x1504) = *(s32 *)(arg0 + 0x1504) + 1;
            a1 = 0x62;
            break;
        case 1:
            *(s32 *)(arg0 + 0x1508) = *(s32 *)(arg0 + 0x1508) + 1;
            a1 = 0x65;
            break;
        case 2:
            *(s32 *)(arg0 + 0x14FC) = *(s32 *)(arg0 + 0x14FC) + 1;
            a1 = 0x5C;
            break;
        case 3:
            *(s32 *)(arg0 + 0x1500) = *(s32 *)(arg0 + 0x1500) + 1;
            a1 = 0x5F;
            break;
        case 4:
            a1 = 0x56;
            *(s32 *)(arg0 + 0x150C) = *(s32 *)(arg0 + 0x150C) + 1;
            break;
        case 5:
            a1 = 0x59;
            *(s32 *)(arg0 + 0x150C) = *(s32 *)(arg0 + 0x150C) + 1;
            break;
        }
    }
    BattleSide_SetChara(arg0, a1);
    func_00217CB8(arg0);
    func_0020FC38(arg0, 0x2E);
    *(s32 *)(arg0 + 0x149C) = *(s32 *)(arg0 + 0x149C) + 1;
}
