#include "common.h"

s32 func_0024C148(void);
void func_0024C188(void *arg0, s32 arg1);
extern u8 *D_003879A0;

void func_0024C380(s32 arg0) {
    u8 *s5;
    u8 *s1;
    u8 *s0p;
    u8 *a1p;
    u8 *p;
    s32 s2;
    s32 s3;
    s32 v1;
    s32 r1;
    s32 r2;
    s32 r3;
    s32 a0;
    s32 cond;

    if (arg0 == 0) {
        s5 = (u8 *)(func_0024C148() + ((*(s32 *)(D_003879A0 + 0x1C8) + *(s32 *)(D_003879A0 + 0x1CC) * 7) * 0x22) + 0x1408);
    } else {
        s5 = D_003879A0 + 0x3314;
    }
    func_0024C188(s5, arg0);

    s2 = *(s32 *)(D_003879A0 + arg0 * 4 + 0x321C);
    if (s2 < 7) {
        s3 = s2 * 4 + 0x3330;
        s1 = s5 + s2 * 4;
        do {
            v1 = *(s16 *)s1;
            if (v1 == 0) {
                s2 += 1;
            } else if (arg0 != 0) {
                *(s32 *)(D_003879A0 + s3) = v1;
                s2 += 1;
            } else {
                r1 = func_0024C148();
                p = (u8 *)(*(s16 *)s1 * 4 + r1);
                *(u16 *)(p + 0x1F2E) = (u16)(*(u16 *)(p + 0x1F2E) + 1);

                s0p = *(u8 **)(D_003879A0 + 0x334C) + (*(s16 *)s1) * 0x30;
                r2 = func_0024C148();
                s0p = s0p - 0x30;
                a0 = *(s32 *)(s0p + 0x10);
                p = (u8 *)(*(s16 *)s1 * 4 + r2);
                cond = a0 < *(s16 *)(p + 0x1F2E);
                s2 += 1;
                if (cond) {
                    r3 = func_0024C148();
                    v1 = *(s16 *)s1;
                    a1p = *(u8 **)(D_003879A0 + 0x334C) + v1 * 0x30;
                    p = (u8 *)(v1 * 4 + r3);
                    *(u16 *)(p + 0x1F2E) = *(u16 *)(a1p - 0x20);
                }
            }
            *(s16 *)s1 = 0;
            *(s16 *)(s1 + 2) = 0;
            s3 += 4;
            s1 += 4;
        } while (s2 < 7);
    }
    func_0024C188(s5, arg0);
}
