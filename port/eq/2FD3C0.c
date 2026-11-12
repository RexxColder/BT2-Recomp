#include "common.h"

s32 func_00306F28(void);
void func_00306FA0();
s32 func_002FB818(s32 arg0);
void func_002FB5D8(s32 arg0);

void func_002FD3C0(u8 *arg0) {
    s32 v;

    if (*(s32 *)(arg0 + 0x1C) == 0) {
        return;
    }
    func_00306F28();
    v = func_002FB818(*(s32 *)(arg0 + 0x1C));
    if ((u32)v < 10) {
        switch (v) {
        case 0:
            *(u8 *)(arg0 + 2) = 0;
            func_002FB5D8(*(s32 *)(arg0 + 0x1C));
            *(s32 *)(arg0 + 0x1C) = 0;
            break;
        case 3: {
            s32 a0 = *(s32 *)(arg0 + 0x10);
            *(s32 *)(arg0 + 0x14) = a0;
            *(s32 *)(arg0 + 0xC) = *(s32 *)(arg0 + 0xC) + a0;
            *(u8 *)(arg0 + 2) = 1;
            func_002FB5D8(*(s32 *)(arg0 + 0x1C));
            *(s32 *)(arg0 + 0x1C) = 0;
            break;
        }
        case 9:
            *(u8 *)(arg0 + 2) = 3;
            func_002FB5D8(*(s32 *)(arg0 + 0x1C));
            *(s32 *)(arg0 + 0x1C) = 0;
            break;
        default:
            break;
        }
    }
    func_00306FA0();
}
