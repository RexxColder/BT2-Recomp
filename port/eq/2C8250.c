#include "common.h"

#define LD32(p, off) (*(s32 *)((u8 *)(p) + (off)))

void *memcpy(void *dst, const void *src, u32 n);
void func_002D1C18(void *arg0, void *arg1, void *arg2);

/* 0x002C8250: copies 32 bytes from +0xD4C into a frame buffer, runs func_002D1C18 on it (two words out at
 * buf+0x20 and buf+0x24), stores the buffer at +0xDF4 and sets the entry at +0xDF0 (flag 1, the difference
 * of buf+0x20 and +0xD90 and buf+0x24 at +0xE14/+0xE18). When the difference is not below +0xDBC the 0x2C-byte
 * entry at +0xDF0 is copied to +0xD98. */
void func_002C8250(s32 arg0) {
    u8 *p;
    u8 buf[0x28];
    s32 diff;

    p = (u8 *)(s32)arg0;
    memcpy(buf, p + 0xD4C, 0x20);
    func_002D1C18(buf, buf + 0x20, buf + 0x24);
    memcpy(p + 0xDF4, buf, 0x20);

    LD32(p, 0xDF0) = 1;
    diff = LD32(buf, 0x20) - LD32(p, 0xD90);
    LD32(p, 0xE14) = diff;
    LD32(p, 0xE18) = LD32(buf, 0x24);
    if (diff < LD32(p, 0xDBC)) {
        return;
    }
    memcpy(p + 0xD98, p + 0xDF0, 0x2C);
}
