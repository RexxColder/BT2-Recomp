#include "common.h"

extern u8 *D_0042BB74 __attribute__((section(".data")));
extern u8 *D_003876A4 __attribute__((section(".data")));
extern s32 D_003876AC __attribute__((section(".data")));

s32 func_00100D58(s32 arg0, s32 arg1, s32 arg2);
s32 func_00243A80(s32 a0, s32 a1, s32 a2);
void func_00243968(s32 a0, s32 a1, s32 a2);
void func_0028BB60(s32 arg0);
void func_0029BD28(void);
s32 func_00250978(s32 arg0);
void func_002539C8(s32 arg0);
s32 func_0029BB88(u8 *a0, s32 a1);

/* 0x00409338: sub-state enter/leave on the object at D_0042BB74 (flags word +0x210, record pair at
   +0x210/+0x214 picked by the g.0x48C bit 1), with the 0x37/0x38 step loop on D_003876A4 (+0x1C). */
s32 func_00409338(void) {
    u8 *A;
    u8 *g;
    u8 *M;
    s32 flags;
    s32 result;
    s32 saved;
    s32 cont;
    s32 state;
    s32 off;
    s32 a1;

    A = D_0042BB74;
    flags = *(s32 *)(A + 0x210);

    if (!(flags & 0x10000)) {
        *(s32 *)(A + 0x210) = flags | 0x10000;
        func_00100D58(*(s32 *)(D_003876A4 + 4) + 14, 0, 1);
        return func_00243A80(0, 0, 0);
    }

    result = flags & 0x20000;
    if (result != 0) {
        return result;
    }

    result = func_00100D58(0, 0, 0);
    D_003876AC = result;
    if (result == 0) {
        return result;
    }

    A = D_0042BB74;
    *(s32 *)(A + 0x210) = *(s32 *)(A + 0x210) | 0x20000;
    flags = *(s32 *)(A + 0x210);

    if (flags & 0x4000) {
        if (*(s32 *)(A + 0x36C4) == 2) {
            *(s32 *)(D_003876A4 + 0x48C) |= 0x20;
        }
    } else if (flags & 0x8000) {
        g = D_003876A4;
        if (*(s32 *)(A + 0x36C4) == 1) {
            *(s32 *)(g + 0x48C) |= 1;
        } else {
            *(s32 *)(g + 0x48C) |= 0x20;
        }
        *(s32 *)(g + 0x48C) |= 2;
    }

    off = (*(s32 *)(D_003876A4 + 0x48C) & 2) ? 0x214 : 0x210;
    g = D_003876A4;
    *(s32 *)(g + 0x494) = *(s32 *)(A + off + 4) + 7 * *(s32 *)(A + off + 0xC);

    saved = *(s32 *)(g + 0x1C);
    *(s32 *)(g + 0x1C) = 0x37;
    func_0029BD28();

    cont = 1;
    while (cont) {
        g = D_003876A4;
        state = *(s32 *)(g + 0x1C);
        if (state == 0x37) {
            if (func_00250978(1) != 0) {
                *(s32 *)(D_003876A4 + 0x1C) = 0x38;
            } else {
                cont = 0;
            }
        } else if (state == 0x38) {
            func_002539C8(2);
            *(s32 *)(D_003876A4 + 0x1C) = 0x37;
        }
    }

    *(s32 *)(D_003876A4 + 0x1C) = saved;

    A = D_0042BB74;
    flags = *(s32 *)(A + 0x210);
    if (flags & 0x4000) {
        *(s32 *)(A + 0x210) = flags ^ 0x4000;
    } else if (flags & 0x8000) {
        *(s32 *)(A + 0x210) = flags ^ 0x8000;
    }

    A = D_0042BB74;
    *(s32 *)(A + 0x210) &= 0xFFFEFFFF;
    *(s32 *)(A + 0x210) &= 0xFFFDFFFF;
    *(s32 *)(D_003876A4 + 0x48C) &= -2;
    *(s32 *)(D_003876A4 + 0x48C) &= -3;
    *(s32 *)(D_003876A4 + 0x48C) &= -0x21;

    func_00243968(0, 0, 0);
    func_0028BB60(D_003876AC);
    D_003876AC = 0;

    A = D_0042BB74;
    M = *(u8 **)(A + 4);
    a1 = *(s32 *)(A + 0x24);
    return func_0029BB88(M + ((*(u32 *)(M + 0x6C) >> 2) << 2), a1);
}
