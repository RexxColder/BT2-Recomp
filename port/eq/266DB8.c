#include "common.h"

extern u8 D_00344750[], D_00344770[], D_003447B0[], D_003447D8[];

s32 func_00266938(u8 *a0);
void func_002673C0(u8 *a0);
void func_00266950(u8 *a0, u8 *a1);
s32 rand(void);

#define F(p, o) (*(f32 *)((p) + (o)))
#define W(p, o) (*(s32 *)((p) + (o)))
#define U(p, o) ((f32)*(u32 *)((p) + (o)))

void func_00266DB8(u8 *a0, u8 *a1) {
    u8 *s0 = a1;
    u8 *s1 = a0;
    s32 st = W(s0, 0x10);
    s32 v, i, cnt;
    u8 *a2, *rec;
    f32 f1, f2, f3, t;
    s16 *sp_;

    if ((u32)st >= 0x13) return;
    switch (st) {
    case 0:
        func_002673C0(s1);
        return;
    case 1:
        if (!func_00266938(s1)) return;
        a2 = *(u8 **)(s0 + 0x2C);
        F(s0, 0x1C) = F(s0, 0x1C) + F(s0, 0x20);
        if (U(a2, 0x3C) <= F(s0, 0x1C)) F(s0, 0x1C) = U(a2, 0x3C);
        break;
    case 2:
        W(s0, 0x40) = 0;
        return;
    case 3:
        F(s0, 0x1C) = F(s0, 0x1C) + F(s0, 0x20);
        if (func_00266938(s1)) goto timed;
        if (F(s0, 0x18) <= F(s0, 0x1C)) {
            if (rand() & 1) { v = 7; *(u8 **)(s0 + 0x28) = D_00344750; }
            else { v = 5; *(u8 **)(s0 + 0x28) = D_00344770; }
            goto pick;
        }
        break;
    case 5:
        F(s0, 0x1C) = F(s0, 0x1C) + F(s0, 0x20);
        if (func_00266938(s1)) {
        timed:
            if (U(*(u8 **)(s0 + 0x2C), 0x3C) <= F(s0, 0x1C)) {
                W(s0, 0x1C) = 0;
                W(s0, 0x14) = 0;
                func_00266950(s1, s0);
            }
        } else if (F(s0, 0x18) <= F(s0, 0x1C)) {
            v = 10;
            if (rand() & 1) *(u8 **)(s0 + 0x28) = D_003447B0;
            else *(u8 **)(s0 + 0x28) = D_003447D8;
        pick:
            W(s0, 0x24) = v;
            W(s0, 0x1C) = 0;
            W(s0, 0x14) = *(s16 *)(*(u8 **)(s0 + 0x28) + 2);
        }
        break;
    case 6:
        F(s0, 0x1C) = F(s0, 0x1C) + F(s0, 0x20);
        if (func_00266938(s1) != 1) {
            if (F(s0, 0x18) <= F(s0, 0x1C)) func_002673C0(s1);
        } else {
            if (U(*(u8 **)(s0 + 0x2C), 0x3C) <= F(s0, 0x1C)) func_002673C0(s1);
        }
        break;
    case 7:
        break;
    default:
        return;
    }
    if (func_00266938(s1)) {
        cnt = W(s0, 0x24);
        if (!(1 < cnt)) {
            W(s0, 0x14) = 0;
            return;
        }
        a2 = *(u8 **)(s0 + 0x2C);
        f1 = F(s0, 0x1C);
        for (i = 1; i < cnt; i++) {
            u8 *a0p = a2 + 0x10 * i;
            if (U(a0p, -4) == f1) {
                rec = a2 + 0x10 * i - 0x10;
                goto copy;
            }
            if (U(a0p, -4) < f1 && f1 < U(a0p, 0xC)) {
                f3 = f1 - U(a0p, -4);
                f2 = U(a0p, 0xC) - U(a0p, -4);
                f2 = f3 / f2;
                F(s0, 0x50) = (F(a0p, 0) - F(a0p, -0x10)) * f2 + F(a0p, -0x10);
                F(s0, 0x54) = (F(a0p, 4) - F(a0p, -0xC)) * f2 + F(a0p, -0xC);
                F(s0, 0x5C) = 1.0f;
                F(s0, 0x58) = (F(a0p, 8) - F(a0p, -8)) * f2 + F(a0p, -8);
                W(s0, 0x14) = 0;
                return;
            }
            if (U(a0p, 0xC) == f1) {
                rec = a2 + 0x10 * i;
                goto copy;
            }
        }
        W(s0, 0x14) = 0;
        return;
    copy:
        F(s0, 0x50) = F(rec, 0);
        F(s0, 0x54) = F(rec, 4);
        F(s0, 0x5C) = 1.0f;
        F(s0, 0x58) = F(rec, 8);
        W(s0, 0x14) = 0;
        return;
    }
    cnt = W(s0, 0x24);
    if (!(1 < cnt)) return;
    f2 = F(s0, 0x1C);
    sp_ = *(s16 **)(s0 + 0x28);
    for (i = 1; i < cnt; i++, sp_ += 2) {
        f1 = (f32)sp_[0];
        if (f1 == f2) { W(s0, 0x14) = sp_[1]; return; }
        if (f1 <= f2 && f2 <= (f32)sp_[2]) { W(s0, 0x14) = sp_[1]; return; }
    }
}
