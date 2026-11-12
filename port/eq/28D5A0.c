#include "common.h"

#define F(p, off) (*(f32 *)((u8 *)(p) + (off)))

extern f32 D_003870F4;
extern f32 D_003870F8;

s32 ColBox_ClipRay(u8 *arg0, u8 *arg1, u8 *arg2) {
    u8 sp[0x30];
    s32 t2;
    s32 i;
    s32 best;
    s32 bestoff;
    s32 flag;
    f32 mn;
    f32 mx;
    f32 origin;
    f32 t;
    f32 pt;
    f32 d;

    t2 = 1;
    for (i = 0; i < 3; i++) {
        origin = F(arg1, 4 * i);
        mn = F(arg0, 4 * i);
        mx = F(arg0, 0xC + 4 * i);
        if (origin < mn) {
            sp[i] = 1;
            t2 = 0;
            F(sp, 0x20 + 4 * i) = mn;
        } else if (!(mx < origin)) {
            sp[i] = 2;
        } else {
            sp[i] = 0;
            t2 = 0;
            F(sp, 0x20 + 4 * i) = mx;
        }
    }

    if (t2 != 0) {
        F(arg2, 0) = F(arg1, 0);
        F(arg2, 4) = F(arg1, 4);
        F(arg2, 0xC) = 1.0f;
        F(arg2, 8) = F(arg1, 8);
        return 1;
    }

    for (i = 0; i < 3; i++) {
        flag = sp[i];
        if ((flag != 2) && (F(arg1, 0x10 + 4 * i) != 0.0f)) {
            F(sp, 0x10 + 4 * i) = (F(sp, 0x20 + 4 * i) - F(arg1, 4 * i)) / F(arg1, 0x10 + 4 * i);
        } else {
            F(sp, 0x10 + 4 * i) = -1.0f;
        }
    }

    best = 0;
    bestoff = 0;
    for (i = 1; i < 3; i++) {
        if (F(sp, 0x10 + bestoff) < F(sp, 0x10 + 4 * i)) {
            best = i;
            bestoff = 4 * i;
        }
    }
    if (F(sp, 0x10 + bestoff) < 0.0f) {
        return 0;
    }

    for (i = 0; i < 3; i++) {
        if (best == i) {
            F(arg2, 4 * i) = F(sp, 0x20 + 4 * i);
        } else {
            t = F(sp, 0x10 + bestoff);
            pt = F(arg1, 4 * i) + (t * F(arg1, 0x10 + 4 * i));
            F(arg2, 4 * i) = pt;

            mn = F(arg0, 4 * i);
            if (pt < mn) {
                d = mn - pt;
                d = (d < 0.0f) ? -d : d;
                if (D_003870F4 < d) {
                    return 0;
                }
            }
            mx = F(arg0, 0xC + 4 * i);
            if (mx < pt) {
                d = pt - mx;
                d = (d < 0.0f) ? -d : d;
                if (D_003870F8 < d) {
                    return 0;
                }
            }
        }
    }
    return 1;
}
