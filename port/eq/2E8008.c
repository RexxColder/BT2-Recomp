#include "common.h"

extern s32 func_002F8E58();
extern s32 func_002F8EB8();

/* 0x002E8008: calls func_002F8E58 with fields of obj+0x48, then tail calls func_002F8EB8(obj->+8). */
s32 func_002E8008(u8 *obj, s32 idx) {
    u8 *p = obj + 0x48;
    u8 *h = *(u8 **)(obj + 8);
    s32 n = idx << 1;
    s32 a3 = *(s32 *)(p + 0x14) + (*(s32 *)(p + 0x20) << 1);
    s32 t0 = a3 + (*(s32 *)(p + 0x1C) << 1);

    func_002F8E58(h, *(s32 *)p, n, a3, t0);
    return func_002F8EB8(h);
}
