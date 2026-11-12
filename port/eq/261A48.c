#include "common.h"

extern s32 D_003B2654;
extern u8 *D_00387A40;
void func_002677E0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

void func_00261A48(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 idx = arg0 & 0xFFFF;

    if ((D_003B2654 & 0x100) == 0) {
        u8 *base = (u8 *)*(s32 *)(D_00387A40 + 0x8);

        func_002677E0((s32)(base + 0x1520 * idx), arg1, idx, arg3);
    }
}
