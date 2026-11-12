#include "common.h"

extern u8 *gObjOutline;

#define W(p, off) (*(s32 *)((p) + (off)))
#define LD(p, off) (*(s64 *)((p) + (off)))

/* GS packet builder: writes 0x50 bytes at out and returns out + 0x50. */
u8 *func_00106DC0(u8 *out, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7) {
    s32 s0;
    s32 s1;
    s32 t1s;
    s32 base;
    u8 *t7;
    s32 half;
    s32 h3;
    s32 t5;
    s32 t9;
    s32 P1;
    s32 v0;
    s32 t4;
    s32 t8;
    s32 t1b;
    s32 t0n;
    s32 a1n;
    s32 a2n;
    s32 a3n;
    s32 A1;
    s32 V1;
    s32 T3v;
    s32 A0;
    s64 s2;
    s64 s3;
    s64 v0b;
    s64 v1p;
    s64 a0p;
    s64 v0p;
    s64 t2s;
    s64 M;

    s0 = arg1 + 0x700;
    s1 = arg2 + 0x720;
    t1s = arg5 << 6;
    base = W((u8 *)W(gObjOutline, 0), 0x10);
    t7 = (u8 *)(base + t1s);
    half = arg4 >> 1;
    t5 = arg2 + half;
    t9 = arg2 + arg4 + 0x720;
    P1 = (s32)((u32)arg6 * (u32)arg4);
    v0 = (s32)((u32)P1 + (u32)arg4);
    t4 = W(t7, 0x20);
    t8 = (arg2 - half) + 0x720;
    t1b = W(t7, 0x24);
    t5 = t5 + 0x720;
    t0n = P1;
    v0 = (s32)((u32)v0 << 4);
    h3 = arg3 >> 1;
    a2n = arg1 + h3;
    a3n = arg1 + arg3;
    a1n = arg1 - h3;
    t0n = (s32)((u32)t0n << 4);
    s2 = (s64)t0n << 16;
    v0b = (s64)v0 << 16;
    a3n = a3n + 0x700;
    s3 = (s64)(s32)((u32)arg3 << 4) | v0b;
    a1n = a1n + 0x700;
    a2n = a2n + 0x700;
    t4 = t4 + 0x2A40;
    t1b = t1b + 0x2A00;

    if (arg7 != 0) {
        A1 = (s32)((u32)a1n << 4);
        V1 = (s32)((u32)t8 << 4);
        T3v = (s32)((u32)a2n << 4);
        A0 = (s32)((u32)t5 << 4);
    } else {
        A1 = (s32)((u32)s0 << 4);
        V1 = (s32)((u32)s1 << 4);
        T3v = (s32)((u32)a3n << 4);
        A0 = (s32)((u32)t9 << 4);
    }

    M = (s64)0x0F00000000000000LL;
    v1p = (s64)A1 | ((s64)V1 << 16);
    v1p = v1p | M;
    a0p = ((s64)T3v | ((s64)A0 << 16)) | M;
    t2s = (s64)t1b << 37;
    v0p = LD(t7, 0x30) | t2s;
    v0p = v0p | (s64)t4;
    v0p = v0p | (s64)0x400000000LL;

    LD(out, 0x00) = (s64)0x8400000000008001LL;
    LD(out, 0x08) = (s64)0x535316F0LL;
    LD(out, 0x10) = (s64)0x156;
    LD(out, 0x18) = 0;
    LD(out, 0x20) = v0p;
    LD(out, 0x28) = (s64)0x3F80000080808080LL;
    LD(out, 0x30) = s2;
    LD(out, 0x38) = v1p;
    LD(out, 0x40) = s3;
    LD(out, 0x48) = a0p;
    return out + 0x50;
}
