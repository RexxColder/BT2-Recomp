#include "common.h"

s32 func_003126C8(u8 *a0, u8 *a1);
void func_00312650(f32 *a0, u8 *a1, u8 *a2);
void func_00312680(f32 *a0, f32 *a1, f32 farg0);
void func_00312638(u8 *a0, f32 *a1, u8 *a2);
f32 func_0029DFD0(f32 *a0);
f32 sceVu0InnerProduct(f32 *a0, f32 *a1);

/* 0x00121740: searches the record list at arg0+0xBE0 (16-byte entries) for the entry matching the
 * vector pair; writes the result float to arg3, a flag byte to arg4 and an index byte to arg5 and
 * returns the (possibly decremented) index s1. */
s32 func_00121740(u8 *arg0, u8 *arg1, u8 *arg2, f32 *arg3, u8 *arg4, u8 *arg5) {
    f32 va[4];
    f32 vb[4];
    u8 *s2;
    u8 *base;
    s32 s1;
    s32 s3;
    s32 flag;
    s32 val28;
    f32 f20;
    f32 f21;
    f32 f22;

    s2 = arg0 + 0xBE0;
    flag = 0;
    val28 = 0;
    s1 = *(s32 *)(arg0 + 0xFF4);
    if (s1 == 0) {
        func_003126C8(arg2, arg0 + 0xC00);
        f20 = 0.0f;
        goto out;
    }

    f22 = 0.0f;
    f21 = 1.0f;
    for (;;) {
        s3 = s1 << 4;
        base = s2 + s3;
        func_00312650(va, base + 0x10, base + 0x20);
        func_00312650(vb, arg1, base + 0x20);
        *(s32 *)&va[1] = 0;
        *(s32 *)&vb[1] = 0;
        f20 = func_0029DFD0(va);
        f20 = f20 * f20;
        f20 = sceVu0InnerProduct(va, vb) / f20;

        if (f20 < f22) {
            f20 = 0.0f;
            if (!(s1 < *(s32 *)(s2 + 4) - 1)) {
                flag = 1;
            }
            break;
        }
        if (f21 < f20) {
            if (s1 < 2) {
                s1 = 1;
                f20 = 1.0f;
                val28 = s1;
                s3 = 0x10;
                break;
            }
            s1 = s1 - 1;
            continue;
        }
        break;
    }

    base = s2 + s3;
    func_00312650(va, base + 0x10, base + 0x20);
    func_00312680(va, va, f20);
    func_00312638(arg2, va, base + 0x20);

out:
    if (arg3 != NULL) {
        *arg3 = f20;
    }
    if (arg4 != NULL) {
        *arg4 = (u8)flag;
    }
    if (arg5 != NULL) {
        *arg5 = (u8)val28;
    }
    return s1;
}
