#include "common.h"

void *func_00269A40(s32 arg0, s32 arg1);
void *memset(void *, int, unsigned int);

/* 0x001F9E90: for each of 12 groups of 8 bits in the bitmap at arg0+4+0x8F0 (byte per group), for each set bit
 * k, obj = func_00269A40(*(arg0+0x1530), group*8+k); if obj is not NULL, copy floats +0x80..+0x9C to
 * +0xA0..+0xBC (0x9C to 0xBC, the rest in order). Then clears 12 bytes at arg0+0x8F4. */
void func_001F9E90(u8 *arg0) {
    s32 s1;
    s32 s0;
    u8 *flags;
    u8 *obj;

    for (s1 = 0; s1 < 0xC; s1++) {
        flags = arg0 + 4 + s1 + 0x8F0;
        if (*flags != 0) {
            s0 = 0;
            do {
                if ((((s32)*flags) >> s0) & 1) {
                    obj = (u8 *)func_00269A40(*(s32 *)(arg0 + 0x1530), (s1 * 8) + s0);
                    s0 += 1;
                    if (obj != NULL) {
                        *(f32 *)(obj + 0xA0) = *(f32 *)(obj + 0x80);
                        *(f32 *)(obj + 0xBC) = *(f32 *)(obj + 0x9C);
                        *(f32 *)(obj + 0xA4) = *(f32 *)(obj + 0x84);
                        *(f32 *)(obj + 0xA8) = *(f32 *)(obj + 0x88);
                        *(f32 *)(obj + 0xAC) = *(f32 *)(obj + 0x8C);
                        *(f32 *)(obj + 0xB0) = *(f32 *)(obj + 0x90);
                        *(f32 *)(obj + 0xB4) = *(f32 *)(obj + 0x94);
                        *(f32 *)(obj + 0xB8) = *(f32 *)(obj + 0x98);
                    }
                } else {
                    s0 += 1;
                }
            } while (s0 < 8);
        }
    }
    memset(arg0 + 0x8F4, 0, 0xC);
}
