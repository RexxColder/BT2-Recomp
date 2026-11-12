#include "common.h"

#define LD32(p, off) (*(s32 *)((u8 *)(p) + (off)))
#define PTR(v) ((u8 *)(s32)(v))

void func_002D1510(s32 arg0, void *arg1, void *arg2);
s32 func_002D2540(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_002D25B8(s32 arg0, s32 arg1, f32 farg0, f32 farg1);

extern u8 D_00346DD8[] __attribute__((section(".data")));

/* 0x002D23F0: sets the flag at arg3 from two words of the object (func_002D1510 gives them): when the second
 * word is 1 the first is compared with -2 (flag 1) or the work goes to func_002D2540; otherwise the first word
 * is moved by (second * arg4) / table[+8] and the ratio of arg1*10000/arg2 is compared with the moved word. */
void func_002D23F0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 w[2];
    s32 t;
    f32 f1;
    f32 f2;
    f32 f0;
    f32 f13;
    u8 *p;

    p = PTR(arg0);
    func_002D1510(arg0, &w[0], &w[1]);

    if (w[1] == 1) {
        if (w[0] == -2) {
            LD32(arg3, 0) = 1;
            return;
        }
        func_002D2540(arg0, arg1, arg2, arg3);
        return;
    }

    t = (s32)((u32)w[1] * (u32)arg4) / LD32(D_00346DD8, 8);
    w[0] = w[0] + t;

    f0 = (f32)arg1 * 10000.0f;
    f1 = f0 / (f32)arg2;
    f2 = (f32)w[1];
    f0 = (f32)w[0] * 10000.0f;
    f13 = f0 / f2;

    if (LD32(p, 0xA48) != 1) {
        func_002D25B8(arg0, arg3, f1, f13);
        return;
    }
    if (f1 <= f13) {
        LD32(arg3, 0) = 1;
    } else {
        LD32(arg3, 0) = 0;
    }
}
