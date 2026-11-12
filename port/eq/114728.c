#include "common.h"

void func_00113510(void *arg0);
extern s32 D_003B0A84 __attribute__((section(".data")));

#define ST(k, off, v) (*(s64 *)((u8 *)arg0 + 0x10 * (k) + (off)) = (s64)(v))

void *func_00114728(void *arg0) {
    s16 h[4];
    s64 v0, v1;

    func_00113510(h);
    ST(0, 0, 0x1000000000000005LL);
    ST(0, 8, 0xE);
    ST(1, 0, 0x3F80000080808080LL);
    ST(1, 8, 1);
    ST(2, 0, 0x44);
    ST(2, 8, 0x42);
    ST(3, 0, (D_003B0A84 & 1) ? 0xA64020000LL : 0xA64020E00LL);
    ST(3, 8, 6);
    ST(4, 0, 0);
    ST(4, 8, 0x3F);
    ST(5, 0, 0x116);
    ST(5, 8, 0);
    ST(6, 0, 0x4400000000008001LL);
    ST(6, 8, 0x5353);
    v0 = ((s64)(s32)(h[0] * 16 + 8)) | (((s64)(s32)(h[1] * 16 + 8)) << 16);
    ST(7, 0, v0);
    ST(7, 8, 0x7C007C00);
    v1 = ((s64)(s32)(h[2] * 16 + 8)) | (((s64)(s32)(h[3] * 16 + 8)) << 16);
    ST(8, 0, v1);
    ST(8, 8, 0x84008400LL);
    return (u8 *)arg0 + 0x90;
}
