#include "common.h"

extern s32 D_00388D48[];
extern u8 D_00388A48[];
void *memset(void *s, s32 c, u32 n);
s32 func_0028BAA8(s32 arg0);

s32 func_00261D30(s32 arg0) {
    s32 *g;
    u8 *a;
    u8 *b;
    u8 *bk;
    s32 n;
    s32 i;
    s32 k;
    s32 result;

    switch (arg0) {
        case 0:
            n = 2;
            break;
        case 1:
        case 2:
        case 3:
            n = 0;
            break;
        case 4:
            n = 1;
            break;
        default:
            n = 0;
            break;
    }

    g = D_00388D48;
    result = (s32)memset(D_00388A48, 0, 0x320);
    g[3] = n;
    if (n == 0) {
        return result;
    }

    g[0] = func_0028BAA8(n * 16 + 16);
    g[1] = func_0028BAA8(n * 48);
    memset((void *)g[0], 0, n * 16 + 16);
    memset((void *)g[1], 0, n * 48);

    a = (u8 *)g[0];
    b = (u8 *)g[1];

    i = 0;
    do {
        *(s32 *)(a + 16 * i) = func_0028BAA8(0xE9800);
        *(s32 *)(a + 16 * i + 12) = *(s32 *)(a + 16 * i);
        memset((void *)*(s32 *)(a + 16 * i), 0, 0xE9800);
        i++;
    } while (i < n + 1);

    for (k = 0; k < n; k++) {
        bk = b + 48 * k;
        *(s32 *)(bk + 0x28) = func_0028BAA8(0x120000);
        *(s32 *)(bk + 0x2C) = func_0028BAA8(0x7B000);
        memset((void *)*(s32 *)(bk + 0x28), 0, 0x120000);
        memset((void *)*(s32 *)(bk + 0x2C), 0, 0x7B000);
        *(s32 *)(bk + 0x24) = *(s32 *)(a + 16 * k);
    }

    g[2] = (s32)(a + 16 * n);
    return g[2];
}
