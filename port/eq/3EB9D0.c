#include "common.h"

extern s32 func_0026EA88(s32 arg0);
extern void func_0026EAE0(s32 arg0, s32 arg1);
extern void func_0026EB78(s32 arg0, s32 arg1);
extern s32 func_0026EB70(s32 arg0);
extern s32 func_002493C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
extern s32 ColorFade_IsFadingOut();
extern s32 func_00297FE0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
extern void func_00243A80(s32 arg0, s32 arg1, s32 arg2);
extern void func_00101A10();
extern void func_00101AB0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern s32 func_00101A88(s32 arg0);
extern void func_00101AF8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8,
                          s32 arg9, s32 arg10, s32 arg11, s32 arg12, s32 arg13, s64 arg14, s32 arg15, s32 arg16,
                          s32 arg17);
extern s32 func_0024AF50(s32 arg0);
extern s32 func_00101A60(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5);

extern u8 *D_00428F48 __attribute__((section(".data")));
extern u8 *D_3876A4 __attribute__((section(".data")));
extern u8 *D_3876A0 __attribute__((section(".data")));
extern s32 D_003B0C34 __attribute__((section(".data")));
extern u8 D_004294A8[];
extern u8 D_004294B8[];
extern u8 D_00429738[];

#define W(p, o) (*(s32 *)((p) + (o)))
#define T D_00428F48

s32 func_003EB9D0(s32 *arg0) {
    u8 sp[0x320];
    u8 *ent;
    u8 *e;
    u8 *fp;
    s32 i, j, s0, s1, v, sel, ret, t0;

    ret = 0;
    if (W(T, 0x10) == 0) {
        *arg0 = 0;
        return ret;
    }
    switch (W(T, 0x198)) {
    case 0x00:
        ent = (u8 *)W(T, 0x10) + 16 * W(T, 0x19C);
        v = ent[0];
        if (v == 0) {
            W(T, 0x198) = 0x28;
            return 0x28;
        }
        if (v == 5) {
            W(T, 0x1B0) = W(D_3876A4, 0x484);
            W(T, 0x1B4) = W(D_3876A4, 0x484);
        } else if (v >= 4) {
            if (v == 4) {
                W(T, 0x1A8) = W(ent, 8) + 0x63;
                ent = (u8 *)W(T, 0x10) + 16 * W(T, 0x19C);
                if (W(T, 0x1C0) != W(ent, 0xC)) {
                    W(T, 0x194) |= 0x80;
                }
                W(T, 0x1C0) = W((u8 *)W(T, 0x10) + 16 * W(T, 0x19C), 0xC);
            }
        } else if (v >= 2) {
            W(T, 0x1A8) = W(ent, 8) + 1;
        } else if (v == 1) {
            W(T, 0x1A8) = W(ent, 8) + 0x131;
        }
        W(T, 0x198) = 0xA;
        return 0xA;
    case 0x0A:
        W(T, 0x198) = 0xC;
        ent = (u8 *)W(T, 0x10) + 16 * W(T, 0x19C);
        s1 = ent[0] - 1;
        if ((W(T, 0x194) >> s1) & 1) return (s32)ent;
        s0 = s1 * 40;
        func_0026EA88((s32)(T + s0 + 0x28));
        func_0026EAE0((s32)(T + s0 + 0x28), 0x3C);
        if (s1 == 4) func_0026EB78((s32)(T + 0xC8), (s32)D_004294A8);
        W(T, 0x194) |= 1 << s1;
        W(T, 0x198) = 0xB;
        return 0xB;
    case 0x0B:
        ent = (u8 *)W(T, 0x10) + 16 * W(T, 0x19C);
        s1 = ent[0] - 1;
        ret = func_0026EB70((s32)(T + s1 * 40 + 0x28)) & 0x200;
        if (ret) {
            W(T, 0x194) |= 0x100;
            W(T, 0x198) = W(T, 0x198) + 1;
            return W(T, 0x198);
        }
        return ret;
    case 0x0C:
        ent = (u8 *)W(T, 0x10) + 16 * W(T, 0x19C);
        if ((u32)(ent[0] - 2) < 2) {
            func_002493C0(W(T, 0xC), 0x3743, 0x3B5C, 0, W(ent, 8));
        }
        W(T, 0x198) = 0x14;
        return 0x14;
    case 0x14:
        ret = ColorFade_IsFadingOut(arg0);
        if (ret) return ret;
        if (D_003B0C34 & 0x4000) {
            func_00297FE0(0, 1, 0x40, 0x40, 1);
            W(T, 0x198) = 0x1E;
            return 0x1E;
        }
        return 0;
    case 0x1E:
        W(T, 0x198) = 0;
        s0 = 0;
        for (i = 0; i < 5; i++, s0 += 0x28) {
            if (!((W(T, 0x194) >> i) & 1)) continue;
            __builtin_memcpy(sp + 0x50, D_004294B8, 0x280);
            ent = (u8 *)W(T, 0x10) + 16 * W(T, 0x19C);
            e = ent + 0x10;
            if (e[0] == 0 || ent[0] != e[0] || W(ent, 4) != W(e, 4)) {
                func_0026EB78((s32)(T + s0 + 0x28), (s32)(sp + 0x50 + (i << 7)));
                W(T, 0x198) = 0x1F;
            }
        }
        ret = W(T, 0x198);
        if (ret == 0) {
            W(T, 0x19C) = W(T, 0x19C) + 1;
            return W(T, 0x19C);
        }
        return ret;
    case 0x1F:
        s0 = 0;
        W(T, 0x194) &= ~0x100;
        for (i = 0; i < 5; i++, s0 += 0x28) {
            if (func_0026EB70((s32)(T + s0 + 0x28)) & 0x200) W(T, 0x194) &= ~(1 << i);
        }
        v = W(T, 0x194);
        for (i = 0; i < 5; i++) {
            if ((v >> i) & 1) return 1;
        }
        W(T, 0x19C) = W(T, 0x19C) + 1;
        W(T, 0x198) = 0;
        return 0;
    case 0x28:
        s0 = 0;
        for (i = 0; i < 5; i++, s0 += 0x28) {
            if (!((W(T, 0x194) >> i) & 1)) continue;
            __builtin_memcpy(sp + 0x50, D_00429738, 0x280);
            func_0026EB78((s32)(T + s0 + 0x28), (s32)(sp + 0x50 + (i << 7)));
        }
        W(T, 0x198) = W(T, 0x198) + 1;
        return W(T, 0x198);
    case 0x29:
        s0 = 0;
        for (i = 0; i < 5; i++, s0 += 0x28) {
            if (func_0026EB70((s32)(T + s0 + 0x28)) & 0x200) W(T, 0x194) &= ~(1 << i);
        }
        v = W(T, 0x194);
        for (i = 0; i < 5; i++) {
            if ((v >> i) & 1) return 1;
        }
        func_00243A80(0, 0, 0);
        W(T, 0x198) = 0x32;
        return 0x32;
    case 0x32:
        W(D_3876A4, 0x488) = W(D_3876A4, 0x488) + 1;
        *arg0 = W(D_3876A4, 0x488) & 1;
        W(T, 0x198) = W(T, 0x198) + 1;
        return W(T, 0x198);
    case 0x33:
        if (*arg0 == 0) return 0;
        fp = *(u8 **)(D_3876A0 + 0x74);
        func_00101A10();
        *(s64 *)(D_3876A0 + 0x4D8) = 0;
        e = (u8 *)W(T, 0x18) + 24 * W(D_3876A4, 0x484);
        if (W(e, 4) < 0) {
            func_00101AB0(0, 1, 0, 0);
        } else {
            func_00101AB0(0, 2, 0, 0);
        }
        func_00101AB0(1, 1, 1, 0);
        for (i = 0; i < 2; i++) {
            s32 s6 = func_00101A88(i) + 8;
            for (j = 0; j < 2; j++, s6 += 0x58) {
                e = (u8 *)W(T, 0x18) + 24 * W(D_3876A4, 0x484);
                if (i == 0) {
                    if (W(e, 4 * j) < 0) continue;
                } else if (j == 1) {
                    continue;
                }
                sel = (i == 0) ? W(e, 4 * j) : W(e, 8);
                t0 = sel * 9;
                if (sel == 4) t0 = sel * 9 + 2;
                v = W(e, 0x10 + 4 * i);
                func_00101AF8(s6, t0, 0, 2, 0, v != 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, W(fp, 16 * sel), W(fp, 16 * sel),
                              W(fp, 16 * sel + 4));
            }
        }
        e = (u8 *)W(T, 0x18) + 24 * W(D_3876A4, 0x484);
        v = func_0024AF50(W(e, 0xC));
        return func_00101A60(4, 0x1C, 0, 3, 4, v);
    default:
        return ret;
    }
}
