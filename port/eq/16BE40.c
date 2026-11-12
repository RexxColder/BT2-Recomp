#include "common.h"

s32 func_0020AB90(s32 arg0);
s32 func_0016D0E0(u8 *arg0);
void func_00126DE0(void *arg0);

/* 0x0016BE40(obj): s1 = obj->+0x38, s0 = s1->+0xB0; when func_0020AB90(*s0) and func_0016D0E0(s0) are both nonzero:
 * buf = { func_0016D0E0(s0), *s0, *(s0->+0x20) } (12 bytes) passed to func_00126DE0, then *s1 |= 0x80. */
void func_0016BE40(u8 *arg0) {
    u8 *s1 = *(u8 **)(arg0 + 0x38);
    u8 *s0 = *(u8 **)(s1 + 0xB0);
    s32 buf[3];

    if (func_0020AB90(*(s32 *)s0) == 0) {
        return;
    }
    if (func_0016D0E0(s0) == 0) {
        return;
    }
    buf[0] = func_0016D0E0(s0);
    buf[1] = *(s32 *)s0;
    buf[2] = *(s32 *)(*(u8 **)(s0 + 0x20));
    func_00126DE0(buf);
    *(s32 *)s1 |= 0x80;
}
