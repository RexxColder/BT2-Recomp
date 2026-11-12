#include "common.h"

s32 Rand_Range(s32 arg0, s32 arg1);
void func_002B5138(s32 arg0, s32 arg1);
void func_002B5180(s32 arg0, s32 arg1);
void func_002B51D0(s32 arg0, s32 arg1, s32 arg2);
void func_002B55D8(s32 arg0, s32 arg1);
s32 func_002B7CB8(s32 arg0);
s32 func_002B8280(s32 arg0);
s32 func_002CEE48(s32 arg0, s32 arg1, s32 arg2);
void memset(void *arg0, s32 arg1, u32 arg2);
extern u8 D_003783E0[] __attribute__((section(".data")));

s32 func_002B4EC8(s32 arg0, s32 arg1, s32 arg2) {
    s32 sp[4];
    s32 t;
    s32 v;
    s32 r;

    memset((void *)arg2, 0, 0x90);
    *(s32 *)(arg2 + 0) = 0;
    *(s32 *)(arg2 + 4) = -1;
    *(s32 *)arg1 = -1;
    t = func_002B8280(arg0);
    if (t != 1) {
        Rand_Range((s32)D_003783E0, 2);
        return 0;
    }
    func_002B5138(arg0, 2);
    v = func_002B7CB8(arg0);
    if (v == 0) {
        return 0;
    }
    r = func_002CEE48(v, arg1, (s32)sp);
    if (r != t) {
        return r;
    }
    *(s32 *)(arg0 + 0x78) = sp[0];
    func_002B55D8(arg0, sp[0]);
    func_002B51D0(arg0, sp[0], arg2);
    *(s32 *)(arg2 + 4) = *(s32 *)arg1;
    *(s32 *)(arg0 + 0xB8) = *(s32 *)(arg2 + 0x30);
    func_002B5180(arg0, arg2);
    return 1;
}
