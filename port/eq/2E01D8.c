#include "common.h"

extern s32 D_00347624 __attribute__((section(".data")));
extern s32 D_00399DF8 __attribute__((section(".data")));

void func_002E01D8(u8 *arg0) {
    *(s32 *)(arg0 + 0x30) = D_00399DF8 + 0x1100;
    *(s32 *)(arg0 + 0x110) = D_00347624;
    *(s32 *)(arg0 + 0x40) = D_00347624;
}
