#include "common.h"

s32 BtlChar_GetPos(s32 a0);
void func_00312638(s32 a0, s32 a1, s32 a2);

/* 0x0020E440: p = BtlChar_GetPos(a0) + 0xA0; func_00312638(p, p, a1). */
void func_0020E440(s32 a0, s32 a1) {
    s32 p = BtlChar_GetPos(a0) + 0xA0;
    func_00312638(p, p, a1);
}
