#include "common.h"

extern void func_00405C98();
extern void func_00243968(s32 arg0, s32 arg1, s32 arg2);
extern void func_002711A0(void);
extern void func_00405898(void);
extern void func_0028B090(void);
extern void func_0028C0A8(void);
extern void func_00297978();
extern void func_002438E8(void);
extern void func_00407AC8(void);
extern void func_00406CA0(void);
extern void BattleSetup_Finish(void);
extern void func_00409698(void);
extern void func_002437E8(void);
extern void func_00271240();
extern void func_00409338(void);
extern s32 ColorFade_IsFadingOut();
extern s32 ColorFade_IsOutDone();
extern void func_00101498(void);
extern void func_00407BC0(void);
extern void func_00407BE0(s32 *arg0);
extern s32 GetTimerSystemTime();
extern void func_00325370(s64 arg0);
extern s32 rand(void);
extern s32 func_0024B6C8(s32 arg0);
extern void func_00101A10();
extern void func_00101AB0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern s64 func_0024B010(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
extern s32 func_0024B7F0(s32 arg0);
extern s32 func_00101A88(s32 arg0);
extern void func_00101AF8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8,
                          s32 arg9, s32 arg10, s32 arg11, s32 arg12, s32 arg13, s64 arg14, s32 arg15, s32 arg16,
                          s32 arg17);
extern void func_00406BF0(void);
extern void func_0028B218(void);

extern u8 *D_0042BB74 __attribute__((section(".data")));
extern u8 *D_3876A4 __attribute__((section(".data")));
extern u8 *D_3876A0 __attribute__((section(".data")));
extern u8 *D_387F2C __attribute__((section(".data")));

#define W(p, o) (*(s32 *)((p) + (o)))

s32 func_00409BB8(s32 arg0) {
    u8 sp[0xE0];
    u8 *base;
    u8 *fp;
    u8 *p;
    s32 i, s1, s2, idx, cnt, r, a1, k;
    s64 s3;

    W(sp, 0x80) = 1;
    func_00405C98(arg0);
    func_00243968(0, 0, 0);

    for (;;) {
        func_002711A0();
        func_00405898();
        func_0028B090();
        func_0028C0A8();
        func_00297978();
        func_002438E8();
        func_00407AC8();
        func_00406CA0();
        BattleSetup_Finish();
        func_00409698();
        func_002437E8();
        func_00271240();
        base = D_0042BB74;
        if (W(base, 0x210) & 0xC000) {
            if (W(base, 0x36C0) != 4) continue;
            func_00409338();
            continue;
        }
        if (ColorFade_IsFadingOut(4)) {
            if (W(sp, 0x80) == 0) {
                if (W(D_3876A4, 0x1C) != 0x3F) continue;
            }
            func_00101498();
            continue;
        }
        if (ColorFade_IsOutDone()) {
            if (W(D_0042BB74, 0x36C0) == 4) break;
            continue;
        }
        base = D_0042BB74;
        {
            s32 f = W(base, 0x210);
            s32 v;
            if ((f & 0xC00) != 0xC00) {
                if (W(base, 0x36E8) == 0) func_00407BE0((s32 *)(sp + 0x80));
                continue;
            }
            if ((f & 0x400000) == 0) {
                W(base, 0x210) = f | 0x400000;
                W(D_0042BB74, 0x36D8) = 1;
                base = D_0042BB74;
            }
            v = W(base, 0x36D8);
            if (v != 0) continue;
            v = W(base, 0x36D4) - 1;
            W(base, 0x36D4) = v;
            if (v != -1) continue;
        }
        func_00407BC0();
        for (i = 0; i < 2; i++) {
            s32 s4 = 0x240 + 4 * i;
            s32 s5 = 0x260 + 4 * i;
            u8 *tbl;
            if (W(D_0042BB74, s4 + 4) == 0x82) {
                func_00325370(GetTimerSystemTime());
                do {
                    r = rand();
                    base = D_0042BB74;
                    cnt = W(base, 0x25C);
                    idx = r % cnt;
                    a1 = W(*(u8 **)(base + s5), 44 * idx);
                } while (a1 >= 0x82);
                W(base, s4 + 4) = a1;
                tbl = *(u8 **)(D_0042BB74 + s5);
                if (W(tbl, 44 * idx + 4) != 0) {
                    s1 = s4;
                    r = rand();
                    base = D_0042BB74;
                    tbl = *(u8 **)(base + s5) + 44 * idx;
                    k = r % W(tbl, 4);
                    W(base, s4 + 4) = W(tbl, 8 + 4 * k);
                } else {
                    s1 = 4 * i + 0x240;
                }
                r = rand();
                s2 = func_0024B6C8(W(D_0042BB74, s1 + 4));
                base = D_0042BB74;
                W(base, 4 * i + 0x234) = r % s2;
            }
        }
        base = D_0042BB74;
        W(D_3876A4, 0x390) = W(base, 0x214) + W(base, 0x21C) * 7;
        base = D_0042BB74;
        W(D_3876A4, 0x3A4) = W(base, 0x218) + W(base, 0x220) * 7;
        W(D_3876A4, 0x3B8) = W(D_0042BB74, 0x22C);
        W(D_3876A4, 0x3CC) = W(D_0042BB74, 0x230);
        W(D_3876A4, 0x430) = W(D_0042BB74, 0x234);
        W(D_3876A4, 0x444) = W(D_0042BB74, 0x238);
        W(D_3876A4, 0x3E0) = W(D_0042BB74, 0x244);
        W(D_3876A4, 0x3F4) = W(D_0042BB74, 0x248);
        W(D_3876A4, 0x408) = W(D_0042BB74, 0x224);
        W(D_3876A4, 0x41C) = W(D_0042BB74, 0x228);
    }

    /* exit at .L00409FA0 */
    if (W(sp, 0x80) == 0) {
        *(s64 *)(D_3876A0 + 0x4D8) = 0;
    } else {
        fp = *(u8 **)(D_3876A0 + 0x74);
        func_00101A10();
        *(s64 *)(D_3876A0 + 0x4D8) = 0;
        base = D_0042BB74;
        if (W(base, 0x36C4) == 1) {
            *(s64 *)(D_3876A0 + 0x4D8) |= 2;
        }
        for (i = 0; i < 2; i++) {
            W(sp, 0x50 + 4 * i) = W(base, 0x234 + 4 * i) + 9 * W(base, 0x244 + 4 * i);
        }
        r = W(D_0042BB74, 0x36C4);
        if (r == 1) {
            func_00101AB0(0, 1, 0, 0);
            func_00101AB0(1, 1, 0, 0);
            W(D_3876A4, 0x468) = W(D_0042BB74, 0x4BA8);
            W(D_3876A4, 0x470) = W(D_0042BB74, 0x8BA8);
            W(D_3876A4, 0x46C) = W(D_0042BB74, 0x4BAC);
            W(D_3876A4, 0x474) = W(D_0042BB74, 0x8BAC);
        } else if (r >= 2) {
            if (r == 2) {
                func_00101AB0(0, 1, 1, 0);
                func_00101AB0(1, 1, 1, 0);
            }
        } else if (r == 0) {
            func_00101AB0(0, 1, 0, 0);
            func_00101AB0(1, 1, 1, 0);
        }
        W(sp, 0x84) = 0x240;
        for (i = 0; i < 2; i++) {
            s32 s4 = 0x210 + 4 * i;
            s32 s6 = 4 * i;
            u8 *a2;
            u8 *v0;
            u8 *sbase;
            s32 ix;
            base = D_0042BB74;
            if (W(base, 0x210) & (0x40000 << i)) {
                a2 = D_3876A4;
                if (W(a2, 0x4C8) != 0 && W(a2, 0x4CC) != 0) {
                    u8 *s0 = *(u8 **)(a2 + s6 + 0x4C8);
                    ix = W(base + s4, 4) + W(base + s4, 0xC) * 7;
                    s3 = func_0024B010(W(base, 0x36DC), W(base, 0x36E0), (s32)(s0 + ix * 34 + 0x1408),
                                       (s32)(sp + 0x60), 0x14);
                    base = D_0042BB74;
                    ix = W(base + s4, 4) + W(base + s4, 0xC) * 7;
                    v0 = s0 + ix * 34;
                } else {
                    base = D_0042BB74;
                    ix = W(base + s4, 4) + W(base + s4, 0xC) * 7;
                    s3 = func_0024B010(W(base, 0x36DC), W(base, 0x36E0), (s32)(D_387F2C + ix * 34 + 0x1408),
                                       (s32)(sp + 0x60), 0x14);
                    base = D_0042BB74;
                    ix = W(base + s4, 4) + W(base + s4, 0xC) * 7;
                    v0 = D_387F2C + ix * 34;
                }
                s1 = *(s16 *)(v0 + 0x1426);
                r = func_0024B7F0(W(sp, 0x60));
                base = D_0042BB74;
                s2 = W(fp + (W(base, W(sp, 0x84) + 4) << 4), 0) + r;
            } else {
                s3 = 0;
                for (k = 7; k >= 0; k--) W(sp, 0x60 + 4 * k) = 1;
                s1 = 0;
                base = D_0042BB74;
                s2 = W(fp + (W(base, s6 + 0x244) << 4), 0);
            }
            r = func_00101A88(i);
            W(sp, 0x84) += 4;
            sbase = D_387F2C;
            base = D_0042BB74;
            func_00101AF8(r + 8, W(sp, 0x50 + s6), 0, W(sbase, 0x810), s1, W(sbase, s6 + 0x814) ^ 1, W(sp, 0x60),
                          W(sp, 0x64), W(sp, 0x68), W(sp, 0x6C), W(sp, 0x70), W(sp, 0x74), W(sp, 0x78), W(sp, 0x7C),
                          s3, s2, s2, W(fp + (W(base, s6 + 0x244) << 4), 4));
        }
    }
    if (W(D_0042BB74, 0x36C4) == 1) {
        base = D_0042BB74;
        __builtin_memcpy(D_387F2C, base + 0x3B14, 0x4000);
        __builtin_memcpy(*(u8 **)(D_3876A4 + 0x4D0), base + 0x8F1C, 0xB28);
        base = D_0042BB74;
        __builtin_memcpy(*(u8 **)(D_3876A4 + 0x4D4), base + 0x9A44, 0x90C);
        W(D_3876A4, 0x4C8) = 0;
        W(D_3876A4, 0x4CC) = 0;
    }
    func_00406BF0();
    func_0028B218();
    return W(sp, 0x80);
}
