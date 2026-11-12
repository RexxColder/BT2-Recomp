#include "common.h"

extern u8 *D_003876A0;

s32 EftTechEvt_GetEvents(void *arg0);
s32 func_00182368(void *a0, void *a1, void *a2, s32 a3, s32 t0, s32 t1, s32 t2, s32 t3);
s32 func_0014F2B8(void *a0, void *a1, s32 a2, s32 a3);
void func_001513D0(void *a0, void *a1, void *a2, void *a3, void *t0, void *t1, s32 t2, s32 t3, f32 f12, s32 st0,
                   s32 st1);

void func_00182380(u8 *arg0, s32 *arg1, s32 arg2) {
    u8 *s0;
    u8 *s2;
    u8 *s3;
    u8 *s4;
    u8 *s7;
    u8 *cur;
    s32 fp;
    s32 n;
    s32 j;
    s32 s1;
    s32 s5;
    s32 acc;
    s32 ev;
    s32 v0;
    s32 v1;
    s32 cnt;
    s32 *arr;
    s32 t1v;
    s32 skip;
    s32 go444;
    f32 f12;

    fp = arg2 & 0xFF;
    s0 = *(u8 **)(arg0 + 0x38);
    s2 = s0 + 0xA00;
    s7 = *(u8 **)(s2 + 0x28);

    n = s2[2];
    if (n > 0) {
        arr = (s32 *)(s0 + 0xA90);
        for (j = n; j > 0; j--) {
            arr[j] = arr[j - 1];
        }
    }

    s5 = 0;
    acc = 0;
    v0 = EftTechEvt_GetEvents(*(void **)s7);
    *(s32 *)(s0 + 0xA90) = v0 & ~0x80;

    do {
        cur = *(u8 **)(s7 + 0x20);
        ev = *(s32 *)cur;
        skip = 0;
        go444 = 0;
        if ((u32)(ev - 0xEC) < 3U || ev == 0xF0 || ev == 0xF9) {
            go444 = 1;
        }
        if (go444) {
            if ((*(u64 *)(D_003876A0 + 0x4D8) & 2) != 0) {
                if (s5 == 2) {
                    skip = 1;
                }
            }
        } else if (ev == 0xFC) {
            if (s5 == 7) {
                skip = 1;
            }
        } else if (ev == 0xFD) {
            if ((u32)(s5 - 10) < 2U) {
                skip = 1;
            }
        }

        if (!skip) {
            s3 = (u8 *)(*(s32 *)arg1 + acc);
            cnt = s3[0];
            if (cnt != 0) {
                s1 = 0;
                s4 = s3 + 0x11;
                v0 = s4[0];
                do {
                    v1 = (s2 + v0)[0x10];
                    s4 += 0x20;
                    if (v1 != 0) {
                        if (fp == 0) {
                            t1v = *(s32 *)(s0 + 0xA80);
                            v1 = func_00182368(*(void **)s7, arg1, s0, s5, s1, t1v & 2, t1v & 4,
                                               *(s32 *)(s0 + 0xA90 + (s2[2] << 2)));
                        } else {
                            v1 = func_0014F2B8(arg1, s0, s5, s1);
                        }
                        v0 = *(s32 *)(s0 + 0xA80);
                        if ((v0 & 0x200) != 0) {
                            v1 = 2;
                        }
                        if (v1 != 0) {
                            f12 = *(f32 *)(s2 + 8);
                            /* asm 0x182540: a0 = s7 itself (not *s7 as for 182368) */
                            func_001513D0((void *)s7, arg1, s0, s0 + 0x7B0, s2 + 0x40, s2 + 0x60, s5, s1, f12,
                                          s1, v1);
                        }
                        cnt = s3[0];
                    }
                    s1 += 1;
                    if (s1 < cnt) {
                        v0 = s4[0];
                    } else {
                        break;
                    }
                } while (1);
            }
        }

        acc += 0x110;
        s5 += 1;
    } while (s5 < 16);

    if (fp != 0) {
        return;
    }
    v1 = *(s32 *)(s0 + 0xA80);
    if ((v1 & 2) != 0) {
        *(s32 *)(s0 + 0xA80) = v1 | 0x80;
    }
    if (arg0[1] == 0) {
        *(s32 *)(s0 + 0xA80) = *(s32 *)(s0 + 0xA80) | 0x20;
        arg0[1] = arg0[1] + 1;
    }
}
