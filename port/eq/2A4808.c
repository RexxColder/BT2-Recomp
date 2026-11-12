#include "common.h"

s32 func_002A3C68(s32 arg0);
void func_002A4CF0(s32 a0, s32 a1, s32 a2, s32 a3, s32 t0, s32 t1, s32 t2, s32 t3,
                   s32 s9, s32 s10, s32 s11, s32 s12, s32 s13, s32 s14, s32 s15, s32 s16, s32 s17);

void func_002A4808(s32 arg0, s32 arg1) {
    s32 s0;
    s32 s1;
    s32 s2;
    s32 s3;
    s32 s4;
    s32 a0;
    s32 v;
    s32 t6;
    s32 t7;

    s0 = 0;
    s1 = 0;
    s2 = 0;
    s3 = 0;
    s4 = 0;
    a0 = arg0;
    if (arg0 == 0) {
        s2 = 0x1C0;
        s1 = 0x18B;
    } else if (arg0 > 0) {
        if (arg0 == 1) {
            s2 = 0x160;
            s1 = 0x18B;
        }
    } else if (arg0 == -1) {
        s2 = 0x1A4;
        s1 = 0x18B;
    }
    if (arg1 >= 0) {
        s4 = 1;
        s3 = 0x80;
        a0 = arg1 / 50;
        s0 = (arg1 / 50) % 2;
    }
    v = func_002A3C68(a0);
    t6 = s0 << 5;
    t7 = s4 << 5;
    func_002A4CF0(0x1E, 6, v, 1, s2, s1, s2 + 0x20, s1 + 0x20,
                  0x80, 0x80, 0x80, s3, t6, t7, t6 + 0x20, t7 + 0x20, 0);
}
