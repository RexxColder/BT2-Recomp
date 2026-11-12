#include "common.h"

#define BE16(p) ((u16)((((u8 *)(p))[0] << 8) | ((u8 *)(p))[1]))
#define BE32(p) ((((u8 *)(p))[0] << 24) | (((u8 *)(p))[1] << 16) | (((u8 *)(p))[2] << 8) | ((u8 *)(p))[3])

s32 func_002E9808(s32 arg0, s32 arg1, void *arg2, void *arg3);
void *memcpy(void *dst, const void *src, u32 n);

s32 func_002E9CE0(s32 arg0, s32 arg1, s32 *arg2, u64 *arg3, u16 *arg4, u16 *arg5) {
    u8 *buf;
    u8 tag[16];
    s32 r;
    s32 v13;
    s32 ofs;
    s32 t0v;
    s32 tt;
    s32 t2;
    s32 t3;
    s32 t4;
    s32 t5;
    u32 raw;

    buf = (u8 *)arg0;
    *arg2 = 0;
    r = func_002E9808(arg0, arg1, &tag[0], &tag[1]);
    if (r != 0) {
        return r;
    }

    v13 = (tag[0] == 4) ? 72 : 60;
    if (arg1 < v13) {
        return -1;
    }
    if (BE16(buf) != 0x8000) {
        return -2;
    }
    if ((s16)BE16(buf + 2) < v13 - 4) {
        return -1;
    }

    ofs = (tag[0] == 4) ? 32 : 20;
    t0v = ofs + 2;
    tt = t0v + 2;
    if (BE16(buf + t0v) != 0) {
        tt = tt + 20;
    }
    if (BE32(buf + tt) != 0x41494E46) {
        return -2;
    }

    t2 = tt + 4;
    raw = *(u32 *)(buf + t2);
    *arg2 = (s32)(((raw >> 24) & 0xFF) | ((raw >> 8) & 0xFF00) | ((raw << 8) & 0xFF0000) | (raw << 24));

    t3 = t2 + 4;
    t4 = t3 + 16;
    t5 = t4 + 4;
    memcpy(arg3, buf + t3, 16);
    *arg4 = BE16(buf + t4);
    *arg5 = BE16(buf + t5);
    arg5[1] = BE16(buf + t5 + 2);
    return 0;
}
