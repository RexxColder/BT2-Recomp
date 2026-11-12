#include "common.h"

extern u8 D_003B26B0[] __attribute__((section(".data")));

s32 func_002AD188(s32 arg0);
void func_002AD1F0(s32 arg0, s32 arg1, s32 arg2);
void func_002AA100(s32 arg0, s32 arg1, s32 arg2);

/* Clears n bytes; a loop kept out of the optimizer (optnone), because clang would turn it into a memset on a
 * 4-byte game pointer, which the PC build cannot lower. */
__attribute__((noinline, optnone)) static void ClearBytes(u8 *p, s32 n) {
    s32 k;

    for (k = 0; k < n; k++) {
        p[k] = 0;
    }
}

s32 func_002ACF90(s32 arg0, s32 arg1) {
    u8 *st;
    s32 v12;
    s32 v13;
    s32 v14;
    s32 v15;
    s32 mode;
    s32 bits_a;
    s32 bits_b;
    s32 i;
    s32 result;

    st = D_003B26B0;
    bits_a = 0;
    bits_b = 0;
    v12 = *(s32 *)(st + 0x30);
    v13 = *(s32 *)(st + 0x34);

    mode = func_002AD188(arg0);
    switch (mode) {
    case 1:
        for (i = 0; i < 32; i++) {
            func_002AD1F0(i, (s32)&v14, (s32)&v15);
            if (v14 != 0) {
                bits_a |= 1 << i;
            }
            if (v15 != 0) {
                bits_b |= 1 << i;
            }
        }
        /* fall through */
    case 0:
    case 2:
        func_002AA100((s32)&v12, (s32)&v13, arg0);
        break;
    default:
        break;
    }

    if (mode != 4) {
        *(s32 *)(st + 0x4) = 0;
        ClearBytes(st + 0x8, 12);
        ClearBytes(st + 0x38, 0x20);
        ClearBytes(st + 0x58, 0x258);
    }

    if (*(s32 *)(st + 0x30) != v12 || *(s32 *)(st + 0x34) != v13) {
        *(s32 *)(st + 0x24) = 0;
        *(s32 *)(st + 0x28) = 0;
        *(s32 *)(st + 0x2C) = 0;
        *(s32 *)(st + 0x14) = 0;
        *(s32 *)(st + 0x18) = 0;
        *(s32 *)(st + 0x1C) = 0;
        *(s32 *)(st + 0x20) = 0;
        ClearBytes(st + 0x2B0, 0x50);
    }

    if (arg1 >= 0) {
        *(s32 *)(st + 0x1C) |= 1 << arg1;
    }

    result = bits_a & ~(bits_b & *(s32 *)(st + 0x1C));

    *(s32 *)(st + 0x0) = mode;
    *(s32 *)(st + 0x18) = bits_b;
    *(s32 *)(st + 0x20) = bits_a;
    *(s32 *)(st + 0x14) = result;
    *(s32 *)(st + 0x30) = v12;
    *(s32 *)(st + 0x34) = v13;
    *(s32 *)(st + 0x30C) = 0;

    return result;
}
