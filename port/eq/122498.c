#include "common.h"

f32 func_00121648(s32 a0, s32 a1);
s32 func_001216A8(s32 arg0);
s32 func_00126058(s32 arg0, s32 arg1, s32 arg2);
s32 func_00126040(s32 arg0);
f32 func_00240D50(s32 arg0, s32 arg1);
s32 func_00240E50(s32 arg0, s32 arg1);
void func_00208DE8(s32 arg0, s32 arg1, s32 arg2);

void func_00122498(s32 *arg0) {
    s32 sp[4];
    u8 *s1;
    u8 *s2;
    f32 f1;
    f32 f2;
    f32 f20;
    s32 a0;
    s32 a1;
    s32 a2;
    s32 v;

    s1 = (u8 *)arg0 + 0xFE0;
    s2 = (u8 *)arg0 + 0xBE0;
    *(s32 *)(s1 + 0x28) &= ~4;
    func_00208DE8(arg0[0], (s32)sp, 3);
    if (func_001216A8((s32)arg0) != 0) {
        if (func_00126058((s32)arg0, 0, 0x100) != 0) {
            f20 = func_00240D50(func_00126040((s32)arg0), 5);
            a0 = func_00126040((s32)arg0);
            a1 = 3;
        } else {
            f20 = func_00240D50(func_00126040((s32)arg0), 4);
            a0 = func_00126040((s32)arg0);
            a1 = 1;
        }
        f2 = f20 * (f32)func_00240E50(a0, a1);
        if (f2 < 100.0f) {
            f2 = 100.0f;
        }
        a2 = *(s32 *)(s1 + 8);
        a1 = 1;
        f1 = *(f32 *)(s2 + a2 * 4 + 0x2E0) * (1.0f - *(f32 *)(s1 + 0xC));
        if ((s8)*(s2 + a2 + 0x3E0) > 1) {
            do {
                v = a2 - a1;
                a1 += 1;
                f1 = f1 + *(f32 *)(s2 + v * 4 + 0x2E0);
            } while (a1 < (s8)*(s2 + a2 + 0x3E0));
        }
        if (!(f1 < f2) && !(func_00121648((s32)sp, (s32)(s1 + 0x60)) > 50.0f)) {
            *(s32 *)(s1 + 0x28) |= 4;
        }
    }
}
