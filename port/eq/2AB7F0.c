#include "common.h"

void func_002AB440(s32 arg0);
void func_002AB6A8(s32 arg0, s32 arg1, s32 arg2);
extern u8 *D_00387F2C;

void func_002AB7F0(s32 *arg0) {
    s32 sel;

    if (*arg0 & 1) {
        sel = ((*(s32 *)(D_00387F2C + 0x1008) & 1) == 0) ? 0xABA3 : 0xAC2F;
        func_002AB6A8((s32)arg0, sel, 0xABA3);
        return;
    }
    func_002AB440((s32)arg0);
    *arg0 |= 1;
}
