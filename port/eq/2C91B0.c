#include "common.h"

s32 func_002CACB8(s32 arg0, s32, s32, s32);
void func_002CADB0(s32 arg0);

s32 func_002C91B0(u8 *arg0, u8 *arg1, u8 *arg2, u8 *arg3) {
    u8 *st;
    u8 *cur;
    s32 r;
    s32 x;
    s32 y;
    s32 w;
    s32 h;
    s32 a3v;
    s32 a2v;
    s32 p;
    s32 q;
    s32 pH;
    s32 qH;
    u8 *ptrA;
    u8 *ptrB;
    u32 t0v;
    u32 t1v;
    u32 sh;
    u32 base0;
    u32 base1;
    u32 qH9;
    s32 idx0;
    s32 idx1;

    st = *(u8 **)(arg0 + 0x1FC0);
    if (*(s32 *)(st + 0x168) != 0) {
        *(s32 *)arg3 = *(s32 *)(st + 0x168);
    } else {
        r = func_002CACB8((s32)arg0, arg1, arg2, arg3);
        *(s32 *)arg3 = r;
        if (r == 0) {
            *(s32 *)(arg0 + 0x950 + 0x2C) = 1;
            return -1;
        }
    }

    cur = *(u8 **)arg3;
    __builtin_memcpy(cur + 0x5C, arg1, 128);
    *(s64 *)(cur + 0xE0) = *(s64 *)(st + 0x1120);

    if (*(s32 *)(arg0 + 0x38) == 3) {
        if (((u32)(*(s32 *)(arg1 + 0x18) - 1)) < 2) {
            if (*(s32 *)(st + 0x168) == 0) {
                func_002CADB0(*(s32 *)(st + 0x160));
                *(s32 *)(st + 0x160) = *(s32 *)(st + 0x164);
                *(s32 *)(st + 0x164) = *(s32 *)arg3;
            }
        }

        x = *(s32 *)arg1;
        y = *(s32 *)(arg1 + 4);

        /* round up to 16 pixels, then to 16-pixel blocks (signed shifts) */
        w = x + 15;
        if (w < 0) {
            w = x + 30;
        }
        w >>= 4;

        h = y + 15;
        if (h < 0) {
            h = y + 30;
        }
        h >>= 4;

        a3v = (w << 4) + 63;
        if (a3v < 0) {
            a3v = (w << 4) + 126;
        }
        a2v = (w << 3) + 63;
        if (a2v < 0) {
            a2v = (w << 3) + 126;
        }
        p = a3v >> 6;
        q = a2v >> 6;

        pH = p * h;
        qH = q * h;
        p = p << 6;
        q = q << 6;

        ptrA = *(u8 **)(st + 0x160);
        ptrB = *(u8 **)(st + 0x164);
        t0v = *(u32 *)(ptrA + 8);
        t1v = *(u32 *)(ptrB + 8);

        sh = (u32)pH << 10;
        *(u16 *)(arg2 + 0x1E) = (u16)p;
        base1 = t1v + sh;
        base0 = t0v + sh;
        qH9 = (u32)qH << 9;
        *(u16 *)(arg2 + 0x1C) = (u16)q;

        *(u32 *)(arg2 + 0x14) = base1 + qH9;
        *(u32 *)(arg2 + 0x4) = base0 + qH9;
        *(u16 *)(arg2 + 0xE) = (u16)p;
        *(u16 *)(arg2 + 0xC) = (u16)q;
        *(u32 *)(arg2 + 0x8) = t0v;
        *(u32 *)(arg2 + 0x0) = base0;
        *(u32 *)(arg2 + 0x18) = t1v;
        *(u32 *)(arg2 + 0x10) = base1;
    } else {
        if (((u32)(*(s32 *)(arg1 + 0x18) - 1)) < 2) {
            *(u8 **)(st + 0x164) = cur;
            *(s32 *)(st + 0x138) = *(s32 *)(st + 0x138) ^ 1;
            *(s32 *)(st + 0x13C) = *(s32 *)(st + 0x13C) ^ 1;
        }
        idx0 = *(s32 *)(st + 0x138);
        idx1 = *(s32 *)(st + 0x13C);
        __builtin_memcpy(arg2, st + 0x140 + (idx0 << 4), 16);
        __builtin_memcpy(arg2 + 0x10, st + 0x140 + (idx1 << 4), 16);
    }

    cur = *(u8 **)arg3;
    *(s32 *)(arg2 + 0x2C) = 0;
    *(s32 *)(arg2 + 0x28) = 0;
    *(s32 *)(arg2 + 0x20) = *(s32 *)(cur + 8);
    *(u8 **)(arg2 + 0x24) = cur + 0x5C;
    *(s32 *)(arg0 + 0x950 + 0x2C) = 0;

    return 0;
}
