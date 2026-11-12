#include "common.h"

/* byte helpers (no libc) */
static void blob_zero(u8 *d, u32 n) {
    u32 i;
    for (i = 0; i < n; i++) {
        d[i] = 0;
    }
}

static void blob_copy(u8 *d, u8 *s, u32 n) {
    u32 i;
    for (i = 0; i < n; i++) {
        d[i] = s[i];
    }
}

extern u8 *D_00423120 __attribute__((section(".data")));
extern u8 *D_003876A4;
extern u8 *D_00387F2C;

void func_003D5360(u8 *arg0);
void func_003D6798(u8 *arg0);
s32 func_003D6D88(u8 *arg0);
void func_003D7110(u8 *arg0);
void func_003D82C0(u8 *arg0);
void func_003D7910(u8 *arg0);
void func_003D76A8(u8 *arg0);
void func_003D7878(u8 *arg0);
void func_003D73E8(u8 *P);
void func_00248708(u8 *a0, u8 *a1, u8 *a2, u8 *a3);
s32 func_0028BAA8(s32 arg0);
void func_00325370(s64 arg0);
s64 GetTimerSystemTime(void);

/* 0x003CFDD0: menu overlay init. Allocates the 0x3640-byte state block at D_00423120,
   fills its pointers and tables from D_003876A4 (game object) and D_00387F2C. */
void func_003CFDD0(void) {
    u8 *p;
    s32 t;

    D_00423120 = (u8 *)func_0028BAA8(0x3640);
    blob_zero(D_00423120, 0x3640);
    func_00325370((s64)GetTimerSystemTime());

    /* the 0x4C8/0x4CC copies into 0x3638/0x363C of the asm are overwritten just below: omitted */
    p = D_00423120;
    *(u8 **)(p + 0x3638) = D_00387F2C;
    *(u8 **)(p + 0x363C) = D_00387F2C;
    func_003D5360(p);

    p = D_00423120;
    func_00248708(p + 0x2DC, p + 0x2E0, p + 0x2D0, p + 0x2D4);
    p = D_00423120;
    *(u8 **)(p + 0x2D0) = *(u8 **)(p + 0x2DC);
    *(u8 **)(p + 0x2D4) = p + 0x2E0;
    *(u8 **)(p + 0x2D8) = p + 0x1AF0;
    *(s32 *)(p + 0x8) = func_0028BAA8(0x17800);
    p = D_00423120;
    *(s32 *)(p + 0xC) = func_0028BAA8(0x17800);
    p = D_00423120;
    *(s32 *)(p + 0x10) = func_0028BAA8(0x20560);
    p = D_00423120;
    *(s32 *)(p + 0x14) = func_0028BAA8(0x20560);

    /* mode table chosen by D_003876A4->0x90 */
    p = D_00423120;
    t = *(s32 *)(D_003876A4 + 0x90);
    if (t == 1) {
        *(s32 *)(p + 0x3318) = 4;
        *(s32 *)(p + 0x331C) = 16;
        *(s32 *)(p + 0x3328) = -512;
    } else if (t < 2) {
        if (t == 0) {
            *(s32 *)(p + 0x3318) = 3;
            *(s32 *)(p + 0x331C) = 8;
            *(s32 *)(p + 0x3328) = 0;
        }
    } else if (t < 4) {
        *(s32 *)(p + 0x3318) = 5;
        *(s32 *)(p + 0x331C) = 13;
        *(s32 *)(p + 0x3328) = -256;
    }

    p = D_00423120;
    blob_copy(p + 0x333C, D_003876A4 + 0xA0, *(s32 *)(p + 0x331C) * 32);

    if ((*(s32 *)(D_003876A4 + 0x18) & 0x10) == 0) {
        blob_zero(D_003876A4 + 0x2A0, 0xF0);
        func_003D6D88(D_00423120);
        func_003D7110(D_00423120);
        func_003D6798(D_00423120);
    }

    if ((*(s32 *)(D_003876A4 + 0x18) & 0x10) != 0) {
        p = D_00423120;
        *(s32 *)(p + 0x3320) = *(s32 *)(D_003876A4 + 0x98);
        *(s32 *)(p + 0x3324) = *(s32 *)(D_003876A4 + 0x9C);
        blob_copy(p + 0x353C, D_003876A4 + 0x2A0, 0xF0);
        func_003D82C0(D_00423120);
        func_003D7910(D_00423120);
        func_003D76A8(D_00423120);
    }

    /* scan the index table for the first entry whose flags have bit 0 set */
    p = D_00423120;
    for (;;) {
        s32 i = *(s32 *)(p + 0x3324);
        u8 *e = p + 0xE + (i << 4);
        u32 k0 = *(u16 *)(e + 0x3530);
        u32 k1;
        if ((*(u16 *)(p + (k0 << 5) + 0x333C) & 1) != 0) {
            break;
        }
        k1 = *(u16 *)(e + 0x3532);
        if ((*(u16 *)(p + (k1 << 5) + 0x333C) & 1) != 0) {
            break;
        }
        *(s32 *)(p + 0x3324) = i + 1;
    }

    if ((*(s32 *)(D_003876A4 + 0x18) & 0x10) != 0) {
        func_003D7878(D_00423120);
    }
    func_003D73E8(D_00423120);
}
