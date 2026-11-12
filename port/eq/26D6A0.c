#include "common.h"

extern u8 D_00387A78[], D_00387A80[], D_00387A88[], D_00387A90[], D_00387A98[], D_00387AA0[], D_00387AA8[];

void *memset(void *arg0, s32 arg1, u32 arg2);
s32 strcmp(const u8 *a, const u8 *b);
void func_0026CE98(u8 *a0, u8 *a1, s32 *a2);
s32 func_0026CD98(s32 a0, u8 *a1);
u8 *func_002701F0(s32 a0, u8 *a1);
extern s32 func_00325830();

#define W(p, o) (*(s32 *)((p) + (o)))

s32 func_0026D6A0(u8 *a0, u8 *a1, s32 *a2) {
    u8 sp[0x1E0];
    u8 *s3 = a0;
    u8 op;
    s32 idx, v, i, s2;
    u8 *obj;

    idx = *a2;
    op = a1[idx];
    *a2 = idx + 1;
    sp[0] = op;
    if (op == 0) return idx + 1;
    for (;;) {
        obj = *(u8 **)a0;
        if (a0[0x11] & 0x20) {
            switch ((u32)(op - 0x81)) {
            case 0:
                *a2 = *a2 + 2;
                break;
            case 2:
                memset(sp + 0x10, 0, 0x40);
                memset(sp + 0x50, 0, 0x40);
                func_0026CE98(sp + 0x10, a1, a2);
                func_0026CE98(sp + 0x50, a1, a2);
                if (strcmp(sp + 0x10, D_00387A78) == 0) {
                    if (strcmp(sp + 0x50, D_00387A80) == 0) {
                        W(*(u8 **)a0, 0x14) |= 2;
                    } else if (strcmp(sp + 0x50, D_00387A88) == 0) {
                        W(*(u8 **)a0, 0x14) &= ~2;
                    }
                }
                break;
            case 9:
                *a2 = *a2 + 3;
                break;
            case 10:
            case 11:
                idx = *a2;
                if (a1[idx]) {
                    do {
                        idx++;
                        *a2 = idx;
                    } while (a1[idx]);
                }
                *a2 = idx + 1;
                return 0;
            default:
                break;
            }
        } else {
            switch (op) {
            case 4:
                v = W(s3, 8) + 1;
                W(s3, 8) = v;
                s3[0x11] = (s3[0x11] & 0xF7) | 4;
                break;
            case 5:
                v = W(s3, 8) - 1;
                s3[0x11] = (s3[0x11] & 0xFB) | 8;
                W(s3, 8) = v;
                break;
            case 6:
                s3[0x11] = (s3[0x11] & 0xFE) | 2;
                break;
            case 7:
                s3[0x11] = (s3[0x11] & 0xFD) | 1;
                break;
            case 0x81:
                idx = *a2;
                s3[8] = a1[idx];
                s3[9] = a1[idx + 1];
                *a2 = idx + 2;
                s3[0x11] |= 0x10;
                break;
            case 0x83:
                memset(sp + 0x10, 0, 0x40);
                memset(sp + 0x50, 0, 0x40);
                func_0026CE98(sp + 0x10, a1, a2);
                func_0026CE98(sp + 0x50, a1, a2);
                if (strcmp(sp + 0x10, D_00387A78) == 0) {
                    if (strcmp(sp + 0x50, D_00387A80) == 0) {
                        W(*(u8 **)a0, 0x14) |= 2;
                    } else if (strcmp(sp + 0x50, D_00387A88) == 0) {
                        W(*(u8 **)a0, 0x14) &= ~2;
                    }
                } else if (strcmp(sp + 0x10, D_00387A90) == 0) {
                    if (strcmp(sp + 0x50, D_00387A98) == 0) {
                        W(*(u8 **)a0, 0x14) |= 8;
                    } else if (strcmp(sp + 0x50, D_00387AA0) == 0) {
                        W(*(u8 **)a0, 0x14) |= 0x200;
                    } else {
                        memset(sp + 0x90, 0, 0x40);
                        s2 = 0;
                        do {
                            i = s2 + 1;
                            func_00325830(sp + 0x90, D_00387AA8, i);
                            if (strcmp(sp + 0x50, sp + 0x90) == 0)
                                W(*(u8 **)a0, 0x14) |= 0x10 << s2;
                            s2 = i;
                        } while (s2 < 5);
                    }
                }
                break;
            case 0x8A:
                idx = *a2;
                sp[0xD0] = a1[idx];
                sp[0xD1] = a1[idx + 1];
                *a2 = idx + 2;
                *a2 = idx + 3;
                sp[0xD2] = a1[idx + 2];
                break;
            case 0x8B:
                memset(sp + 0x90, 0, 0x40);
                func_0026CE98(sp + 0x90, a1, a2);
                if ((s8)sp[0x90] != 0) {
                    u8 *r;
                    s3 = a0;
                    r = func_002701F0(W(*(u8 **)a0, 0x1C), sp + 0x90);
                    if (r) s3 = r + 0xA8;
                } else {
                    s3 = a0;
                }
                break;
            case 0x8C:
                memset(sp + 0xE0, 0, 0xFF);
                func_0026CE98(sp + 0xE0, a1, a2);
                v = func_0026CD98(W(s3, 4), sp + 0xE0);
                if (v >= 0) W(s3, 8) = v;
                s3[0x11] |= 0x10;
                break;
            default:
                break;
            }
        }
        idx = *a2;
        op = a1[idx];
        *a2 = idx + 1;
        sp[0] = op;
        if (op == 0) return 0;
    }
}
