#include "common.h"

void func_002D64D8(s32 arg0, s32 arg1, s32 arg2);
void func_002D6C90(s32 arg0, s32 arg1, s32 arg2);
s32 func_002D6CE0(void);
extern u8 D_0037AB70[] __attribute__((section(".data")));

void func_002D6668(void *arg0, u32 *arg1, void *arg2) {
    s32 F[64];
    u8 *a;
    u8 *o;
    s32 t0;
    s32 prod;
    s32 t2v;
    s32 bitv;
    s32 a0v;
    void (*fp)(s32, s32, s32);

    a = (u8 *)arg0;
    o = (u8 *)arg2;
    func_002D64D8((s32)arg0, (s32)arg1, (s32)F);
    if (*arg1 != 0 && *arg1 < 3U) {
        t0 = *(s32 *)(a + 8);
        F[30] = *(s32 *)(o + 8);
        F[29] = *(s32 *)(o + 4);
        F[31] = *(s32 *)(o + 0xC);
        if (t0 == 0) {
            goto block_8;
        }
        F[32] = t0;
    } else if (*arg1 == 3) {
        prod = (s32)((u32)F[4] * (u32)F[3]);
        t0 = *(s32 *)(a + 8);
        F[30] = *(s32 *)(o + 8);
        F[31] = *(s32 *)(o + 0xC);
        t2v = prod + (s32)(((u32)prod) >> 31);
        a0v = t2v >> 1;
        bitv = (s32)(((u32)t2v) >> 31);
        F[1] += a0v;
        a0v = a0v + bitv;
        a0v = a0v >> 1;
        F[5] += a0v;
        F[9] += a0v;
        F[29] = *(s32 *)(o + 4);
        if (t0 != 0) {
            F[32] = t0;
        } else {
block_8:
            F[32] = F[2] * 4;
        }
    } else {
        func_002D6C90((s32)arg0, (s32)arg1, (s32)D_0037AB70);
    }
    if (func_002D6CE0() != 1) {
        F[56] = 0;
    } else {
        F[56] = *(s32 *)(a + 0x38);
    }
    fp = (void (*)(s32, s32, s32))(*(s32 *)(a + 0x6C));
    if (fp != 0) {
        fp((s32)F, (s32)(F + 28), (s32)(F + 56));
    }
}
