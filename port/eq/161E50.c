#include "common.h"

u8 *func_001F3758(u8 *arg0);
s32 func_0020AB90(s32 arg0);
void func_00126DE0(void *arg0);

/* 0x00161E50(obj): v = func_001F3758(obj); s1 = obj->+0x38, s2 = v->+0x38, s0 = s1->+0x70; when func_0020AB90(*s0)
 * is nonzero and bit 5 of the word at s1 is clear: buf = { s2->+0x1E84, *s0, *(s0->+0x20) } is passed to
 * func_00126DE0 and bit 5 is set in the word at s1. */
void func_00161E50(u8 *arg0) {
    u8 *v;
    u8 *s1;
    u8 *s2;
    u8 *s0;
    s32 buf[3];

    v = func_001F3758(arg0);
    s1 = *(u8 **)(arg0 + 0x38);
    s2 = *(u8 **)(v + 0x38);
    s0 = *(u8 **)(s1 + 0x70);
    if (func_0020AB90(*(s32 *)s0) == 0) {
        return;
    }
    if ((*(s32 *)s1 & 0x20) != 0) {
        return;
    }
    buf[0] = *(s32 *)(s2 + 0x1E84);
    buf[1] = *(s32 *)s0;
    buf[2] = *(s32 *)(*(u8 **)(s0 + 0x20));
    func_00126DE0(buf);
    *(s32 *)s1 |= 0x20;
}
