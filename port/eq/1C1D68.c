#include "common.h"

void EftTexSet_Load16(u8 *arg0, s32 arg1, s32 arg2);
extern u8 *D_00387898;

u8 *func_001C1D68(s32 arg0) {
    u8 *G;
    u8 *v1;
    s32 a2v;
    s32 s1;
    s32 s2;
    s32 s0;
    s32 a1v;
    s32 a3v;
    s32 t0;
    s32 t1;
    s32 t2;
    s32 cnt;
    s32 tmp;
    u8 *p;

    G = D_00387898;
    a2v = (s32)G;
    s1 = 0;
    if (*(s32 *)(G + 0x108) != 0) {
        v1 = G + 0x108;
        a2v = 0;
        do {
            s1 += 1;
            v1 += 0x108;
            a2v += 0x20;
            if (s1 > 0) {
                s2 = s1 << 5;
                break;
            }
            s2 = a2v;
            if (*(s32 *)v1 == 0) {
                break;
            }
        } while (1);
    } else {
        s2 = 0;
    }

    s0 = (s2 + s1) << 3;
    EftTexSet_Load16(G + s0 + 8, arg0, a2v);

    a1v = s0 + 0x100;
    t1 = 0;
    t2 = s1 << 4;
    cnt = *(s32 *)(G + a1v + 8);
    if (cnt > 0) {
        a1v = t2 + 0x110;
        t0 = s0;
        a3v = a1v;
        do {
            if (*(s64 *)(G + t0 + 8) == 0) {
                *(u8 *)(G + a1v) = 1;
            } else {
                *(u8 *)(G + a3v) = 2;
            }
            t0 += 0x10;
            t1 += 1;
            a3v += 1;
            a1v += 1;
        } while (t1 < *(s32 *)(G + (s0 + 0x100) + 8));
    }
    *(u8 *)(G + t1 + t2 + 0x110) = 3;

    tmp = (((s2 + s1) << 3)) + 0x100;
    t1 = 0;
    if (*(s32 *)(G + tmp + 8) - 1 > 0) {
        t0 = t2;
        do {
            p = G + t1 + t0 + 0x110;
            cnt = t1 + 1;
            if (*p == 2) {
                if (*(u8 *)(G + cnt + t2 + 0x110) == 1) {
                    *p = 0;
                }
            }
            t1 = cnt;
        } while (t1 < *(s32 *)(G + tmp + 8) - 1);
    }

    *(s32 *)(G + 0x120) = *(s32 *)(G + 0x120) + 1;
    return G + (((s2 + s1) << 3)) + 8;
}
