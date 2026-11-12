#include "common.h"

void func_00129C28(u8 *arg0, u8 *arg1);
s32 func_0014EFA8(s32 arg0, u8 *arg1, u8 *arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6);
void func_001513D0(f32 farg0, s32 arg0, u8 *arg1, u8 *arg2, u8 *arg3, u8 *arg4, u8 *arg5, s32 arg6, s32 arg7, s32 stk0, s32 stk1);
void func_00208DE8(s32 arg0, void *arg1, s32 arg2);

void func_00171B38(s32 arg0, u8 *arg1, u8 *arg2) {
    u8 sp[0x40];
    u8 *s0;
    u8 *s1;
    u8 *s4;
    u8 *s5;
    u8 *s6;
    s32 s2;
    s32 s3;
    s32 s7;
    s32 fp;
    s32 flags;
    s32 t2;
    s32 res;
    f32 f0;
    f32 f12;

    s6 = arg2;
    fp = 0;
    s1 = *(u8 **)(arg1 + 0x38);
    *(s32 *)(sp + 0x20) = arg0;
    *(s32 *)(sp + 0x24) = *(s32 *)(s1 + 0xB0);
    func_00129C28(sp + 0x10, s1 + 0x80);
    flags = *(s32 *)s1;
    *(s32 *)(sp + 0x28) = 0;
    s3 = flags & 1;
    if (flags & 0x200) {
        if (flags & 0x800) {
            fp = 1;
            func_00208DE8(*(s32 *)(s1 + 0x8), sp + 0x10, 3);
            s3 = *(s32 *)s1 & 0x100;
            *(s32 *)(sp + 0x28) = s3;
        } else {
            *(s32 *)s1 = flags | 0x800;
        }
    }

    s7 = 0;
    *(s32 *)(sp + 0x2C) = 0;
    do {
        s4 = *(u8 **)s6 + *(s32 *)(sp + 0x2C);
        if (*s4 != 0) {
            s2 = 0;
            s5 = s1 + 0xB4;
            s0 = s4 + 0x10;
            do {
                flags = *(s32 *)s1;
                t2 = flags & 4;
                if (fp != 0) {
                    s3 = *(s32 *)(sp + 0x28);
                    if (s0[2] == 0) {
                        f0 = *(f32 *)(s0 + 0x8);
                        if (0.0f < f0) {
                            s3 = 0;
                            t2 = 0;
                        }
                    }
                }
                res = func_0014EFA8(arg0, s6, s5, s7, s2, s3, t2);
                f12 = *(f32 *)(s1 + 0x1C);
                if (fp != 0 && s0[0] == 2) {
                    f12 = *(f32 *)(s1 + 0x20);
                }
                if (res != 0) {
                    func_001513D0(f12, *(s32 *)(sp + 0x24), s6, s5, s1 + 0x860, sp + 0x10, s1 + 0x30, s7, s2, s2, res);
                }
                s2 += 1;
                s0 += 0x20;
            } while (s2 < *s4);
        }
        s7 += 1;
        *(s32 *)(sp + 0x2C) += 0x110;
    } while (s7 < 0x10);
}
