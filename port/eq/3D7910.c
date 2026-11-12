#include "common.h"

extern u8 *D_003876A0;

s32 func_003D6D18(u8 *a0, u8 *a1, s32 a2);

#define REC(i) (arg0 + 0x3330 + ((i) << 5))
#define IDX1() (*(u16 *)(s1 + *(s32 *)(arg0 + 0x3324) * 0x10 + 0x3530))
#define IDX2() (*(u16 *)(s1 + *(s32 *)(arg0 + 0x3324) * 0x10 + 0x3532))

/* 0x003D7910: state step on the slot pair given by G->0x3324 (table at G + 0xE + 16 * slot, entries u16 idx1 at +0x3530 and
 * idx2 at +0x3532 indexing 32-byte records at G + 0x3330). S = D_003876A0 + 0x480, flags F = *(s32 *)S.
 * F & 1: if record idx1 has bit 0 of its flag (+0xC): record idx2 |= 2, G->0x2C8 = 0, f0 = S->0x30, store f0 at
 * record idx1 +0x28 and toggle record idx2; else record idx1 |= 2, G->0x2C8 = 1, f0 = S->0x30, store at record idx2
 * +0x28 and toggle record idx1. F & 2 (not F & 1): the same with S->0x34 and the roles of idx1/idx2 swapped in the
 * flag-set case. func_003D6D18(G, record idx1, slot*16) sets G->0x2BC bit 0x4000 when it returns nonzero. Then, for
 * both records, flag &= ~8; and G[16 * slot + 0x353C] |= 1. */
void func_003D7910(u8 *arg0) {
    u8 *s;
    u8 *s1;
    s32 flags;
    s32 a2;
    f32 f0;
    s32 tog;

    s = D_003876A0 + 0x480;
    flags = *(s32 *)s;
    s1 = arg0 + 0xE;

    if (flags & 1) {
        a2 = *(s32 *)(arg0 + 0x3324) * 0x10;
        if (*(u16 *)(REC(IDX1()) + 0xC) & 1) {
            *(u16 *)(REC(IDX2()) + 0xC) = (u16)(*(u16 *)(REC(IDX2()) + 0xC) | 2);
            *(s32 *)(arg0 + 0x2C8) = 0;
            *(s32 *)(arg0 + 0x2BC) |= 0x10;
            if (func_003D6D18(arg0, REC(IDX1()), a2) != 0) {
                *(s32 *)(arg0 + 0x2BC) |= 0x4000;
            }
            f0 = *(f32 *)(s + 0x30);
            *(f32 *)(REC(IDX1()) + 0x28) = f0;
            tog = IDX2();
        } else {
            *(u16 *)(REC(IDX1()) + 0xC) = (u16)(*(u16 *)(REC(IDX1()) + 0xC) | 2);
            *(s32 *)(arg0 + 0x2C8) = 1;
            *(s32 *)(arg0 + 0x2BC) |= 0x10;
            if (func_003D6D18(arg0, REC(IDX1()), a2) != 0) {
                *(s32 *)(arg0 + 0x2BC) |= 0x4000;
            }
            f0 = *(f32 *)(s + 0x30);
            *(f32 *)(REC(IDX2()) + 0x28) = f0;
            tog = IDX1();
        }
        *(u16 *)(REC(tog) + 0xC) = (u16)(*(u16 *)(REC(tog) + 0xC) ^ 2);
    } else if (flags & 2) {
        a2 = *(s32 *)(arg0 + 0x3324) * 0x10;
        if (*(u16 *)(REC(IDX1()) + 0xC) & 1) {
            *(u16 *)(REC(IDX1()) + 0xC) = (u16)(*(u16 *)(REC(IDX1()) + 0xC) | 2);
            *(s32 *)(arg0 + 0x2C8) = 1;
            *(s32 *)(arg0 + 0x2BC) |= 0x10;
            if (func_003D6D18(arg0, REC(IDX1()), a2) != 0) {
                *(s32 *)(arg0 + 0x2BC) |= 0x4000;
            }
            f0 = *(f32 *)(s + 0x34);
            *(f32 *)(REC(IDX2()) + 0x28) = f0;
            tog = IDX1();
        } else {
            *(u16 *)(REC(IDX2()) + 0xC) = (u16)(*(u16 *)(REC(IDX2()) + 0xC) | 2);
            *(s32 *)(arg0 + 0x2C8) = 0;
            *(s32 *)(arg0 + 0x2BC) |= 0x10;
            if (func_003D6D18(arg0, REC(IDX1()), a2) != 0) {
                *(s32 *)(arg0 + 0x2BC) |= 0x4000;
            }
            f0 = *(f32 *)(s + 0x34);
            *(f32 *)(REC(IDX1()) + 0x28) = f0;
            tog = IDX2();
        }
        *(u16 *)(REC(tog) + 0xC) = (u16)(*(u16 *)(REC(tog) + 0xC) ^ 2);
    }

    *(u16 *)(REC(IDX1()) + 0xC) = (u16)(*(u16 *)(REC(IDX1()) + 0xC) & 0xFFF7);
    *(u16 *)(REC(IDX2()) + 0xC) = (u16)(*(u16 *)(REC(IDX2()) + 0xC) & 0xFFF7);
    *(u16 *)(arg0 + *(s32 *)(arg0 + 0x3324) * 0x10 + 0x353C) |= 1;
}
