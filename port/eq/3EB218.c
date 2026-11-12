#include "common.h"

extern u8 *D_00428F48 __attribute__((section(".data")));
extern u8 *D_3876A4 __attribute__((section(".data")));
extern u8 D_00429000[];
extern u8 D_00429018[];
extern u8 D_00429030[];
extern u8 D_00429130[];
extern u8 D_00429230[];
extern u8 D_00429240[];
extern u8 D_00429440[];
extern u8 D_00429458[];
extern u8 D_00429470[];
extern u8 D_00429488[];

void func_00277E70(u8 *arg0, s32 arg1, s64 arg2);
void func_0026EB20(s32 arg0, s32 arg1, s32 arg2);
void func_0026EB30(s32 arg0, s32 arg1);
extern s32 func_0026EBC0();
extern s32 func_0026EFC8();
void func_003EA848(s32 arg0, s32 *arg1, s32 arg2, s32 arg3, u8 *arg4, s32 arg5, u8 *arg6, s32 arg7);
void func_003EA5D8(s32 x, u8 *p, s32 ya, s32 yb, u8 *tbl, s32 idx, s32 flag, u32 color, u32 shadow);
void func_003EA9C0(s32 arg0, s32 *arg1, s32 arg2, s32 arg3, u8 *arg4, s32 arg5, u8 *arg6, s32 arg7);
void func_003EA470(s32 arg0, s32 *arg1, s32 arg2, s32 arg3);
void func_0026EC78(u8 *arg0, s32 *arg1, s32 *arg2, s32 *arg3, s32 *arg4, s32 arg5, s32 arg6, s32 arg7);
extern s32 func_0026EC48();
void func_0026EEF8(u8 *arg0, s32 *arg1, s32 arg2, s32 arg3, f32 farg0);
s32 func_0026EA58(s32 arg0);

#define W(p, o) (*(s32 *)((p) + (o)))
#define P(p, o) (*(u8 **)((p) + (o)))

s32 func_003EB218(void) {
    s32 sp10[4];
    s32 sp20[4];
    u8 buf1[256], buf2[256], buf3[512];
    u8 *O, *s0, *e, *a1;
    s32 i, s2, v, off;
    u32 v1;

    O = D_00428F48;
    func_00277E70(P(O + (W(P(O, 0x18) + W(D_3876A4, 0x484) * 24, 0xC) << 2), 0xF0), 0, 0x80);
    i = 0;
    s2 = 0;
    do {
        O = D_00428F48;
        s0 = O + s2 + 0x28;
        if (i == 3) {
            func_0026EB20((s32)(O + 0xA0), 0, 0);
            O = D_00428F48;
        }
        if (((W(O, 0x194) >> i) & 1) == 0) {
            func_0026EB30((s32)s0, 0);
            i += 1;
            s2 += 0x28;
            continue;
        }
        func_0026EB30((s32)s0, 1);
        v = 0;
        if (i == 4) {
            O = D_00428F48;
            if (W(O, 0x194) & 0x100) {
                func_0026EBC0(O + 0xC8, D_00429000, sp10);
                O = D_00428F48;
                func_003EA848((s32)(O + 0xC8), sp10, 0, 0, P(O, 8), W(O, 0x1B0) + 0x11C, 0, W(O, 0x124));
                O = D_00428F48;
                func_0026EBC0(O + 0xC8, D_00429018, sp10);
                O = D_00428F48;
                func_003EA848((s32)(O + 0xC8), sp10, 0, 0, P(O, 8), W(O, 0x1B4) + 0x107, 0, W(O, 0x124));
            }
        } else {
            if ((u32)(i - 1) < 2) {
                __builtin_memcpy(buf1, D_00429030, 0x100);
                __builtin_memcpy(buf2, D_00429130, 0x100);
                O = D_00428F48;
                a1 = (i == 1) ? buf1 : buf1 + 0x80;
                func_0026EBC0(O + s2 + 0x28, a1, sp10);
                O = D_00428F48;
                e = P(O, 0x10) + (W(O, 0x19C) << 4);
                if (W(e, 0) & 0x100) {
                    func_0026EFC8(O + s2 + 0x28, sp10, 8);
                } else {
                    func_0026EFC8(O + s2 + 0x28, sp10, 4);
                }
                O = D_00428F48;
                a1 = (i == 1) ? buf2 : buf2 + 0x80;
                func_0026EBC0(O + s2 + 0x28, a1, sp10);
                O = D_00428F48;
                e = P(O, 0x10) + (W(O, 0x19C) << 4);
                if (W(e, 0) & 0x100) {
                    func_0026EFC8(O + s2 + 0x28, sp10, 4);
                } else {
                    func_0026EFC8(O + s2 + 0x28, sp10, 8);
                }
                O = D_00428F48;
                e = P(O, 0x10) + (W(O, 0x19C) << 4);
                v1 = W(e, 0);
                if ((u32)((v1 & 0xFF) - 2) < 2) {
                    s32 a0 = W(e, 4);
                    if (a0 < 5) {
                        off = (v1 & 0x100) ? (a0 << 7) : (a0 << 7) + 0x40;
                        W(O, 0x140) = W(P(O, 0x10C), 0x10) + off;
                        O = D_00428F48;
                        e = P(O, 0x10) + (W(O, 0x19C) << 4);
                        off = (W(e, 0) & 0x100) ? (W(e, 4) << 7) : (W(e, 4) << 7) + 0x40;
                        W(O, 0x158) = W(P(O, 0x10C), 0x10) + off;
                    }
                }
            }
            sp20[1] = 0x20;
            sp20[2] = 0x20;
            sp20[0] = 0;
            sp20[3] = 0x40;
            func_0026EBC0(s0, D_00429230, sp10);
            O = D_00428F48;
            func_0026EC78(s0, sp10, (s32 *)(O + 0x1A0), (s32 *)(O + 0x1A4), sp20, 2, 1, 8);
            __builtin_memcpy(buf3, D_00429240, 0x200);
            O = D_00428F48;
            func_0026EBC0(O + s2 + 0x28, buf3 + (i << 7), sp10);
            O = D_00428F48;
            if (i != 3) {
                func_003EA5D8((s32)(O + s2 + 0x28), (u8 *)sp10, 0, 0, P(O, 8), W(O, 0x1A8) - 1, 0, 0x80, 0x40404040);
                v = i - 3;
            } else if (!(W(O, 0x194) & 0x100)) {
                v = i - 3;
            } else {
                func_003EA9C0((s32)(O + 0xA0), sp10, 0, 0, P(O, 8), W(O, 0x1A8), 1, W(O, 0x124));
                v = 0;
            }
            goto after;
        }
        v = i - 3;
after:
        if ((u32)v < 2) {
            O = D_00428F48;
            func_0026EBC0(O + s2 + 0x28, D_00429440, sp10);
            O = D_00428F48;
            func_003EA470((s32)(O + s2 + 0x28), sp10, W(D_3876A4, 0x484) + 0x139, 1);
            sp20[1] = 0x20;
            O = D_00428F48;
            sp20[2] = 0x100;
            sp20[0] = 0;
            sp20[3] = 0x40;
            func_0026EBC0(O + s2 + 0x28, D_00429458, sp10);
            O = D_00428F48;
            func_0026EC48(O + s2 + 0x28, sp10, sp20);
            O = D_00428F48;
            sp20[2] = 0x200;
            sp20[3] = 0x80;
            sp20[0] = 0;
            sp20[1] = 0x40;
            func_0026EBC0(O + s2 + 0x28, D_00429470, sp10);
            O = D_00428F48;
            func_0026EC48(O + s2 + 0x28, sp10, sp20);
        }
        if (i != 3) {
            i += 1;
        } else {
            O = D_00428F48;
            func_0026EBC0(O + 0xA0, D_00429488, sp10);
            O = D_00428F48;
            func_0026EEF8(O + 0xA0, sp10, 0, 0, *(f32 *)(O + 0x1BC));
            i += 1;
        }
        s2 += 0x28;
    } while (i < 5);

    {
        s32 s0o = 0, k = 4, r;
        do {
            k -= 1;
            O = D_00428F48;
            r = func_0026EA58((s32)(O + s0o + 0x28));
            s0o += 0x28;
        } while (k >= 0);
        return r;
    }
}
