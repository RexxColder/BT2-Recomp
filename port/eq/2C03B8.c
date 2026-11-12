#include "common.h"

s32 func_002C0448(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

void func_002C03B8(u8 *arg0) {
    s32 sp[6];
    u32 v1;
    u32 base;
    u32 size;
    u32 base2;
    u32 size2;
    u8 *s0;

    s0 = arg0 + 0x18;
    func_002C0448(*(s32 *)(arg0 + 4), 1, (s32)&sp[0], (s32)&sp[4]);
    v1 = *(u32 *)s0;
    base = (u32)sp[0];
    size = (u32)sp[1];
    base2 = (u32)sp[4];
    size2 = (u32)sp[5];
    if (!(v1 >= base && v1 < base + size) && !(v1 >= base2 && v1 < base2 + size2)) {
        *(s32 *)(s0 + 4) = 0;
        *(u32 *)s0 = 0U;
    }
}
