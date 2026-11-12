#include "common.h"

extern f32 D_00384B98;
extern f32 D_00384B9C;

void func_00184F48(void *arg0, void *arg1, void *arg2, s32 arg3, s32 arg4);
void func_00184AD0(void *arg0, void *arg1, void *arg2, s32 p3, s32 p4, s32 p5, s32 p6, s64 p7,
                   f32 f0, f32 f1, f32 f2);
void func_00185C38(void **arg0, void **arg1, void *arg2);
void func_00185C68(void **arg0, void **arg1, u8 *arg2);
s32 func_00185CD0(void);

s32 func_00184880(u8 *arg0, s64 a1, s64 a2, s64 a3, s64 t0, s64 t1, s64 t2, s64 t3) {
    u8 mtx[64];
    u8 *obj = arg0;
    u8 *s2;
    u8 *s7;
    u8 *list;
    u8 *e;
    f32 step;
    f32 k;
    f32 outer;
    f32 inner;
    f32 rnd;
    f32 lo;
    f32 lo2;
    f32 scale;
    s32 placed = 0;
    s32 i;
    s32 j;

    __builtin_memset(mtx, 0, sizeof(mtx));
    Mtx_StoreIdentity(mtx);
    s2 = *(u8 **)(obj + 0x30);
    s7 = *(u8 **)(obj + 0x34);
    list = *(u8 **)(obj + 0x1A4);
    step = D_00384B98 / *(f32 *)(s2 + 0x94);

    for (i = 0; i < (s32)*(f32 *)(s2 + 0x94); i++) {
        k = D_00384B9C;
        lo = *(f32 *)(s2 + 0x24);
        rnd = Rand_FloatRange(lo, lo + *(f32 *)(s2 + 0x28));
        outer = EftMath_WrapAngle(step * (f32)i + rnd * k);

        for (j = 0; j < (s32)*(f32 *)(s2 + 0x94); j++) {
            lo2 = *(f32 *)(s2 + 0x2C);
            rnd = Rand_FloatRange(lo2, lo2 + *(f32 *)(s2 + 0x30));
            inner = EftMath_WrapAngle(step * (f32)j + rnd * k);

            if (list != NULL) {
                e = list;
                if ((*(u16 *)(e + 0xBE) & 2) != 0) {
                    list = *(u8 **)(e + 0xC0);
                    continue;
                }
            } else {
                e = func_00185CD0();
                if (e == NULL) {
                    continue;
                }
                list = e;
                func_00185C38((void **)(obj + 0x1A4), (void **)(obj + 0x1A8), e);
            }

            func_00184F48(e, s2, s7, *(u8 *)(obj + 0x199), *(u8 *)(obj + 0x198));
            scale = *(f32 *)(s2 + 0x20) * (f32)placed;
            placed++;
            func_00184AD0(e, mtx, s2, 0, 0, 0, 0, t3, outer, inner, scale);
            *(u16 *)(e + 0xBE) |= 3;
            list = *(u8 **)(e + 0xC0);
        }
    }

    while (list != NULL) {
        if ((*(u16 *)(list + 0xBE) & 2) == 0) {
            *(u16 *)(list + 0xBE) = 0;
            func_00185C68((void **)(obj + 0x1A4), (void **)(obj + 0x1A8), list);
        }
        list = *(u8 **)(list + 0xC0);
    }

    return 1;
}
