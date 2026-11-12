#include "common.h"

void func_00129C28(void *arg0, void *arg1);
s32 func_0014EFA8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6);
void func_001513D0(f32 farg0, s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5,
                   s32 arg6, s32 arg7, s32 st0, s32 st1);
void func_00208DE8(s32 arg0, void *arg1, s32 arg2);
s32 func_0020B3D0(s32 arg0);

void func_00148E20(s32 arg0, u8 *arg1, void *arg2) {
    f32 sp10[4];
    f32 sp20[4];
    s32 var_s7, sp34, s1, v, r;
    u8 *s0, *fp, *s2, *s3, *s4;

    var_s7 = 0;
    s0 = *(u8 **)(arg1 + 0x38);
    fp = *(u8 **)(s0 + 0x90);
    sp34 = 0;
    func_00208DE8(func_0020B3D0(*(s32 *)fp), sp10, 3);
    do {
        s3 = *(u8 **)arg2 + sp34;
        s1 = 0;
        if (s3[0] != 0) {
            s4 = s0 + 0x94;
            s2 = s3 + 0x11;
            v = s2[0];
            do {
                s2 += 0x20;
                if (v == 5) {
                    func_00129C28(sp20, sp10);
                } else {
                    func_00129C28(sp20, s0 + 0x60);
                }
                r = func_0014EFA8(arg0, (s32)arg2, (s32)s4, var_s7, s1,
                                  *(s32 *)s0 & 1, *(s32 *)s0 & 4);
                if (r != 0) {
                    func_001513D0(*(f32 *)(s0 + 0x18), (s32)fp, (s32)arg2, (s32)s4,
                                  (s32)(s0 + 0x840), (s32)sp20, (s32)(s0 + 0x20), var_s7, s1,
                                  s1, r | 0x40);
                }
                s1 += 1;
                if (s1 < s3[0]) {
                    v = s2[0];
                } else {
                    break;
                }
            } while (1);
        }
        var_s7 += 1;
        sp34 += 0x110;
    } while (var_s7 < 0x10);
}
