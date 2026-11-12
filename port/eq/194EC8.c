#include "common.h"

void Vec3_Add(s32 arg0, s32 arg1, s32 arg2);
void func_00129C38();
extern u8 func_00194948[] __attribute__((section(".data")));

s32 func_00194EC8(u8 *arg0, s32 arg1) {
    u8 *s0;
    u8 *s1;
    s32 fa;
    s32 r;

    r = 0;
    if (arg0 == NULL) {
        return r;
    }
    fa = *(s32 *)*(u8 **)(arg0 + 0x28);
    if (fa != (s32)0x00194948 /* PS2 class address (class 1: the table holds PS2 addresses) */) {
        return r;
    }
    s0 = *(u8 **)(arg0 + 0x38);
    if ((*(s32 *)(s0 + 0x60) & 1) == 0) {
        return r;
    }
    s1 = s0 + 0x20;
    func_00129C38((s32)s1, arg1, fa, (s32)arg0);
    s0 = *(u8 **)(s0 + 0x0);
    r = 1;
    if (s0 != NULL) {
        do {
            Vec3_Add((s32)(s0 + 0x90), (s32)(s0 + 0x80), (s32)s1);
            s0 = *(u8 **)(s0 + 0x140);
        } while (s0 != NULL);
    }
    return r;
}
