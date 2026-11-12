#include "common.h"

extern u8 *D_0042A590 __attribute__((section(".data")));
extern u8 *D_003876A4 __attribute__((section(".data")));

s32 func_00100FC8(s32 a0);
void func_00100ED0(s32 a0, s32 a1, s32 a2);
void func_002B24C8(s32 a0, s32 a1, s32 a2);
void Res_RelocateOffsets(s32 *a0, s32 a1, s32 a2);

/* state 1 (jtbl index 0): pick two entries from the table at +0x278 by the record at +0x274[g.0x64],
   set the flag bits, and call 100ED0 for each set bit; then 100FC8(1) and state -> 2. */
static s32 st1(void) {
    u8 *A = D_0042A590;
    u8 *g = D_003876A4;
    s32 idx = *(s32 *)(g + 0x64);
    u8 *E = *(u8 **)(A + 0x274) + 56 * idx;
    s32 kind = *(s32 *)(E + 0xC);
    u8 *T = *(u8 **)(A + 0x278);
    s32 i2 = *(s32 *)(A + 0x23C);
    s32 v9[2];
    s32 f;
    s32 i;

    if (kind == 2 || kind == 4) {
        v9[0] = *(s32 *)(T + 80 * idx + 4 * i2);
        v9[1] = *(s32 *)(T + 80 * idx + 4 * i2 + 0x28);
        f = *(s32 *)(A + 0x208) | 0xC;
    } else {
        v9[0] = *(s32 *)(T + 80 * idx + 4 * i2);
        f = *(s32 *)(A + 0x208) | 0x4;
    }
    *(s32 *)(A + 0x208) = f;

    for (i = 0; i < 2; i++) {
        if (*(s32 *)(D_0042A590 + 0x208) & (4 << i)) {
            func_00100ED0(v9[i] + 0x5EE, *(s32 *)(D_0042A590 + 8 + 4 * i), i == 0);
        }
    }

    func_00100FC8(1);
    *(s32 *)(D_0042A590 + 0x228) = 2;
    return 2;
}

/* state 2: wait on 100FC8(0); when it returns nonzero, state -> 3. */
static s32 st2(void) {
    s32 r = func_00100FC8(0);
    if (r == 0) {
        return r;
    }
    *(s32 *)(D_0042A590 + 0x228) = 3;
    return 3;
}

/* state 3: for each active slot (bits 4 and 8 of +0x208), call 2B24C8 and relocate, copy a word
   into the object at +0x14C/+0x140 (+4); then set bit 0x80 and state -> 4. */
static s32 st3(void) {
    u8 *A;
    s32 j;
    s32 off;
    s32 v10[4];
    s32 cur;

    for (j = 0; j < 2; j++) {
        off = (j == 0) ? 0x14C : 0x140;
        if (*(s32 *)(D_0042A590 + 0x208) & (4 << j)) {
            A = D_0042A590;
            func_002B24C8(*(s32 *)(A + 8 + 4 * j), *(s32 *)(A + 0x10 + 4 * j), 0);
            v10[0] = *(s32 *)(A + 0x10 + 4 * j);
            Res_RelocateOffsets(v10, v10[0], v10[0]);
            *(s32 *)(A + off + 4) = *(s32 *)((u8 *)(long)v10[0] + 0x10);
            *(s32 *)(A + 0x208) |= 0x10 << j;
        } else {
            *(s32 *)(D_0042A590 + off + 4) = 0;
        }
    }

    cur = *(s32 *)(D_0042A590 + 0x208) | 0x80;
    *(s32 *)(D_0042A590 + 0x208) = cur;
    *(s32 *)(D_0042A590 + 0x228) = 4;
    return cur;
}

/* state 4: wait for flag 0x40; then state -> 6. */
static s32 st4(void) {
    s32 f = *(s32 *)(D_0042A590 + 0x208) & 0x40;
    if (f == 0) {
        return f;
    }
    *(s32 *)(D_0042A590 + 0x228) = 6;
    return 6;
}

/* state 5 (also reached directly): state -> 6. */
static s32 st5(void) {
    *(s32 *)(D_0042A590 + 0x228) = 6;
    return 6;
}

/* state 6: if flag 0x40 is set, clear it along with 0x4 and 0x8; state -> 1. */
static s32 st6(void) {
    u8 *A = D_0042A590;
    s32 f = *(s32 *)(A + 0x208);

    if (f & 0x40) {
        f ^= 0x40;
        *(s32 *)(A + 0x208) = f;
        f &= -5;
        *(s32 *)(A + 0x208) = f;
        f &= -9;
        *(s32 *)(A + 0x208) = f;
    }
    *(s32 *)(A + 0x228) = 1;
    return 1;
}

/* 0x003FF9C0: state machine on the object at D_0042A590 (state at +0x228, states 1..6). */
s32 func_003FF9C0(void) {
    s32 st = *(s32 *)(D_0042A590 + 0x228);

    if ((u32)(st - 1) >= 6) {
        return 0;
    }
    switch (st) {
    case 1:
        return st1();
    case 2:
        return st2();
    case 3:
        return st3();
    case 4:
        return st4();
    case 5:
        return st5();
    case 6:
        return st6();
    default:
        return 0;
    }
}
