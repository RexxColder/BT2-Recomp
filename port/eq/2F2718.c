#include "common.h"

void func_002F9CE8(u8 *arg0);
void func_002F3378(void);
void func_002F3390(void);
s32 func_002F9998(s32 arg0, s32 arg1, s32 arg2);
void func_002EA0C8(s32 arg0, s32 arg1);
s32 func_002F9DC8(s32 arg0, s32 arg1, s32 arg2);
s32 func_002F9D60(s32 arg0);
s32 func_002FA088(s32 arg0);
s32 func_002F1F10(s32 arg0, s32 arg1);
s32 func_002FA020(s32 arg0);
void func_002F22F0(u8 *obj);
extern u8 D_0037C638[] __attribute__((section(".data")));
extern u8 D_0037C668[] __attribute__((section(".data")));

/* 0x002F2718: per-object stream state machine (bytes at +0x45..+0x49, +0x1, +0x2). */
void func_002F2718(u8 *s0) {
    s32 s1 = 0;
    s32 s2;
    s32 a0;
    s32 v0;
    s32 t;
    s32 v1;

    if (s0[2] != 0) {
        goto L2964;
    }
    if (s0[0x48] == 1) {
        t = s0[0x47];
        s0[0x48] = 0;
        if (t == 0) {
            s0[1] = 1;
        }
    }
    if (s0[0x46] == 1) {
        a0 = *(s32 *)(s0 + 8);
        if (a0 != 0) {
            *(s32 *)(s0 + 8) = 0;
            func_002F9CE8((u8 *)a0);
        }
        func_002F3378();
        s0[0x46] = 0;
        func_002F3390();
        s0[0x49] = 0;
    }

    /* L2794 */
    s1 = 0;
    func_002F3378();
    a0 = s0[0x45];
    if (a0 == 1) {
        if (s0[0x49] == 0) {
            s0[0x49] = (u8)a0;
            s1 = 1;
            func_002F3390();
            if (*(s32 *)(s0 + 8) == 0) {
                v0 = func_002F9998(*(s32 *)(s0 + 0x50), *(s32 *)(s0 + 0x54), 0);
                *(s32 *)(s0 + 8) = v0;
                if (v0 == 0) {
                    func_002EA0C8((s32)D_0037C638, *(s32 *)(s0 + 0x50));
                    s0[1] = 4;
                    s0[0x45] = 0;
                    s0[0x49] = 0;
                    return;
                }
            }
        }
        /* L2814 */
        if (s0[0x49] == 1) {
            if (s1 == 0) {
                func_002F3390();
            }
            v0 = *(s32 *)(s0 + 0x44);
            if ((v0 & 0xFFFF00) == 0x10100) {
                return;
            }
            func_002F9DC8(*(s32 *)(s0 + 8), 0, 2);
            s1 = func_002F9D60(*(s32 *)(s0 + 8));
            s2 = s1 << 11;
            if (*(s32 *)(s0 + 0x54) == 0) {
                s2 = func_002FA088(*(s32 *)(s0 + 0x50));
            }
            func_002F9DC8(*(s32 *)(s0 + 8), 0, 0);
            if (*(s32 *)(s0 + 0x10) == 0x7FFFF800) {
                *(s32 *)(s0 + 0x10) = s2;
                *(s32 *)(s0 + 0x14) = s1;
            }
            /* L28B8 */
            v1 = *(s32 *)(s0 + 0xC);
            if (s1 < v1) {
                *(s32 *)(s0 + 0xC) = s1;
                v1 = s1;
            }
            v0 = *(s32 *)(s0 + 0x14) + v1;
            if (s1 < v0) {
                v0 = s1 - v1;
                v1 = v0 << 11;
                *(s32 *)(s0 + 0x14) = v0;
                *(s32 *)(s0 + 0x10) = v1;
            }
            func_002F1F10((s32)s0, 0);
            s0[0x45] = 0;
            v0 = func_002FA020(*(s32 *)(s0 + 8));
            if (v0 == 3) {
                func_002EA0C8((s32)D_0037C668, *(s32 *)(s0 + 0x50));
                if (*(s32 *)(s0 + 8) != 0) {
                    a0 = *(s32 *)(s0 + 8);
                    *(s32 *)(s0 + 8) = 0;
                    func_002F9CE8((u8 *)a0);
                }
                s0[0x45] = 0;
                s0[1] = 4;
                s0[0x49] = 0;
                return;
            }
        }
    }
    else {
        func_002F3390();
    }

    /* L2954 */
    v0 = s0[0x47];
    if (v0 == 1) {
        s0[0x47] = 0;
    }
    /* L2960 */
    v0 = s0[1];
L2964:
    if (s0[1] != 2) {
        return;
    }
    if (s0[0x49] != 1) {
        return;
    }
    if (s0[0x45] != 0) {
        return;
    }
    func_002F22F0(s0);
}
