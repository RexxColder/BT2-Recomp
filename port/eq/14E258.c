#include "common.h"

s32 BtlScene_GetPackEntry(s32 arg0, s32 arg1);
void EftTexSet_Load4(u8 *arg0, s32 arg1);
void EftTexSet_Load8(u8 *arg0, s32 arg1);
void EftTexSet_Load16(u8 *arg0, s32 arg1);
void EftTexSet_Load32(u8 *arg0, s32 arg1);

#define G(i) BtlScene_GetPackEntry(*(s32 *)(arg0 + 0x1C), (i))
#define W(o) (*(s32 *)(b + (o)))
#define H(o) (*(u8 *)(*(u8 **)b + (o)))
#define PAIRS(cnt, xo, yo)                       \
    do {                                         \
        s32 k = 0;                               \
        do {                                     \
            s32 x = G(s1);                       \
            s1++;                                \
            W((xo) + 4 * k) = x;                 \
            x = G(s1);                           \
            s1++;                                \
            W((yo) + 4 * k) = x;                 \
            k++;                                 \
        } while (k < H(cnt));                    \
    } while (0)
#define SINGLES(cnt, xo)                         \
    do {                                         \
        s32 k = 0;                               \
        do {                                     \
            s32 x = G(s1);                       \
            s1++;                                \
            W((xo) + 4 * k) = x;                 \
            k++;                                 \
        } while (k < H(cnt));                    \
    } while (0)

/* 0x0014E258: walk the battle-effect pack index (a0+0x1C = scene) in order and bind each pack
 * entry into the effect table a1 (header pointer at a1+0); returns the next unused index. */
s32 func_0014E258(u8 *arg0, u8 *b) {
    s32 s1 = 5;
    s32 e;

    *(u8 **)(b + 0x1E78) = arg0;
    e = G(4);
    W(0) = e;
    if (*(u8 *)e != 0) {
        s1 = 7;
        e = G(5);
        W(8) = e;
        EftTexSet_Load4(b + 0x10, e);
        W(0x60) = G(6);
    }
    if (H(0x110) != 0) {
        e = G(s1);
        s1++;
        W(0x68) = e;
        EftTexSet_Load16(b + 0x70, e);
        if (H(0x110) != 0) {
            PAIRS(0x110, 0x180, 0x1A0);
        }
    }
    if (H(0x220) != 0) {
        e = G(s1);
        s1++;
        W(0x1C0) = e;
        EftTexSet_Load16(b + 0x1C8, e);
        e = G(s1);
        s1++;
        W(0x2D8) = e;
        e = G(s1);
        s1++;
        W(0x2DC) = e;
    }
    if (H(0x330) != 0) {
        e = G(s1);
        s1++;
        W(0x2E0) = e;
        EftTexSet_Load16(b + 0x2E8, e);
        e = G(s1);
        s1++;
        W(0x3F8) = e;
        e = G(s1);
        s1++;
        W(0x3FC) = e;
    }
    if (H(0x440) != 0) {
        e = G(s1);
        s1++;
        W(0x400) = e;
        EftTexSet_Load32(b + 0x408, e);
        if (H(0x440) != 0) {
            PAIRS(0x440, 0x618, 0x638);
        }
    }
    if (H(0x550) != 0) {
        if (H(0x551) != 0) {
            s32 k = 0;
            s32 s5 = 0x680;
            s32 s0 = 0x678;
            do {
                e = G(s1);
                k++;
                s1++;
                W(s0) = e;
                s0 += 0x218;
                EftTexSet_Load32(b + s5, e);
                s5 += 0x218;
            } while (k < H(0x551));
        }
        if (H(0x550) != 0) {
            SINGLES(0x550, 0x658);
        }
    }
    if (H(0x660) != 0) {
        e = G(s1);
        s1++;
        W(0x1540) = e;
        EftTexSet_Load8(b + 0x1548, e);
        if (H(0x660) != 0) {
            PAIRS(0x660, 0x15D8, 0x15EC);
        }
    }
    if (H(0x770) != 0) {
        e = G(s1);
        s1++;
        W(0x1600) = e;
        EftTexSet_Load16(b + 0x1608, e);
        if (H(0x770) != 0) {
            PAIRS(0x770, 0x1718, 0x172C);
        }
    }
    if (H(0x990) != 0) {
        e = G(s1);
        s1++;
        W(0x1740) = e;
        EftTexSet_Load8(b + 0x1748, e);
        if (H(0x660) != 0) {
            PAIRS(0x660, 0x17D8, 0x17EC);
        }
    }
    if (H(0xAA0) != 0) {
        e = G(s1);
        s1++;
        W(0x1800) = e;
        EftTexSet_Load16(b + 0x1808, e);
        if (H(0xAA0) != 0) {
            PAIRS(0xAA0, 0x1918, 0x1938);
        }
    }
    if (H(0xBB0) != 0) {
        e = G(s1);
        s1++;
        W(0x1958) = e;
        EftTexSet_Load16(b + 0x1960, e);
        if (H(0xBB0) != 0) {
            PAIRS(0xBB0, 0x1A70, 0x1A90);
        }
    }
    if (H(0xCC0) != 0) {
        e = G(s1);
        s1++;
        W(0x1AB0) = e;
        EftTexSet_Load16(b + 0x1AB8, e);
        if (H(0xCC0) != 0) {
            PAIRS(0xCC0, 0x1BC8, 0x1BD8);
        }
    }
    if (H(0xDD0) != 0) {
        e = G(s1);
        s1++;
        W(0x1BE8) = e;
        EftTexSet_Load16(b + 0x1BF0, e);
        if (H(0xDD0) != 0) {
            PAIRS(0xDD0, 0x1D00, 0x1D20);
        }
    }
    if (H(0xEE0) != 0) {
        e = G(s1);
        s1++;
        W(0x1D40) = e;
        EftTexSet_Load16(b + 0x1D48, e);
        if (H(0xEE0) == 0) {
            return s1;
        }
        PAIRS(0xEE0, 0x1E58, 0x1E68);
    }
    return s1;
}
