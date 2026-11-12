#include "common.h"

extern void *gEftSurf;

s32 func_00129720(void *arg0, void *arg1, void *arg2, s32 arg3);
void func_00129A50(void *arg0, void *arg1, void *arg2, s32 arg3);
void EftSurf_PutTri(void *a0, void *a1, void *a2, void *a3, void *t0, void *t1, void *t2,
                    void *t3, s32 st0, s64 st1);

void func_00137AB0(u8 *arg0, s64 arg1) {
    s32 fr[0x60];
    u8 *frame = (u8 *)fr;
    u8 *s0, *s1, *s6, *s7, *sp10, *spA0, *sp18, *sp28, *p3;
    s32 s2, s4, v;

    s1 = arg0;
    s2 = 4;
    s4 = 3;
    s0 = *(u8 **)((u8 *)gEftSurf + 0x10);
    do {
        s2 -= 1;
        s4 = func_00129720(s1, s1, s0, s4);
        s0 += 0x10;
    } while (s2 >= 0);

    if (s4 != 0) {
        spA0 = frame + 0xA0;
        sp10 = frame + 0x10;
        sp18 = frame + 0x18;
        sp28 = frame + 0x28;
        func_00129A50(sp10, spA0, s1, s4);
        s2 = 2;
        if (s2 < s4) {
            s6 = spA0;
            s7 = arg0 + 0x20;
            s0 = arg0 + 0x60;
            s1 = sp28;
            do {
                v = *(s32 *)sp18;
                if (v > 0xFFFFFF) {
                    v = 0xFFFFFF;
                }
                *(s32 *)sp18 = v;
                p3 = sp18 + (s2 * 0x10);
                s2 += 1;
                if (*(s32 *)s1 > 0xFFFFFF) {
                    *(s32 *)s1 = 0xFFFFFF;
                }
                if (*(s32 *)p3 > 0xFFFFFF) {
                    *(s32 *)p3 = 0xFFFFFF;
                }
                EftSurf_PutTri(sp10, sp10 + ((s2 - 2) * 0x10), sp10 + ((s2 - 1) * 0x10), s6,
                               s6 + ((s2 - 2) * 0x10), s6 + ((s2 - 1) * 0x10), s7,
                               s0 - 0x10, (s32)(s0 + 0x20), arg1);
                s0 += 0x30;
                s1 += 0x10;
            } while (s2 < s4);
        }
    }
}
