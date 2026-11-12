#include "common.h"

void func_002E25B0(s32 arg0);
void func_002E25B8(s32 arg0);
void func_002E2728(s32 arg0);

/* Reads n bits (MSB first) from the byte stream at bit position pos into dst. */
#define READ_BITS(dst, n) \
    do { \
        u32 acc_ = 0; \
        s32 j_; \
        for (j_ = 0; j_ < (n); j_++) { \
            acc_ = (acc_ << 1) | ((stream[pos >> 3] >> (7 - (pos & 7))) & 1); \
            pos++; \
        } \
        (dst) = acc_; \
    } while (0)

/* MPEG sequence header: parses the fields into the decoder state at +0x160 and returns the stream
   position after the header (rounded up to a byte). */
u8 *func_002E2730(u8 *dec, u8 *stream) {
    u8 *st;
    u32 *f;
    s32 pos;
    s32 mode;

    st = dec + 0x160;
    f = (u32 *)st;
    *(s32 *)(st + 0x420) = 1;
    *(s32 *)(st + 0x42C) = *(s32 *)(st + 0x42C) + 1;
    *(s32 *)(st + 0x4A4) = 0;
    *(s32 *)(st + 0x4A8) = 0;
    *(s32 *)(st + 0x4AC) = 0;
    mode = *(s32 *)(st + 0x308);
    if ((mode != 0 && mode != 0x40) || *(s32 *)(st + 0x30C) != 0) {
        *(s32 *)(st + 0x494) = *(s32 *)(st + 0x494) + 1;
    }
    func_002E25B0((s32)st);
    pos = 0;
    READ_BITS(f[0], 32);
    READ_BITS(f[1], 12);
    READ_BITS(f[2], 12);
    READ_BITS(f[3], 4);
    READ_BITS(f[4], 4);
    READ_BITS(f[5], 18);
    READ_BITS(f[6], 1);
    READ_BITS(f[7], 10);
    READ_BITS(f[8], 1);
    READ_BITS(f[9], 1);
    if (f[9] != 0) {
        pos += 64 * 8;
    }
    READ_BITS(f[10], 1);
    if (f[10] != 0) {
        pos += 64 * 8;
    }
    func_002E25B8((s32)st);
    func_002E2728((s32)st);
    if (*(s32 *)(st + 0x2C4) == 0) {
        *(s32 *)(st + 0x494) = *(s32 *)(st + 0x494) + 1;
    }
    if (*(s32 *)(st + 0x2C8) == 0) {
        *(s32 *)(st + 0x494) = *(s32 *)(st + 0x494) + 1;
    }
    if ((u32)(*(s32 *)(st + 0xC) - 1) >= 4) {
        *(s32 *)(st + 0x494) = *(s32 *)(st + 0x494) + 1;
    }
    if ((u32)(*(s32 *)(st + 0x10) - 1) >= 8) {
        *(s32 *)(st + 0x494) = *(s32 *)(st + 0x494) + 1;
    }
    *(s32 *)(st + 0x30C) = 1;
    *(s32 *)(st + 0x308) = 16;
    return stream + ((pos + 7) >> 3);
}
