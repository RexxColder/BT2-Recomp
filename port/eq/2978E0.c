#include "common.h"

s32 func_002974F8(s32 arg0, s32 arg1);

extern u8 D_003B0E00[] __attribute__((section(".data")));

void Vu0Cur_Translate(s32 arg0) {
    *(s32 *)(D_003B0E00 + 0xC) = arg0;
    func_002974F8(0x200, (s32)D_003B0E00);
}
