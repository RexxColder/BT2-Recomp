#include "common.h"

extern u8 D_003B1C80[];
void func_003126C8(u8 *arg0, u8 *arg1);

void func_002A3B48(s32 arg0, u8 *arg1, u8 *arg2) {
    s32 off = arg0 << 4;

    func_003126C8(arg1, D_003B1C80 + off);
    func_003126C8(arg2, D_003B1C80 + 0x80 + off);
    *(s32 *)(arg1 + 0xC) = 0;
    *(s32 *)(arg2 + 0xC) = 0;
}
