#include "common.h"

void *memcpy(void *dst, const void *src, u32 n);
extern u8 D_003B2654[] __attribute__((section(".data")));
extern u8 D_00344A40[] __attribute__((section(".data")));
extern f32 D_00386FC8;

/* 0x00272CC8: picks a pair of 16-byte vectors from D_00344A40 (32 bytes per entry) by a mode/index pair in
 * D_003B2654 (+0x3C mode, +0x4C index; the switch tables are jtbl_003769B0 for mode 0 and jtbl_00376A20 for
 * mode 1, both giving 0..4 as the entry number). arg0 gets the first vector, arg1 the second, scaled by
 * D_00386FC8 / 180 per component. */
void func_00272CC8(void *arg0, void *arg1) {
    f32 *s2;
    u8 *base;
    s32 mode;
    s32 idx;
    s32 s1;

    s1 = 0;
    s2 = (f32 *)arg1;
    base = D_00344A40;

    mode = *(s32 *)(D_003B2654 + 0x3C);
    if (mode == 0) {
        idx = *(s32 *)(D_003B2654 + 0x4C);
        if ((u32)idx < 0x1A) {
            switch (idx) {
            case 5:
            case 6:
            case 7:
            case 8:
            case 19:
            case 20:
                s1 = 2;
                break;
            case 9:
                s1 = 1;
                break;
            case 11:
                s1 = 4;
                break;
            case 14:
            case 15:
            case 16:
            case 21:
                s1 = 3;
                break;
            default:
                s1 = 0;
                break;
            }
        }
    } else if (mode == 1) {
        idx = *(s32 *)(D_003B2654 + 0x4C);
        if ((u32)idx < 0x10) {
            switch (idx) {
            case 1:
            case 2:
            case 3:
                s1 = 2;
                break;
            case 5:
            case 6:
            case 9:
                s1 = 1;
                break;
            case 12:
            case 13:
            case 14:
                s1 = 3;
                break;
            case 15:
                s1 = 4;
                break;
            default:
                s1 = 0;
                break;
            }
        }
    }
    s1 = s1 * 32;

    memcpy(arg0, base + s1, 16);
    memcpy(s2, base + s1 + 0x10, 16);

    s2[0] = (s2[0] / 180.0f) * D_00386FC8;
    s2[1] = (s2[1] / 180.0f) * D_00386FC8;
    s2[2] = (s2[2] / 180.0f) * D_00386FC8;
}
