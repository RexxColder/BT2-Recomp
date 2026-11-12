#include "common.h"

#define W(p, off) (*(s32 *)((p) + (off)))

void BtlMember_AddHealth(u8 *arg0, s32 arg1);
void BtlMember_AddMaxPower(u8 *arg0, s32 arg1);
u8 *BtlMember_GetActiveGauge(u8 *arg0);
void func_00203810(u8 *arg0, s32 arg1);
void func_00203968(u8 *arg0, s32 arg1);
void func_00206958(u8 *arg0, s64 arg1);
void func_002113C0(u8 *arg0, s32 arg1, s32 arg2, s32 arg3);

/* Flag bits of the member block at +0xAF0 (0x400, 0x800, 0x1000, 0x2000, 0x200); each clears 0x3E00 first. */
void func_00214128(u8 *arg0) {
    u8 *p;
    u8 *g;
    s32 f;

    p = (u8 *)W(arg0, 0x1530);

    f = W(p, 0xAF0);
    if (f & 0x400) {
        W(p, 0xAF0) = f & 0xFFFFC1FF;
        func_00206958(arg0, (s64)0x8000 << 27);
        BtlMember_AddHealth(arg0, 0x2710);
    }

    f = W(p, 0xAF0);
    if (f & 0x800) {
        W(p, 0xAF0) = f & 0xFFFFC1FF;
        func_00206958(arg0, (s64)0x8000 << 27);
        func_002113C0(arg0, 0, 0x800, 1);
        BtlMember_AddMaxPower(arg0, 0x7530);
        g = BtlMember_GetActiveGauge(arg0);
        func_00203810(arg0, W(g, 0x10));
    }

    f = W(p, 0xAF0);
    if (f & 0x1000) {
        W(p, 0xAF0) = f & 0xFFFFC1FF;
        func_00206958(arg0, (s64)0x8000 << 27);
        func_002113C0(arg0, 0xD, 0x20, 1);
        g = BtlMember_GetActiveGauge(arg0);
        func_00203810(arg0, W(g, 0x10));
    }

    f = W(p, 0xAF0);
    if (f & 0x2000) {
        W(p, 0xAF0) = f & 0xFFFFC1FF;
        func_00206958(arg0, (s64)0x8000 << 27);
        g = BtlMember_GetActiveGauge(arg0);
        func_00203968(arg0, W(g, 0x18));
    }

    f = W(p, 0xAF0);
    if (f & 0x200) {
        W(p, 0xAF0) = f & 0xFFFFC1FF;
        func_00206958(arg0, (s64)0x8000 << 27);
    }
}
