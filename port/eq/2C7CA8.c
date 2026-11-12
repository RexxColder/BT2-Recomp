#include "common.h"

void func_002D1C18(void *a0, void *a1, void *a2);
s32 func_002D07B0(void *a0, s32 a1);
void *memcpy(void *arg0, const void *arg1, u32 arg2);

s32 func_002C7CA8(void *arg0) {
    u8 *s0;
    u8 buf[0x40];
    s32 t;
    s32 a2v;
    s32 a1v;
    s32 v1;

    s0 = (u8 *)arg0;
    if (*(s32 *)(s0 + 0xD98) == 0) {
        return 0;
    }
    memcpy(buf, s0 + 0xD4C, 0x20);
    func_002D1C18(buf, buf + 0x20, buf + 0x24);
    func_002D1C18(s0 + 0xD9C, buf + 0x28, buf + 0x24);
    t = func_002D07B0(s0, 0x35);
    a2v = *(s32 *)(buf + 0x20);
    a1v = *(s32 *)(buf + 0x28);
    v1 = *(s32 *)(buf + 0x24);
    if (!(a1v < a2v)) {
        return 1;
    }
    return (a1v + v1 * t) <= a2v;
}
