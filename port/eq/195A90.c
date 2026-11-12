#include "common.h"

s32 func_0014EFA8(s32 a0, s32 a1, s32 a2, s32 a3, s32 t0, s32 t1, s32 t2);
void func_001513D0(f32 f12, s32 a0, s32 a1, s32 a2, s32 a3, s32 t0, s32 t1, s32 t2, s32 t3, s32 sp0, s32 sp8);
extern u8 *D_003876A0;

void func_00195A90(s32 arg0, u8 *arg1, u8 **arg2) {
    s32 k;
    s32 j;
    s32 sp10;
    s32 s6;
    s32 t4;
    s32 res;
    s32 doCall;
    u8 *s3;
    u8 *O;

    k = 0;
    O = *(u8 **)(arg1 + 0x38);
    s6 = *(s32 *)(O + 0xAF0);
    sp10 = 0;
    do {
        doCall = 1;
        if (*(s64 *)(D_003876A0 + 0x4D8) & 2) {
            if (k == 0xA || k == 7) {
                doCall = 0;
            }
        }
        if (doCall) {
            s3 = *arg2 + sp10;
            j = 0;
            if (*s3 != 0) {
                do {
                    if (k == 8 || k == 4 || k == 11 || k == 5) {
                        /* nothing to do for this slot */
                    } else if (k == 6 && j == 0) {
                        /* nothing to do for this slot */
                    } else {
                        res = func_0014EFA8(arg0, (s32)arg2, (s32)O, k, j, *(s32 *)(O + 0xB70) & 0x8, *(s32 *)(O + 0xB70) & 0x40);
                        t4 = res;
                        if ((*(s64 *)(O + 0xB70) & 0x208) == 0x200) {
                            if (k == 0xA) {
                                t4 = (j != 0) ? res : 2;
                            }
                            if (k == 7) {
                                t4 = (j != 0) ? t4 : 2;
                            }
                        }
                        if (t4 != 0) {
                            func_001513D0(*(f32 *)(O + 0xB14), s6, (s32)arg2, (s32)O,
                                          (s32)(O + 0x7B0), (s32)(O + 0xB30), (s32)(O + 0xB50),
                                          k, j, j, t4);
                        }
                    }
                    j += 1;
                } while (j < (s32)*s3);
            }
        }
        k += 1;
        sp10 += 0x110;
    } while (k < 0x10);
}
