#include "common.h"

void func_00183B78(s32 arg0, s32 arg1, s32 arg2);
void func_00183E70(s32 arg0);
void func_00210000(s32 arg0, s32 arg1);
s32 func_002615B0(s32 arg0);

void func_00183BE0(u8 *arg0) {
    s16 sel;

    if (func_002615B0(*(u16 *)(arg0 + 0xB08)) == 0) {
        sel = *(s16 *)(arg0 + 0xAD4);
        if (sel == 0) {
            func_00183B78((s32)arg0, 1, 2);
            *(u16 *)(arg0 + 0xAD6) = (u16)(*(u16 *)(arg0 + 0xAD6) | 4);
        } else if (sel == 2) {
            func_00183B78((s32)arg0, 3, 1);
            func_00183E70((s32)arg0);
            *(u16 *)(arg0 + 0xAD6) = (u16)(*(u16 *)(arg0 + 0xAD6) | 0x100);
            func_00210000((s32)(arg0 + 0xA70), 0x1C);
        } else if (sel == 3) {
            func_00183B78((s32)arg0, 4, 2);
        }
    }
}
