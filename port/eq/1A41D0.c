#include "common.h"

void func_001A2660(u8 *a0, u8 *a1, s32 a2, s32 a3, s32 a4, s32 a5);
void func_001A3528(u8 *a0, u8 *a1, s32 a2);
void func_001A3FC0(u8 *a0, u8 *a1, s32 a2, s32 a3);

/* 0x001A41D0: per-frame update of record arg1 (flags at +0x50, floats at +0x5C..+0x68) for the
 * object arg0; the tail call depends on arg0's mode byte (+1): 0 -> func_001A2660, 1 -> func_001A3528.
 * Arity of the tail call is a guess from the pass-through of a3..t1 (the callee's arity per ctx). */
void func_001A41D0(u8 *arg0, u8 *arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    s32 s4;
    s32 a;
    s32 s2;
    f32 *p;
    f32 f0;

    s4 = ((arg0[1] ^ 1) == 0) ? 2 : 1;
    a = *(s32 *)(arg1 + 0x50);

    if ((a & 2) != 0 && *(f32 *)(arg1 + 0x68) <= 0.0f) {
        if (*(s32 *)(arg1 + 0x58) <= 0) {
            a = a | 4;
            *(s32 *)(arg1 + 0x50) = a;
        }
    } else {
        if (*(f32 *)(arg1 + 0x64) < 0.0f) {
            s2 = 0;
            p = (f32 *)(arg1 + 0x5C);
            do {
                f0 = *p;
                if (f0 > 0.0f) {
                    f0 = f0 - 1.0f;
                    *p = f0;
                } else {
                    func_001A3FC0(arg0, arg1, arg2, s2);
                }
                s2 = s2 + 1;
                p = p + 1;
            } while (s2 < s4);
            a = *(s32 *)(arg1 + 0x50);
        } else {
            *(f32 *)(arg1 + 0x64) = *(f32 *)(arg1 + 0x64) - 1.0f;
        }
    }

    if ((a & 2) != 0 && *(f32 *)(arg1 + 0x68) > 0.0f) {
        *(f32 *)(arg1 + 0x68) = *(f32 *)(arg1 + 0x68) - 1.0f;
    }

    if (arg0[1] == 0) {
        func_001A2660(arg0, arg1, arg2, arg3, arg4, arg5);
        return;
    }
    if (arg0[1] == 1) {
        func_001A3528(arg0, arg1, arg2);
        return;
    }
}
