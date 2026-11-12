#include "common.h"

extern u8 D_00393E50[] __attribute__((section(".data")));

void *memcpy(void *arg0, const void *arg1, u32 arg2);
s32 func_002CE750(s32 arg0);
s32 func_002BEF18(s32 arg0);
s32 func_002BEF38(s32 arg0);
void func_002BEF70(u8 *arg0);
void func_002D8940(void);

s32 func_002BEE40(u8 *arg0) {
    u8 *p = *(u8 **)(arg0 + 0x2004);
    s32 s0;
    u8 *s2;
    u8 *vt;
    s32 r;

    s0 = *(s32 *)(p + 0);
    if (s0 == 0) {
        return 0;
    }
    s2 = *(u8 **)(p + 4);
    memcpy(D_00393E50, p + 8, 0x1C);
    r = func_002CE750(*(s32 *)(p + 0x20));
    if (r == 1) {
        func_002BEF70(arg0);
        s0 = func_002BEF38(s0);
    } else {
        s0 = func_002BEF18(s0);
    }
    vt = *(u8 **)s2;
    ((void (*)(u8 *))(*(void **)(vt + 0xC)))(s2);
    func_002D8940();
    return s0;
}
