#include "common.h"

void *memset(void *arg0, s32 arg1, s32 arg2);
void func_0026CE98(void *arg0, void *arg1, void *arg2);
u8 *func_002701F0(void *arg0, void *arg1);
s32 func_0026CD98(void *arg0, void *arg1);

/* byte-code interpreter: sp[0] = current command, sp[0x10] = 0x40-byte buffer, sp[0x50] = 0xFF-byte buffer,
   sp[0x150] = read position (passed to func_0026CE98 by address) */
void func_0026BD80(u8 *arg0, u8 *arg1) {
    u8 sp[0x160] __attribute__((aligned(8)));
    s32 *posp = (s32 *)(sp + 0x150);
    u8 *s0;
    u8 *r;
    s32 p;
    s32 r2;
    u8 c;

    *posp = 2;
    sp[0] = arg1[1];
    if (sp[0] == 0) {
        return;
    }
    s0 = arg0;

    do {
        c = sp[0];
        if (c == 0x81) {
            p = *posp;
            s0[8] = arg1[p];
            s0[9] = arg1[p + 1];
            *posp = p + 2;
            s0[0x11] |= 0x10;
        } else if (c == 4) {
            *(s32 *)(s0 + 8) = *(s32 *)(s0 + 8) + 1;
        } else if (c == 5) {
            *(s32 *)(s0 + 8) = *(s32 *)(s0 + 8) - 1;
        } else if (c == 6) {
            s0[0x11] = (s0[0x11] & 0xFE) | 2;
        } else if (c == 7) {
            s0[0x11] |= 1;
        } else if (c == 0x8A) {
            p = *posp;
            sp[2] = arg1[p];
            sp[3] = arg1[p + 1];
            sp[4] = arg1[p + 2];
            *posp = p + 3;
        } else if (c == 0x83) {
            p = *posp;
            if (arg1[p] != 0) {
                p += 1;
                while (arg1[p] != 0) {
                    p += 1;
                }
                *posp = p;
            }
        } else if (c == 0x8B) {
            memset(sp + 0x10, 0, 0x40);
            func_0026CE98(sp + 0x10, arg1, posp);
            if (sp[0x10] != 0) {
                r = func_002701F0(*(void **)(*(u8 **)arg0 + 0x1C), sp + 0x10);
                s0 = arg0;
                if (r != NULL) {
                    s0 = r + 0xA8;
                }
            } else {
                s0 = arg0;
            }
        } else if (c == 0x8C) {
            memset(sp + 0x50, 0, 0xFF);
            func_0026CE98(sp + 0x50, arg1, posp);
            r2 = func_0026CD98(*(void **)(s0 + 4), sp + 0x50);
            if (r2 >= 0) {
                *(s32 *)(s0 + 8) = r2;
            }
            s0[0x11] |= 0x10;
        }

        p = *posp;
        c = arg1[p];
        sp[0] = c;
        *posp = p + 1;
    } while (c != 0);
}
