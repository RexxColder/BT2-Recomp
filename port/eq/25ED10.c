#include "common.h"

#define U16AT(p, off) (*(u16 *)((u8 *)(p) + (off)))
#define U32AT(p, off) (*(u32 *)((u8 *)(p) + (off)))
#define PAIR(p, off) ((s64)U32AT(p, off) + ((s64)U32AT(p, (off) + 4) << 32))

void Quat_Unpack(void *arg0, s64 arg1, void *arg2);
void Quat_Slerp(f32 farg0, void *arg1, void *arg2, void *arg3);
void func_003126C8(void *arg0, void *arg1);

extern u8 D_002C3630[] __attribute__((section(".data")));

void BtlObjAnim_SampleRot(u8 *arg0, u8 *arg1, u16 *arg2, f32 farg0) {
    s32 sp[4];
    s32 sp10[4];
    s32 n;
    s32 stride;
    s32 i;
    s32 s1;
    s32 found;
    s32 k;
    s32 v0;
    f32 f0;
    f32 f1;
    f32 fr;
    u8 *s5;
    u8 *a2;
    u8 *v3;

    n = U16AT(arg0, 2);
    if (U16AT(arg0, 0) & 1) {
        stride = n * 8;
    } else {
        stride = n * 24;
    }
    s5 = arg0 + stride + 4;

    if (n == 1) {
        a2 = arg0 + 4;
        Quat_Unpack(arg1, PAIR(a2, 0), a2);
        return;
    }

    i = *arg2;
    if (i >= n - 1) {
        *arg2 = 0;
        i = 0;
    }

    for (;;) {
        s1 = i + 1;
        a2 = arg0 + 4 + i * 8;
        v3 = s5 + s1 * 2;
        found = 0;
        for (;;) {
            if (!(s1 < n)) {
                break;
            }
            k = U16AT(v3, -2);
            f1 = (f32)k;
            a2 += 8;
            if (f1 == farg0) {
                Quat_Unpack(arg1, PAIR(a2, -8), a2);
                found = 1;
                break;
            }
            v0 = U16AT(v3, 0);
            if (f1 < farg0 && farg0 < (f32)v0) {
                f0 = (f32)(v0 - k);
                fr = (farg0 - f1) / f0;
                Quat_Unpack(sp, PAIR(a2, 0), a2);
                ((void (*)(void *, s64))Quat_Unpack)(sp10, PAIR(a2, -8));
                Quat_Slerp(fr, arg1, sp10, sp);
                found = 1;
                break;
            }
            f0 = (f32)v0;
            if (f0 == farg0) {
                Quat_Unpack(arg1, PAIR(a2, 0), a2);
                found = 1;
                break;
            }
            v3 += 2;
            s1 += 1;
        }
        if (found) {
            *arg2 = s1 - 1;
            return;
        }
        if (*arg2 != 0) {
            *arg2 = 0;
            i = 0;
            continue;
        }
        func_003126C8(arg1, D_002C3630);
        return;
    }
}
