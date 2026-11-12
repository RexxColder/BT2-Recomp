#include "common.h"

extern s32 func_0026EBC0(s32 arg0, s32 arg1, s32 arg2);
extern void func_0026ED60(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, f32 farg0, f32 farg1);
extern void func_00249FB8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6);
extern void func_002495A8(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern void func_00249778(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern s32 func_003C2840(void);
extern s32 func_003C28E8(void);
extern s32 func_0026EEC8(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern void func_003C2D38(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern s32 func_00325830(s32 arg0, s32 arg1, s32 arg2);
extern s32 func_0026EFC8(s32 arg0, s32 arg1, s32 arg2);
extern void func_003C2918(s32 arg0, s8 arg1);
extern s32 func_0026EC48(s32 arg0, s32 arg1, s32 arg2);
extern s32 func_00249BB8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6);
extern void func_00249DB8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6);
extern void func_0026EF38(s32 arg0, s32 arg1, f32 f12, f32 f13);
extern void func_0026EEF8(s32 arg0, s32 arg1, f32 f12);
extern f32 func_0026F148(s32 arg0, s32 arg1);
extern void func_0026EA58(s32 arg0);
extern void BattleSetup_Finish(void);

extern u8 *D_00421CF4 __attribute__((section(".data")));
extern u8 *D_387F2C __attribute__((section(".data")));
extern u8 D_00422CD0[], D_00422CD8[], D_00422CE8[], D_00422CF8[], D_00422D10[], D_00422D20[], D_00422D30[],
    D_00422D40[], D_00422D50[], D_00422D68[], D_00422D80[], D_00422DA0[], D_00422DB8[], D_00422DC0[], D_00422DC8[],
    D_00422DE0[], D_00422DF8[], D_00422E10[], D_00422E20[], D_00422E30[], D_00422E40[], D_00422E48[], D_00422E58[],
    D_00422ED8[], D_00422F58[], D_00422FD8[], D_00422FE8[];

#define W(p, o) (*(s32 *)((p) + (o)))
#define T D_00421CF4
#define P(x) ((s32)(x))

void func_003C38A8(void) {
    u8 sp[0x270];
    u8 *fp = sp + 0x10;
    u8 *buf1 = sp + 0x90;
    u8 *buf2 = sp + 0x110;
    u8 *buf3 = sp + 0x190;
    s32 s2, i, k, b, e, s0, a2, a3;
    f32 f20, f0;

    W(sp, 0x18) = 0x200;
    W(sp, 0x1C) = 0x100;
    W(sp, 0x10) = 0;
    W(sp, 0x14) = 0;
    s2 = P(T + 0x38);
    func_0026EBC0(s2, P(D_00422CD0), P(sp));
    func_0026ED60(s2, P(sp), P(fp), P(T + 0x664), 0, -0x1.0000000000000p-2f, 0.0f);
    s2 = P(T + 0x60);
    func_0026EBC0(s2, P(D_00422CD8), P(sp));
    func_00249FB8(s2, P(sp), 0, 0, W(T, 8), W(T, 0x210), 1);
    if (W(T, 0x1FC) & 0x20) {
        func_0026EBC0(s2, P(D_00422CE8), P(sp));
        func_002495A8(s2, P(sp), P(T + 0x670), 1);
        func_0026EBC0(s2, P(D_00422CF8), P(sp));
        func_00249778(s2, P(sp), P(T + 0x674), 3);
    } else {
        func_0026EBC0(s2, P(D_00422D10), P(sp));
        func_002495A8(s2, P(sp), P(T + 0x668), 1);
        func_0026EBC0(s2, P(D_00422D20), P(sp));
        func_00249778(s2, P(sp), P(T + 0x66C), 3);
    }
    func_0026EBC0(s2, P(D_00422D30), P(sp));
    s0 = func_003C2840();
    a3 = func_003C28E8();
    func_0026EEC8(s2, P(sp), s0, a3);
    func_0026EBC0(s2, P(D_00422D40), P(sp));
    func_003C2D38(P(fp), 0, W(T, 0x1CC), W(T, 0x1C8));
    func_0026EEC8(s2, P(sp), W(sp, 0x10) - 0x38, W(sp, 0x14) - 8);
    for (i = 0; i < 0x24;) {
        s0 = i + 0x1D0;
        func_00325830(P(sp + 0x30), P(D_00422D50), i);
        func_0026EBC0(s2, P(sp + 0x30), P(sp));
        i++;
        b = *(s8 *)(T + s0 + 4);
        if (b == 0) {
            func_0026EFC8(s2, P(sp), 8);
        } else {
            func_0026EFC8(s2, P(sp), 4);
            func_003C2918(P(fp), *(s8 *)(T + s0 + 4));
            func_0026EC48(s2, P(sp), P(fp));
        }
    }
    W(sp, 0x10) = 0;
    W(sp, 0x18) = 0x100;
    k = W(T, 0x204);
    W(sp, 0x14) = k << 5;
    W(sp, 0x1C) = (k << 5) + 0x20;
    func_0026EBC0(s2, P(D_00422D68), P(sp));
    func_0026EC48(s2, P(sp), P(fp));
    W(sp, 0x10) = 0;
    k = W(T, 0x204);
    W(sp, 0x18) = 0x200;
    W(sp, 0x14) = k << 6;
    W(sp, 0x1C) = (k << 6) + 0x40;
    func_0026EBC0(s2, P(D_00422D80), P(sp));
    func_0026EC48(s2, P(sp), P(fp));
    W(sp, 0x10) = 0;
    k = W(T, 0x204);
    W(sp, 0x18) = 0x200;
    W(sp, 0x14) = k << 7;
    W(sp, 0x1C) = (k << 7) + 0x80;
    func_0026EBC0(s2, P(D_00422DA0), P(sp));
    func_0026EC48(s2, P(sp), P(fp));
    func_0026EBC0(s2, P(D_00422DB8), P(sp));
    func_00249BB8(s2, P(sp), 0, 0, W(T, 0x10), *(s16 *)(T + 0x65C), 0);
    func_0026EBC0(s2, P(D_00422DC0), P(sp));
    func_00249DB8(s2, P(sp), 0, 0, W(T, 0x14), *(s16 *)(T + 0x65C), 0);
    for (i = 0; i < 3;) {
        func_00325830(P(sp + 0x70), P(D_00422DC8), i);
        func_0026EBC0(s2, P(sp + 0x70), P(sp));
        e = P(D_387F2C) + 34 * (W(T, 0x1C0) + i);
        if (*(u16 *)(e + 0x1DFC) & 1) {
            func_00249BB8(s2, P(sp), 0, 0, W(T, 0x10), *(s16 *)(e + 0x1DF8), 0);
        }
        func_0026EFC8(s2, P(sp), 4);
        func_00325830(P(sp + 0x70), P(D_00422DE0), i);
        func_0026EBC0(s2, P(sp + 0x70), P(sp));
        e = P(D_387F2C) + 34 * (W(T, 0x1C0) + i);
        i++;
        if (*(u16 *)(e + 0x1DFC) & 1) {
            func_00249DB8(s2, P(sp), 0, 0, W(T, 0x14), *(s16 *)(e + 0x1DF8), 0);
        }
        func_0026EFC8(s2, P(sp), 4);
    }
    func_0026EBC0(s2, P(D_00422DF8), P(sp));
    k = W(T, 0x1BC) - W(T, 0x1C0);
    func_0026EEC8(s2, P(sp), 0, k * 58);
    func_0026EBC0(s2, P(D_00422E10), P(sp));
    func_0026EFC8(s2, P(sp), 8);
    func_0026EBC0(s2, P(D_00422E20), P(sp));
    if (W(T, 0x1C0) > 0) {
        func_0026EFC8(s2, P(sp), 4);
    } else {
        func_0026EFC8(s2, P(sp), 8);
    }
    W(sp, 0x18) = 0x40;
    W(sp, 0x1C) = 0x20;
    W(sp, 0x10) = 0x20;
    W(sp, 0x14) = 0;
    func_0026EBC0(s2, P(D_00422E30), P(sp));
    func_0026EC48(s2, P(sp), P(fp));
    if (W(T, 0x1C0) < 7) {
        func_0026EFC8(s2, P(sp), 4);
    } else {
        func_0026EFC8(s2, P(sp), 8);
    }
    f0 = (f32)W(T, 0x1C0) * 0x1.770a3c0000000p+7f / 0x1.4000000000000p+3f;
    s0 = (s32)f0;
    if (f0 >= 0x1.0000000000000p+31f) {
        s0 = (s32)(f0 - 0x1.0000000000000p+31f) | (s32)0x80000000;
    }
    f20 = 1.0f;
    func_0026EBC0(s2, P(D_00422E40), P(sp));
    func_0026EF38(s2, P(sp), f20, 0x1.c20c460000000p+0f);
    func_0026EEC8(s2, P(sp), 0, s0);
    if (W(T, 0x1FC) & 0x80) {
        *(f32 *)(T + 0x67C) = *(f32 *)(T + 0x67C) + 0x1.3333320000000p-4f;
        if (f20 <= *(f32 *)(T + 0x67C)) *(f32 *)(T + 0x67C) = f20;
    } else {
        W(T, 0x67C) = 0;
    }
    func_0026EBC0(s2, P(D_00422E48), P(sp));
    func_0026EEF8(s2, P(sp), *(f32 *)(T + 0x67C));
    s2 = P(T + 0x88);
    __builtin_memcpy(buf1, D_00422E58, 0x80);
    for (i = 0; i < 2;) {
        func_0026EBC0(s2, P(buf1 + (i << 6)), P(sp));
        if (i == W(T, 0x1C4)) {
            i++;
            func_0026EFC8(s2, P(sp), 8);
        } else {
            func_0026EFC8(s2, P(sp), 4);
            i++;
        }
    }
    __builtin_memcpy(buf2, D_00422ED8, 0x80);
    for (i = 0; i < 2;) {
        k = i << 6;
        W(sp, 0x1C) = k + 0x40;
        W(sp, 0x14) = k;
        W(sp, 0x10) = 0;
        W(sp, 0x18) = 0x80;
        func_0026EBC0(s2, P(buf2 + k), P(sp));
        func_0026EC48(s2, P(sp), P(fp));
        if (i == W(T, 0x1C4)) {
            i++;
            func_0026EFC8(s2, P(sp), 8);
        } else {
            func_0026EFC8(s2, P(sp), 4);
            i++;
        }
    }
    __builtin_memcpy(buf3, D_00422F58, 0x80);
    W(sp, 0x10) = 0;
    W(sp, 0x18) = 0x80;
    k = W(T, 0x1C4) << 6;
    W(sp, 0x14) = k;
    W(sp, 0x1C) = k + 0x40;
    func_0026EBC0(s2, P(buf3 + (W(T, 0x1C4) << 6)), P(sp));
    f20 = func_0026F148(s2, P(sp));
    func_0026EBC0(s2, P(D_00422FD8), P(sp));
    func_0026EC48(s2, P(sp), P(fp));
    func_0026EBC0(s2, P(D_00422FE8), P(sp));
    k = W(T, 0x1C4);
    func_0026EEC8(s2, P(sp), 0, (k << 6) + k);
    func_0026EEF8(s2, P(sp), f20);
    for (i = 0; i < 3; i++) {
        if (i != 2) func_0026EA58(P(T + i * 0x28 + 0x38));
    }
    BattleSetup_Finish();
    func_0026EA58(P(T + 0x88));
}
