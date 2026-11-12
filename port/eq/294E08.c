#include "common.h"

f32 sceVu0InnerProduct(void *arg0, void *arg1);
void func_00312650(void *arg0, void *arg1, void *arg2);
void func_00312FB0(void *arg0, void *arg1, f32 arg2);
void func_00312638(void *arg0, void *arg1, void *arg2);
extern f32 D_003871A0;

/* 0x00294E08: squared distance from pt to the infinite line a..b; out = a + projection (BT3 ColLine_DistSqPoint, same code).
 * A zero line length uses D_003871A0 instead. */
f32 ColLine_DistSqPoint(void *pt, void *a, void *b, void *out) {
    u8 d[0x10];
    u8 l[0x10];
    u8 proj[0x10];
    f32 len;

    func_00312650(d, pt, a);
    func_00312650(l, b, a);
    len = sceVu0InnerProduct(l, l);
    if (len == 0.0f) {
        len = D_003871A0;
    }
    func_00312FB0(proj, l, sceVu0InnerProduct(d, l) / len);
    func_00312638(out, a, proj);
    func_00312650(d, d, proj);
    return sceVu0InnerProduct(d, d);
}
