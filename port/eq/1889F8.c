#include "common.h"

extern f32 D_00384BD0;
extern f32 D_00384BD4;

void func_00188C48(void *arg0, void *arg1, void *arg2, f32 farg0, f32 farg1, f32 farg2);
void func_001890F8(void *arg0, void *arg1, void *arg2, s32 arg3, s32 arg4);
void func_00189EB8(void **arg0, void **arg1, void *arg2);
void func_00189EE8(void **arg0, void **arg1, u8 *arg2);
s32 func_00189F50(void);

s32 func_001889F8(u8 *arg0) {
    u8 mtx[64];
    u8 *obj = arg0;
    u8 *s3;
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
    s3 = *(u8 **)(obj + 0x30);
    s7 = *(u8 **)(obj + 0x34);
    list = *(u8 **)(obj + 0x1E0);
    step = D_00384BD0 / *(f32 *)(obj + 0xB4);

    for (i = 0; i < (s32)*(f32 *)(obj + 0xB4); i++) {
        k = D_00384BD4;
        lo = *(f32 *)(s3 + 0x24);
        rnd = Rand_FloatRange(lo, lo + *(f32 *)(s3 + 0x28));
        outer = EftMath_WrapAngle(step * (f32)i + rnd * k);

        for (j = 0; j < (s32)*(f32 *)(obj + 0xB4); j++) {
            lo2 = *(f32 *)(s3 + 0x2C);
            rnd = Rand_FloatRange(lo2, lo2 + *(f32 *)(s3 + 0x30));
            inner = EftMath_WrapAngle(step * (f32)j + rnd * k);

            if (list != NULL) {
                e = list;
                if ((*(u16 *)(e + 0xBE) & 2) != 0) {
                    list = *(u8 **)(e + 0xC0);
                    continue;
                }
            } else {
                e = func_00189F50();
                if (e == NULL) {
                    continue;
                }
                list = e;
                func_00189EB8((void **)(obj + 0x1E0), (void **)(obj + 0x1E4), e);
            }

            func_001890F8(e, s3, s7, *(u8 *)(obj + 0x1D5), *(u8 *)(obj + 0x1D4));
            scale = *(f32 *)(s3 + 0x20) * (f32)placed;
            placed++;
            func_00188C48(e, s3, mtx, outer, inner, scale);
            *(u16 *)(e + 0xBE) |= 3;
            list = *(u8 **)(e + 0xC0);
        }
    }

    while (list != NULL) {
        if ((*(u16 *)(list + 0xBE) & 2) == 0) {
            *(u16 *)(list + 0xBE) = 0;
            func_00189EE8((void **)(obj + 0x1E0), (void **)(obj + 0x1E4), list);
        }
        list = *(u8 **)(list + 0xC0);
    }

    return 1;
}
