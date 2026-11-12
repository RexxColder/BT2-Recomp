#include "common.h"

#define F32(p, off) (*(f32 *)((u8 *)(p) + (off)))

void *memset(void *s, s32 c, u32 n);
void *memcpy(void *d, const void *s, u32 n);

/* Copies a 0xA8-byte source record into a 0x128-byte frame, fills the float slots, and copies the
 * frame out to dst (the asm's aligned and unaligned paths are the same byte copies). Returns dst. */
u8 *func_0018C128(u8 *dst, u8 *p) {
    u8 sp[0x130];   /* tamano de locales del original (antes 0x128) */
    f32 f2;

    memset(sp, 0, 0x128);
    memcpy(sp, p, 0xA0);
    memcpy(sp + 0xA0, p + 0xA0, 8);
    f2 = F32(p, 0x94);
    F32(sp, 0xAC) = 2.0f;
    F32(sp, 0xB4) = f2;
    F32(sp, 0xC0) = 1.0f;
    F32(sp, 0xA8) = 1.0f;
    F32(sp, 0xB0) = f2;
    F32(sp, 0xB8) = 1.0f;
    F32(sp, 0xBC) = 1.0f;
    memcpy(dst, sp, 0x128);
    return dst;
}
