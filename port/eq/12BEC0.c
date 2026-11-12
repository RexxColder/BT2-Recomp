#include "common.h"

#define FLAG(i) (*(s32 *)(fr + 0x1D0 + (i) * 4))

f32 func_00129CD8(void *a, void *b);
void func_00129B58(void *dst, void *a, void *b, s32 n);
void func_00129C28(void *dst, void *src);
void func_00129DB8(f32 w, void *dst, void *a, void *b);

s32 func_0012BEC0(void *arg0, s32 arg1, void *arg2) {
    u8 fr[0x280];
    u8 *base = (u8 *)arg2;
    u8 *o;
    s32 nz = 0;
    s32 cnt = 0;
    s32 i;
    s32 k;
    f32 f20;
    f32 f21;
    f32 t;

    *(s64 *)(fr + 0x00) = *(s64 *)((u8 *)arg0 + 0x00);
    *(s64 *)(fr + 0x08) = *(s64 *)((u8 *)arg0 + 0x08);

    for (i = 0; i < arg1; i++) {
        f32 f0 = func_00129CD8(fr, base + i * 0x10) + *(f32 *)(fr + 0xC);
        s32 neg = (f0 < 0.0f) ? 1 : 0;
        FLAG(i) = neg;
        nz += neg;
    }

    if (nz == 0) {
        return arg1;
    }
    if (arg1 == nz) {
        return 0;
    }

    o = fr + 0x10;
    for (i = 0; i < arg1; i++) {
        s32 s7 = i + 1;
        s32 s2 = (s7 < arg1) ? s7 : 0;
        u8 *ei = base + i * 0x10;
        u8 *es = base + s2 * 0x10;
        s32 act;

        if (FLAG(i) == 0) {
            cnt += 1;
            func_00129C28(o, ei);
            func_00129C28(o + 0x90, ei + 0x90);
            func_00129C28(o + 0x120, ei + 0x120);
            o += 0x10;
            act = (FLAG(s2) != 0);
        } else {
            act = (FLAG(s2) == 0);
        }

        if (act) {
            cnt += 1;
            func_00129B58(fr + 0x1C0, ei, es, cnt);
            f20 = func_00129CD8(fr, ei);
            t = func_00129CD8(fr, fr + 0x1C0);
            f21 = 1.0f - ((f20 + *(f32 *)(fr + 0xC)) / t);
            func_00129DB8(f21, o, ei, es);
            func_00129DB8(f21, o + 0x90, ei + 0x90, es + 0x90);
            func_00129DB8(f21, o + 0x120, ei + 0x120, es + 0x120);
            o += 0x10;
        }
    }

    for (k = 0; k < 0x1B0; k += 8) {
        *(s64 *)((u8 *)arg2 + k) = *(s64 *)(fr + 0x10 + k);
    }

    return cnt;
}
