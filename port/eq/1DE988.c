#include "m2c_macros.h"

void *memcpy(void *dst, void *src, u32 n);
extern u8 D_0036F1F0[] __attribute__((section(".data")));
extern u8 D_003B0690[] __attribute__((section(".data")));
extern u8 *D_003876A0;

s32 func_0020B1C0(s32 a0);
s32 func_00207EC0(s32 a0);
void func_003126C8(void *dst, void *src);
void func_00208F18(s32 a0, void *a1, s32 a2);
void sceVu0ApplyMatrix(void *dst, void *m, void *src);
void func_001DE408(u8 *c, void *a1, void *a2, s32 a3);

void func_001DE988(u8 *obj) {
    u8 fr[0x80];
    u8 *c;
    u8 *s4;
    s32 idx;
    s32 n;
    s32 v;
    s32 k;
    s32 *tbl;

    memcpy(fr + 0x60, D_0036F1F0, 0x20);
    c = *(u8 **)(obj + 0x38) + 0x10;
    if (*(s64 *)(D_003876A0 + 0x4D8) & 0x100) {
        return;
    }
    idx = *(s32 *)(c + 0x128C);
    n = *(s32 *)(c + 0x1290);
    if (idx != n) {
        do {
            tbl = (s32 *)(c + 0x1080 + idx * 4);
            v = *tbl;
            if (v > 0) {
                *tbl = v - 20;
                if (v - 20 <= 0) {
                    *tbl = 0;
                    *(s32 *)(c + 0x128C) = idx;
                }
            }
            idx = (idx + 1) & 0x7F;
        } while (idx != n);
    }
    if (func_0020B1C0(*(s32 *)(c + 0x1280)) == 0) {
        *(u8 *)(c + 0x1294) = 0;
        return;
    }
    s4 = D_003B0690;
    for (k = 0; k < 7; k++) {
        v = func_00207EC0(*(s32 *)(c + 0x1280));
        if (*(s32 *)(s4 + 0x34 + k * 64) == v) {
            /* a0 = fr + 0x60 (daddu $a0,$s5,$zero at 0xDEA74, s5 = sp+0x60) */
            func_003126C8(fr + 0x60, s4 + k * 64);
            func_003126C8(fr + 0x70, s4 + k * 64 + 0x10);
        }
    }
    func_00208F18(*(s32 *)(c + 0x1280), fr, 0x40);
    sceVu0ApplyMatrix(fr + 0x40, fr, fr + 0x60);
    sceVu0ApplyMatrix(fr + 0x50, fr, fr + 0x70);
    func_001DE408(c, fr + 0x40, fr + 0x50, *(s32 *)(c + 0x1280));
}
