#include "common.h"

#define W(p, off) (*(s32 *)((u8 *)(p) + (off)))
#define B(p, off) (*(u8 *)((u8 *)(p) + (off)))

s32 func_0014EFA8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7);
s32 func_0014F2B8(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_001513D0(f32 farg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7,
                   s32 arg8, s32 st0, s32 st1);

extern u8 *D_003876A0;

void func_00190CA8(s32 arg0, u8 *arg1, s32 arg2, s32 arg3, s32 u4, s32 u5, s32 u6, s32 arg7) {
    u8 *s2;
    u8 *s6;
    u8 *fp;
    u8 *s3;
    u8 *temp_a0;
    u8 *a1p;
    s32 s4;
    s32 s1;
    s32 sp18;
    s32 sp14;
    s32 v1;
    s32 v0;
    s32 result;
    s32 v;
    s32 dflt;
    s32 go;
    s32 process;
    u8 v12;

    s4 = 0;
    s2 = (u8 *)W(arg1, 0x38);
    sp14 = arg3 & 0xFF;
    fp = s2 + 0x60;
    s6 = (u8 *)W(s2, 0);
    sp18 = 0;

    do {
        temp_a0 = (u8 *)W(s6, 0x20);
        v1 = W(temp_a0, 0);

        dflt = 0;
        if (v1 == 0x54 || v1 == 0x90) {
            if (!((u32)(s4 - 0xA) < 2U)) {
                dflt = 1;
            }
        } else if (v1 == 0x7D) {
            if (!((*(s64 *)(D_003876A0 + 0x4D8)) & 2) || (s4 != 7)) {
                dflt = 1;
            }
        } else {
            dflt = 1;
        }

        if (dflt) {
            s3 = (u8 *)W(arg2, 0) + sp18;
            s1 = 0;
            if (B(s3, 0) != 0) {
                do {
                    v1 = W(W(s6, 0x20), 0);
                    v0 = s1 << 5;
                    process = 1;
                    if ((v1 == 0x58) && (s4 == 0xB)) {
                        if (!((*(s64 *)(D_003876A0 + 0x4D8)) & 2)) {
                            if (s1 == 2) {
                                process = 0;
                            }
                        } else if ((s1 == 0) || (s1 == 2)) {
                            process = 0;
                        }
                    }
                    if (process) {
                        a1p = s3 + (v0 + 0x10);
                        if (B(a1p, 1) == W(s2, 0x1C)) {
                            v12 = B(a1p, 0);
                            go = 0;
                            if (v12 == W(s2, 0x20)) {
                                go = 1;
                            } else if ((v12 == 2) && !(B(a1p, 7) & 2)) {
                                go = 1;
                            }
                            if (go) {
                                if (sp14 == 0) {
                                    result = func_0014EFA8(arg0, arg2, (s32)fp, s4, s1,
                                                           W(s2, 0x30) & 2, W(s2, 0x30) & 8, arg7);
                                } else {
                                    result = func_0014F2B8(arg2, (s32)fp, s4, s1);
                                }
                                v = (W(s2, 0x30) & 0x10) ? 2 : result;
                                if (v != 0) {
                                    func_001513D0(*(f32 *)(s2 + 0x38), (s32)s6, arg2, (s32)fp,
                                                  W(s2, 8), (s32)(s2 + 0x820), (s32)(s2 + 0x40), s4, s1,
                                                  s1, v);
                                }
                            }
                        }
                    }
                    s1 += 1;
                } while (s1 < B(s3, 0));
            }
        }
        s4 += 1;
        sp18 += 0x110;
    } while (s4 < 0x10);
}
