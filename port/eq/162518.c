#include "common.h"

extern u8 D_0036E440[] __attribute__((section(".data")));

void EftPtcl3_SetPolys(s32 arg0, s32 arg1);
void EftPtcl4_SetPolys(s32 arg0, s32 arg1);
void EftRibbon_SetEnd(s32 arg0, s32 arg1, s32 arg2);
void EftRibbon_SetPos(s32 arg0, s32 arg1);
s32 func_0014EFA8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6);
s32 func_0014F2B8(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_001513D0(f32 farg0, s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5,
                   s32 arg6, s32 arg7, s32 arg8, s32 arg9);

void func_00162518(s32 arg0, u8 *arg1, s32 *arg2, s32 arg3) {
    s64 sp10;
    s64 sp18;
    s32 sp24;
    s32 sp28;
    s32 sp30;
    u8 *p2c;
    u8 *s0;
    u8 *s4;
    u8 *s5;
    u8 *s6;
    s32 fp;
    s32 idx;
    s32 k;
    s32 v;
    s32 w;

    s0 = *(u8 **)(arg1 + 0x38);
    sp10 = *(s64 *)(D_0036E440 + 0);
    sp18 = *(s64 *)(D_0036E440 + 8);
    sp24 = arg3 & 0xFF;
    sp28 = *(s32 *)(s0 + 0xB0);
    sp30 = 0;
    idx = 0;
    do {
        p2c = (u8 *)(*arg2 + sp30);
        k = 0;
        if (*p2c != 0) {
            s6 = s0 + 0xB4;
            s5 = s0 + 0x198;
            s4 = s0 + 0x47C;
            fp = 0x260;
            do {
                if (sp24 == 0) {
                    w = *(s32 *)s0;
                    v = func_0014EFA8(arg0, (s32)arg2, (s32)s6, idx, k, w & 1, w & 4);
                } else {
                    v = func_0014F2B8((s32)arg2, (s32)s6, idx, k);
                }
                w = *(s32 *)s0;
                v = ((w & 0x100) != 0) ? 2 : v;
                if (v != 0) {
                    func_001513D0(*(f32 *)(s0 + 0x18), sp28, (s32)arg2, (s32)s6, (s32)(s0 + 0x860),
                                  (s32)(s0 + 0x80), (s32)(s0 + 0x30), idx, k, k, v);
                }
                if (idx == 2) {
                    w = *(s32 *)(s5 + 0x264);
                    if (w != 0) {
                        if (*(s32 *)s0 & 0x200) {
                            EftRibbon_SetPos(w, (s32)&sp10);
                            EftRibbon_SetEnd(*(s32 *)(s5 + 0x264), (s32)&sp10, 0);
                        }
                    }
                }
                if (idx == 4) {
                    w = *(s32 *)(s5 + fp + 0xC);
                    if (w != 0) {
                        EftPtcl4_SetPolys(w, 1);
                    }
                }
                if (idx == 0xB) {
                    w = *(s32 *)(s4 + 0x20);
                    if (w != 0) {
                        EftPtcl3_SetPolys(w, 1);
                    }
                }
                if (idx == 0xA) {
                    w = *(s32 *)(s4 + 0);
                    if (w != 0) {
                        EftPtcl3_SetPolys(w, 1);
                    }
                }
                k += 1;
                s4 += 4;
                fp += 4;
            } while (k < (s32)*p2c);
        }
        sp30 += 0x110;
        idx += 1;
    } while (idx < 0x10);
}
