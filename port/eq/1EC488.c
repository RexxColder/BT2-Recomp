#include "common.h"

/* 0x001EC488: v = a1 & 0xFF; if (a0->+0x68 & 8) tail func_001EC818(a0, v) else tail func_001ECF40(a0, v). */
void func_001EC818(s32 arg0, s32 arg1);
void func_001ECF40(s32 arg0, s32 arg1);

void func_001EC488(void *a0, s32 a1) {
    s32 v;

    v = a1 & 0xFF;
    if (*(u32 *)((u8 *)a0 + 0x68) & 0x8) {
        func_001EC818((s32)a0, v);
        return;
    }
    func_001ECF40((s32)a0, v);
}
