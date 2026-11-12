#include "common.h"

u8 *func_002CA9A0(u8 *arg0);
s32 func_002DE618(s32 arg0, u8 *arg1, u8 *arg2);
void func_002C2FF0(u8 *arg0, s32 arg1);
extern void *memcpy(void *dst, const void *src, u32 n);

/* 0x002CA8A8: *arg2 = 0; p = func_002CA9A0(obj); p and *p must be nonzero. Copy p+0xC (0x20 bytes) to obj+0xD6C, p+0x2C
 * (12 bytes) to obj+0xD8C. frame = {p+0x38, word p+0x238}; func_002DE618(*arg1, frame, frame+0x10) == 0 -> *arg2 = 1,
 * else func_002C2FF0(obj, 0xFF000F1B). */
void func_002CA8A8(u8 *arg0, s32 *arg1, s32 *arg2) {
    u8 *p;
    u8 frame[0x18];
    s32 r;

    *arg2 = 0;
    p = func_002CA9A0(arg0);
    if (p == 0) {
        return;
    }
    if (*(s32 *)p == 0) {
        return;
    }
    memcpy(arg0 + 0xD6C, p + 0xC, 0x20);
    memcpy(arg0 + 0xD8C, p + 0x2C, 0xC);
    *(s32 *)frame = (s32)(p + 0x38);
    *(s32 *)(frame + 4) = *(s32 *)(p + 0x238);
    r = func_002DE618(*arg1, frame, frame + 0x10);
    if (r == 0) {
        *arg2 = 1;
        return;
    }
    func_002C2FF0(arg0, 0xFF000F1B);
}
