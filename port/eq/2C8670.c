#include "common.h"

s32 func_002C2FF0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_002CA048(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

s32 func_002C8670(s32 arg0, s32 *arg1) {
    u8 *t4;
    u8 *t3;
    s32 a2;
    s32 a3;
    s32 t6;
    s32 t1;
    s32 t2;
    s32 cnt;
    s32 x1;
    s32 y1;
    s32 ax;
    s32 ay;
    s32 v1;
    s32 v0;
    s32 w;
    s32 i;
    s32 spin;
    s32 *arr;

    t4 = *(u8 **)(arg0 + 0x1FC0);
    a3 = arg1[1];
    a2 = arg1[0];
    t3 = t4 + 4;
    t6 = *(s32 *)(arg0 + 0x38);
    t1 = *(s32 *)(t3 + 0x1C);
    if ((*(s32 *)(t3 + 8) * *(s32 *)(t3 + 0xC)) < a2 * a3) {
        return func_002C2FF0(arg0, 0xFF000F17, a2, a3);
    }
    x1 = ((a2 < 0) ? (a2 + 0xF) : a2) >> 4;
    y1 = ((a3 < 0) ? (a3 + 0xF) : a3) >> 4;
    if (t6 == 2) {
        cnt = (x1 * y1) << 10;
    } else {
        cnt = x1 * y1 * 0x180;
    }
    t2 = cnt + 0x40;

    v1 = *(s32 *)(t3 + 0x14);
    v0 = *(s32 *)(t3 + 0x18);
    a3 = v1 + 0xF;
    a2 = v0 + 0xF;
    ax = ((v1 < 0) ? a3 : v1) >> 4;
    ay = ((v0 < 0) ? a2 : v0) >> 4;
    if (t6 == 2) {
        v0 = ((ax * ay) << 10) + 0x40;
    } else {
        v0 = (ax * ay) * 0x180 + 0x40;
    }
    if ((u32)v0 < (u32)t2) {
        return func_002C2FF0(arg0, 0xFF000F18, a2, a3);
    }

    w = *(s32 *)(t3 + 0x20);
    if (w != 0) {
        if (t1 > 0) {
            arr = (s32 *)(t4 + 0x30);
            i = 0;
            do {
                i += 1;
                arr[i - 1] = w;
                w += t2;
            } while (i < t1);
        }
    } else if (t1 > 0) {
        spin = t1 - 1;
        do {
            spin -= 1;
        } while (spin != 0);
    }
    *(s32 *)(t4 + 0x178) = t1;
    func_002CA048((s32)(t4 + 0x180), (s32)(t4 + 0x30), t1, a3);
    return 0;
}
