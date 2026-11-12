#include "common.h"

#define W32(p, off) (*(s32 *)((u8 *)(p) + (off)))
#define U8(p, off) (*(u8 *)((u8 *)(p) + (off)))

extern s32 D_00355390;
extern s32 D_00355394;

void func_002FB878(u8 *obj);
s32 func_002FC550(s32 arg0);
s32 func_002FC730(s32 arg0, s64 arg1, s32 arg2);
s32 func_002FC920(s32 arg0, s32 arg1, s32 arg2);
s32 func_002FC7E8(s32 arg0, s32 arg1, s32 *arg2);

void func_002FBED0(u8 *obj) {
    s32 a0;
    s32 s0;
    s32 spv;

    a0 = U8(obj, 0x2);
    if (W32(obj, 0x4) == 1) {
        s32 idx = (signed char)a0;
        if ((u32)idx >= 10) {
            W32(obj, 0x4) = 0;
        } else {
            /* jtbl_0037DF40: 0,4..8 -> L2FBF48; 1,3,9 -> L2FBF40; 2 -> L2FBF20 */
            switch (idx) {
            case 2:
                func_002FB878(obj);
                U8(obj, 0x2) = 0;
                D_00355394 = D_00355394 + 1;
                /* fall through */
            case 1:
            case 3:
            case 9:
                U8(obj, 0x2) = 0;
                a0 = 0;
                W32(obj, 0x4) = 0;
                break;
            default:
                W32(obj, 0x4) = 0;
                break;
            }
        }
    }

    if ((signed char)a0 == 1) {
        func_002FC550(0x2000);
        s0 = func_002FC730(W32(obj, 0x30), *(s64 *)(obj + 0x28) << 11, 0);
        func_002FC550(0x2001);
        if (s0 < 0) {
            U8(obj, 0x2) = 9;
            W32(obj, 0x34) = s0;
        }

        func_002FC550(0x2100);
        s0 = func_002FC920(W32(obj, 0x30), W32(obj, 0x18), W32(obj, 0x20));
        func_002FC550(0x2101);
        if (s0 < 0) {
            U8(obj, 0x2) = 9;
            W32(obj, 0x34) = s0;
            a0 = 9;
        } else {
            U8(obj, 0x2) = 2;
            D_00355390 = D_00355390 + 1;
            a0 = 2;
        }
    }

    if ((signed char)a0 == 2) {
        func_002FC550(0x2200);
        if (func_002FC7E8(W32(obj, 0x30), 1, &spv) < 0) {
            func_002FC550(0x2201);
            U8(obj, 0x2) = 9;
            W32(obj, 0x34) = -1;
        } else {
            func_002FC550(0x2202);
            if (spv == 0) {
                U8(obj, 0x2) = 3;
                D_00355394 = D_00355394 + 1;
            }
        }
    }
}
