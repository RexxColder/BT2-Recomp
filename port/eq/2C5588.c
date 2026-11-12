#include "common.h"

extern u8 D_00399C68[];
extern s32 D_00399C90[];
extern s32 D_00399C98[];
extern void *memcpy(void *dst, const void *src, u32 n);

/* 0x002C5588: copies the first 0x20 bytes of arg0 to D_00399C68 (words +0x10 and +0x20 zeroed); D_00399C90[0..1] = round-up
 * to 64 of arg1[0..1]; D_00399C98[0..15] = round-up to 64 of arg2[k] for k < arg0->0x1C, else 0. */
void func_002C5588(u8 *arg0, s32 *arg1, s32 *arg2) {
    s32 i;
    s32 n;

    memcpy(D_00399C68, arg0, 0x20);
    *(s32 *)(D_00399C68 + 0x10) = 0;
    *(s32 *)(D_00399C68 + 0x20) = 0;
    for (i = 0; i < 2; i++) {
        D_00399C90[i] = (arg1[i] + 0x3F) & ~0x3F;
    }
    n = *(s32 *)(arg0 + 0x1C);
    for (i = 0; i < 16; i++) {
        if (i < n) {
            D_00399C98[i] = (arg2[i] + 0x3F) & ~0x3F;
        } else {
            D_00399C98[i] = 0;
        }
    }
}
