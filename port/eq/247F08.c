#include "common.h"

s32 func_001018B8(void);
void *memset(void *dst, s32 val, u32 n);
extern s32 D_00387970;
extern s32 D_00387974;
extern u8 D_003889E8[] __attribute__((section(".data")));

void func_00247F08(void) {
    u8 *T = D_003889E8;
    u8 *base;
    u8 *p;
    s32 a1;
    s32 limit;
    s32 t1;
    f32 f0;
    f32 f1;

    D_00387970 = 0;
    if (D_00387974 != 0) {
        if (func_001018B8() != 3) {
            return;
        }
        D_00387974 = 0;
    }

    if (T[0] == 0) {
        return;
    }

    limit = (s32)*(u16 *)(T + 0xA) - 1;
    a1 = *(u16 *)(T + 0x8);
    t1 = -1;
    if (a1 < limit) {
        f1 = *(f32 *)(T + 0xC);
        base = *(u8 **)(T + 0x4);
        for (;;) {
            p = base + 4 * a1;
            if ((f32)*(u16 *)(p + 0) <= f1) {
                if (f1 < (f32)*(u16 *)(p + 4)) {
                    t1 = a1;
                    *(u16 *)(T + 0x8) = (u16)t1;
                    break;
                }
            }
            a1 = (u16)(a1 + 1);
            if (!(a1 < limit)) {
                break;
            }
        }
    }

    f1 = *(f32 *)(T + 0xC);
    f0 = *(f32 *)(T + 0x10);
    if (f0 < f1) {
        memset(T, 0, 0x14);
        return;
    }
    if (t1 == -1) {
        memset(T, 0, 0x14);
        return;
    }
    base = *(u8 **)(T + 0x4);
    p = base + 4 * t1;
    if (*(u16 *)(p + 2) != 0) {
        D_00387970 = 1;
    }
    *(f32 *)(T + 0xC) = f1 + 1.0f;
}
