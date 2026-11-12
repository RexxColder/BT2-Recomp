#include "common.h"

extern u8 *D_0042BB78 __attribute__((section(".data")));

void func_100ED0(s32 arg0, u8 *arg1, s32 arg2);
s32 func_100FC8(s32 arg0);
u8 *func_2B24C8(u8 *arg0, u8 *arg1, s32 arg2);
void Res_RelocateOffsets(s32 arg0, s32 arg1, s32 arg2);

#define GW(off) (*(s32 *)(D_0042BB78 + (off)))
#define GP(off) (*(u8 **)(D_0042BB78 + (off)))

/* 0x0040AC30: state machine on G->0x37C4 (G = D_0042BB78), states 1..6 via jtbl_0042DF80, others return.
 * k = G->0x23C (bit index), flags = G->0x240. Each case ends by writing the next state to G->0x37C4. */
void func_0040AC30(void) {
    s32 st;
    s32 k;
    s32 fl;
    s32 v;
    s32 a;
    s32 idx;
    s32 t;
    s32 sp[4];
    u8 *a3p;
    s32 a1v;
    s32 a2v;

    st = GW(0x37C4);
    switch (st) {
    case 1:
        k = GW(0x23C);
        fl = GW(0x240);
        if (fl & (0x400 << k)) {
            idx = GW(0x2DC + 4 * k) + 5 * k;
            v = GW(0x2E0 + 4 * idx);
        } else {
            a = k;
            a3p = GP(0x360 + 4 * a);
            idx = GW(0x2DC + 4 * a) + 5 * a;
            a1v = GW(0x26C + 4 * idx);
            a2v = GW(0x244 + 4 * idx);
            v = *(s32 *)(a3p + 44 * (7 * a1v + a2v));
        }
        func_100ED0(v + 0x56B, GP(0x8 + 4 * GW(0x23C)), 1);
        func_100FC8(1);
        *(s32 *)(D_0042BB78 + 0x37C4) = 2;
        break;

    case 2:
        if (func_100FC8(0) != 0) {
            *(s32 *)(D_0042BB78 + 0x37C4) = 3;
        }
        break;

    case 3:
        k = GW(0x23C);
        func_2B24C8(GP(0x8 + 4 * k), GP(0x10 + 4 * k), 0);
        k = GW(0x23C);
        sp[0] = *(s32 *)(D_0042BB78 + 0x10 + 4 * k);
        Res_RelocateOffsets((s32)sp, sp[0], sp[0]);
        if (GW(0x23C) != 0) {
            *(s32 *)(D_0042BB78 + 0x128) = *(s32 *)((u8 *)sp[0] + 0x10);
        } else {
            *(s32 *)(D_0042BB78 + 0x124) = *(s32 *)((u8 *)sp[0] + 0x10);
        }
        fl = GW(0x240);
        fl |= 0x40 << GW(0x23C);
        *(s32 *)(D_0042BB78 + 0x240) = fl;
        t = GW(0x23C) ^ 1;
        if ((GW(0x240) >> t) & 1) {
            *(s32 *)(D_0042BB78 + 0x23C) = t;
            *(s32 *)(D_0042BB78 + 0x37C4) = 6;
        } else {
            *(s32 *)(D_0042BB78 + 0x37C4) = 4;
        }
        break;

    case 4:
        fl = GW(0x240);
        if (fl & 1) {
            *(s32 *)(D_0042BB78 + 0x23C) = 0;
            *(s32 *)(D_0042BB78 + 0x37C4) = 6;
        } else if (fl & 2) {
            *(s32 *)(D_0042BB78 + 0x23C) = 1;
            *(s32 *)(D_0042BB78 + 0x37C4) = 6;
        }
        break;

    case 5:
        t = GW(0x23C) ^ 1;
        if ((GW(0x240) >> t) & 1) {
            *(s32 *)(D_0042BB78 + 0x23C) = t;
        }
        *(s32 *)(D_0042BB78 + 0x37C4) = 6;
        break;

    case 6:
        k = GW(0x23C);
        fl = GW(0x240);
        if ((fl >> k) & 1) {
            *(s32 *)(D_0042BB78 + 0x240) = fl ^ (1 << k);
        }
        *(s32 *)(D_0042BB78 + 0x37C4) = 1;
        break;

    default:
        break;
    }
}
