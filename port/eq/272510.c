#include "common.h"

void StgAabb_SetEmpty(void *arg0);
void func_00312650(void *arg0, void *arg1, void *arg2);
void func_0029DEB8(void *arg0, void *arg1, void *arg2);
void sceVu0CopyMatrix(void *arg0, void *arg1);
void func_003126C8(void *arg0, void *arg1);
void func_002720D8(f32 farg0, f32 farg1, f32 farg2, void *arg0);
void func_00272180(void *arg0, void *arg1);
void ColBox_AddPointKeepW(void *arg0, void *arg1);
s32 func_00272268(void *arg0);

/* asm: tail value of func_00272268 (cull test) is returned; 2729D0 tests it (was void) */
s32 func_00272510(u8 *arg0, u8 *arg1) {
    f32 fb[0x100];
    u8 *s1 = arg1;
    u8 *s2 = arg0;
    u8 *s0;
    f32 *pA, *a1p;
    s32 s4 = 0;
    s32 s3, v;

    StgAabb_SetEmpty(fb);
    for (;;) {
        if (*(s32 *)(s1 + 0xC) == s4) {
            s0 = s2 + 0x90;
            fb[8] = *(f32 *)(s1 + 0x00);
            fb[9] = *(f32 *)(s1 + 0x04);
            fb[10] = *(f32 *)(s1 + 0x08);
            fb[11] = 1.0f;
            func_00312650(fb + 12, fb + 8, s2 + 0xD0);
            func_0029DEB8(fb + 16, s0, fb + 12);
            sceVu0CopyMatrix(fb + 20, s0);
            func_003126C8(fb + 32, fb + 16);
            func_002720D8(*(f32 *)(s1 + 0x10), *(f32 *)(s1 + 0x14), *(f32 *)(s1 + 0x18), fb + 36);
            func_00272180(fb + 36, fb + 20);
            pA = fb + 104;
            a1p = pA;
            s3 = 7;
            do {
                pA += 4;
                s3 -= 1;
                ColBox_AddPointKeepW(fb, a1p);
                a1p = pA;
            } while (s3 >= 0);
            v = *(s32 *)(s1 + 0x2C);
            s1 += 0x30;
            if (v != 0) {
                break;
            }
        }
        if (*(s32 *)(s2 + 0x8) != 0) {
            break;
        }
        s4 += 1;
        s2 += *(s32 *)s2;
    }
    return func_00272268(fb);
}
