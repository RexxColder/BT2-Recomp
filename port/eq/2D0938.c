#include "common.h"

s32 func_002C3210(s32 arg0, s32 arg1);
s32 func_002C2FF0(s32 arg0, s32 arg1);
void func_002CEDC0(s32 arg0, s64 arg1, s32 arg2, s32 arg3);

s32 func_002D0938(u8 *arg0, u8 *arg1) {
    u8 *src;
    u8 *dst;
    u8 *t1;
    u8 *a2p;
    s32 t2;
    s32 a3v;
    s64 a1v;
    s64 tmp;
    s64 cur;

    if (func_002C3210((s32)arg0, (s32)arg1) != 0) {
        return func_002C2FF0(0, 0xFF00011A);
    }
    src = arg0 + 0x36C0;
    dst = arg1;
    while (src != arg0 + 0x37A0) {
        *(s64 *)(dst + 0x00) = *(s64 *)(src + 0x00);
        *(s64 *)(dst + 0x08) = *(s64 *)(src + 0x08);
        *(s64 *)(dst + 0x10) = *(s64 *)(src + 0x10);
        *(s64 *)(dst + 0x18) = *(s64 *)(src + 0x18);
        src += 0x20;
        dst += 0x20;
    }
    t2 = 1;
    t1 = arg1 + 0x30;
    do {
        tmp = *(s64 *)(t1 - 0x10);
        a2p = arg1 + 8 + (t2 << 5);
        a3v = *(s32 *)(t1 + 8);
        t2 += 1;
        *(s64 *)arg1 = *(s64 *)arg1 + tmp;
        a1v = *(s64 *)a2p;
        cur = *(s64 *)(arg1 + 8);
        *(s32 *)(arg1 + 0x18) = *(s32 *)(arg1 + 0x18) + a3v;
        *(s64 *)(arg1 + 8) = (a1v < cur) ? a1v : cur;
        tmp = *(s64 *)t1;
        t1 += 0x20;
        cur = *(s64 *)(arg1 + 0x10);
        *(s64 *)(arg1 + 0x10) = (cur < tmp) ? tmp : cur;
    } while (t2 < 4);
    if (*(s32 *)(arg0 + 0x4C) == 4) {
        func_002CEDC0((s32)arg0, a1v, (s32)a2p, a3v);
    }
    return 0;
}
