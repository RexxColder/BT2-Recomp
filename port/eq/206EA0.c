#include "common.h"

void func_0025E190(s32 arg0, s32 arg1);
void func_00262118(s32 arg0, s32 arg1);
extern s32 D_00387A40;

void func_00206EA0(s32 arg0) {
    s32 v1 = *(s32 *)(arg0 + 0x142C);

    if (v1 >= 0 && v1 < *(s32 *)(D_00387A40 + 0xC)) {
        func_0025E190(*(s32 *)(D_00387A40 + 0x8) + v1 * 0x1520, 0);
        func_00262118(0, *(u16 *)(arg0 + 0x1428));
        *(s32 *)(arg0 + 0x142C) = -1;
        *(u8 *)(arg0 + 0x1434) = 0;
        *(s32 *)(arg0 + 0x1428) = 0;
        *(s32 *)(arg0 + 0x1430) = 0;
    }
}
