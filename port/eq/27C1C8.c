#include "common.h"

void *memset(void *, int, unsigned int);
void func_0027F030(s32 arg0, s32 arg1);

/* 0x0027C1C8: zeroes a 0x400-byte block, fills it with func_0027F030(arg1+0x4C0, block), then for i in 0..0xFF writes
 * a 4-byte entry at arg0 + 4*j, j = i with bits 3 and 4 swapped: bytes 0..2 = 0 and byte 3 = low byte of
 * (float block[i] * 128.0f) converted to an integer (values >= 2^31 keep the 0x80000000 bias). When byte arg1+0x591
 * is non-zero and i == 0xFF, the entry is all zero instead. */
void func_0027C1C8(u8 *arg0, u8 *arg1) {
    u8 buf[0x400];
    s32 i;

    memset(buf, 0, 0x400);
    func_0027F030((s32)(arg1 + 0x4C0), (s32)buf);
    for (i = 0; i < 0x100; i++) {
        s32 j = (i & 0xE7) | ((i & 8) << 1) | ((i & 0x10) >> 1);
        u8 *dst = arg0 + j * 4;
        f32 f;

        if (arg1[0x591] != 0 && i == 0xFF) {
            dst[0] = 0;
            dst[1] = 0;
            dst[2] = 0;
            dst[3] = 0;
            continue;
        }
        f = *(f32 *)(buf + i * 4) * 128.0f;
        dst[0] = 0;
        dst[1] = 0;
        dst[2] = 0;
        if (f >= 2147483648.0f) {
            dst[3] = (u8)(((u32)(s32)(f - 2147483648.0f)) | 0x80000000u);
        } else {
            dst[3] = (u8)(s32)f;
        }
    }
}
