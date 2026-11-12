#include "common.h"

#define W(p, o) (*(s32 *)((u8 *)(p) + (o)))
#define FL(p, o) (*(f32 *)((u8 *)(p) + (o)))
#define B8(p, o) (*(u8 *)((u8 *)(p) + (o)))
#define H16(p, o) (*(u16 *)((u8 *)(p) + (o)))

extern f32 D_00384E84;
extern u8 *D_00387830;

void *memset(void *arg0, s32 arg1, s32 arg2);
f32 BtlCharApi_GetHeight(s32 arg0);
void func_00129C28();
void func_001A5A48(void *arg0);
void SpuBlock_Clear(void *arg0);
void bt2_fightlog_note(const char *fmt, ...);

void func_001A55E0(u8 *arg0, u8 *arg1) {
    u8 *s0;
    u8 *t1;
    u8 *t2;
    u8 *t3;
    u8 *a1p;
    f32 f2;
    s32 a2;
    s32 idx;

    s0 = *(u8 **)(arg0 + 0x38);
    memset(s0, 0, 0x90);
    f2 = BtlCharApi_GetHeight(W(arg1, 0x20)) / D_00384E84;
    t1 = D_00387830;
    a2 = W(arg1, 0x2C);
    t3 = t1 + 0x340;
    t2 = *(u8 **)(t1 + 0x740);

    if (a2 == 0) {
        idx = W(arg1, 0x28);
        a1p = t2 + 0xC;
        W(s0, 0x20) = (s32)t3;
        W(s0, 0x1C) = W(t1, idx * 4 + 0x54C);
        W(s0, 0xC) = (s32)(t1 + 0x598);
        FL(s0, 0x74) = FL(a1p, idx * 4 + 0x170) * f2 * FL(t1, 0x748);
        W(s0, 0x14) = W(t3, idx * 4 + 0x3B0);
        W(s0, 0x10) = W(t1, idx * 4 + 0x6A4);
        FL(s0, 0x50) = FL(a1p, idx * 12 + 0x40) * f2 * FL(t1, 0x748);
        FL(s0, 0x54) = FL(a1p, idx * 12 + 0x44) * f2 * FL(t1, 0x748);
        FL(s0, 0x58) = FL(a1p, idx * 12 + 0x48) * f2 * FL(t1, 0x748);
        B8(s0, 0x6F) = B8(t2, idx * 3);
        B8(s0, 0x70) = B8(t2, idx * 3 + 1);
        B8(s0, 0x71) = B8(t2, idx * 3 + 2);
        B8(s0, 0x6C) = B8(t2 + 4, idx * 3 + 0x300);
        B8(s0, 0x6D) = B8(t2 + 4, idx * 3 + 0x301);
        B8(s0, 0x6E) = B8(t2 + 4, idx * 3 + 0x302);
        FL(s0, 0x5C) = FL(t2, idx * 12 + 0x1D0);
        FL(s0, 0x60) = FL(t2, idx * 12 + 0x1D4);
        W(s0, 0x68) = 3;
        FL(s0, 0x64) = FL(t2, idx * 12 + 0x1D8);
        if (idx == 0x10) {
            H16(s0, 0x88) = (u16)(H16(s0, 0x88) | 0x10);
        }
    } else if (a2 == 1) {
        W(s0, 0x1C) = 0;
        W(s0, 0x20) = 0;
        W(s0, 0xC) = (s32)(t1 + 8);
        FL(s0, 0x74) = FL(t2, 0x1CC) * f2;
        W(s0, 0x14) = W(t1, 0) + W(arg1, 0x24) * 0x50;
        W(s0, 0x10) = W(t1, 4);
        FL(s0, 0x50) = FL(t2, 0x1C8) * f2;
        B8(s0, 0x6F) = 0;
        B8(s0, 0x6C) = B8(t2, 0x350);
        W(s0, 0x68) = a2;
        FL(s0, 0x5C) = FL(t2, 0x2B4);
        H16(s0, 0x88) = (u16)(H16(s0, 0x88) | 8);
    }

    W(s0, 0x78) = W(arg1, 0x28);
    W(s0, 0x84) = W(arg1, 0x24);
    W(s0, 0x80) = W(arg1, 0x20);
    H16(s0, 0x88) = (u16)(H16(s0, 0x88) | 1);
    W(s0, 0x7C) = W(arg1, 0x2C);
    func_00129C28(s0 + 0x30, arg1, W(arg1, 0x2C));
    func_00129C28(s0 + 0x40, arg1 + 0x10);
    func_001A5A48(s0);
    { static int n; if (n++ < 30) bt2_fightlog_note("CHISPA-INIT tipo %d modo %d alto %g esc74 %g esc50 %g tex14 %x tex10 %x col %02x%02x%02x", /* TEMP */
        W(arg1, 0x28), a2, f2, FL(s0, 0x74), FL(s0, 0x50), W(s0, 0x14), W(s0, 0x10), B8(s0, 0x6F), B8(s0, 0x70), B8(s0, 0x71)); }
    SpuBlock_Clear(s0);
}
