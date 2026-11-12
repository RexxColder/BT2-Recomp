#include "common.h"

/* 0x002E7FB8: h = *(a0 + 8); func_002F8E28(h, *(a0+0x48), a1, *(a0+0x5C) + (*(a0+0x68) << 1), 0); tail func_002F8EB8(h). */
void func_002F8E28(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void func_002F8EB8(s32 arg0);

void func_002E7FB8(u8 *a0, s32 a1) {
    s32 h;

    h = *(s32 *)(a0 + 8);
    func_002F8E28(h, *(s32 *)(a0 + 0x48), a1,
                  *(s32 *)(a0 + 0x5C) + (*(s32 *)(a0 + 0x68) << 1), 0);
    func_002F8EB8(h);
}
