#include "m2c_macros.h"

extern u8 *D_00387AEC;
extern u8 *D_003876A0;

void Vu0Screen_StoreMtx(f32 *m);
void sceVu0RotTransPersN(f32 *dst, f32 *m, f32 *src, s32 n, s32 flag);
void func_00312720(f32 *dst, f32 *src);
s32 func_0027AC98(f32 *v, s32 a1);
void func_0027AE58(u8 *obj);

void func_0027BA08(void) {
    f32 fr[20];
    f32 *mtx = fr;
    f32 *vec = fr + 16;
    u8 *p;
    u8 *obj;
    f32 *s1;
    f32 x;
    s32 i;
    s32 r;

    p = D_00387AEC;
    if (p == NULL) {
        return;
    }
    if (*(s64 *)(D_003876A0 + 0x4D8) & 0x100) {
        return;
    }
    if (M2C_FIELD(p, s32 *, 0xA8) + M2C_FIELD(p, s32 *, 0xAC) <= 0) {
        return;
    }
    Vu0Screen_StoreMtx(mtx);
    for (i = 0; i < 10; i++) {
        p = D_00387AEC;
        obj = *(u8 **)p + i * 0x460;
        if (*(s32 *)obj == 0) {
            continue;
        }
        if (*(s32 *)obj & 2) {
            func_0027AE58(obj);
            continue;
        }
        sceVu0RotTransPersN(vec, mtx, (f32 *)(obj + 0x440), 1, 0);
        s1 = (f32 *)(obj + 0x450);
        func_00312720(s1, vec);
        r = func_0027AC98(s1, 0);
        if (r == 0) {
            s32 v4 = *(s32 *)(obj + 4);
            *(s32 *)obj = 0;
            p = D_00387AEC;
            if (v4 == 0) {
                *(s32 *)(p + 0xA8) = *(s32 *)(p + 0xA8) - 1;
            } else {
                *(s32 *)(p + 0xAC) = *(s32 *)(p + 0xAC) - 1;
            }
            return;
        }
        x = *s1;
        *(f32 *)(obj + 0x438) = x;
        *(f32 *)(obj + 0x43C) = *(f32 *)(obj + 0x454);
        *s1 = x - 1792.0f;
        *(f32 *)(obj + 0x454) = *(f32 *)(obj + 0x454) - 1824.0f;
        *s1 = *s1 * 0.5f;
        *(s32 *)obj = *(s32 *)obj | 2;
        *(f32 *)(obj + 0x454) = *(f32 *)(obj + 0x454) * 0.5f;
        func_0027AE58(obj);
    }
}
