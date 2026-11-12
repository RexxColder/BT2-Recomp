#include "common.h"

void func_0026C680(s32 arg0, s32 arg1, s32 *arg2);

void func_0026D640(u8 *arg0, u8 *arg1, s32 *arg2) {
    u8 *p;
    u16 idx;
    s32 v;
    u8 *base;

    v = *arg2;
    p = arg1 + v;
    idx = (u16)((u8)p[0] | ((u8)p[1] << 8));
    *arg2 = v + 2;
    base = *(u8 **)(arg0 + 0x14);
    func_0026C680((s32)(base + idx * 12 - 12), *(s32 *)(arg0 + 0x0), arg2);
}
