#include "common.h"

extern u8 *D_00387A40;
extern f32 D_00383F1C;

f32 sceVu0InnerProduct(void *arg0, void *arg1);
void sceVu0ApplyMatrix(s32 arg0, s32 arg1, s32 arg2);
void func_00312650(void *arg0, void *arg1, void *arg2);
s32 func_0020B0B8(u32 arg0);

s32 func_00116038(u8 *obj, u32 id, s32 slot) {
    f32 vec_a[4];
    f32 vec_b[4];
    f32 cross[4];
    f32 xform[4];
    f32 ip;
    f32 len;
    f32 cur;
    f32 cur_after;
    f32 blend;
    s32 base;
    s32 row_a;
    s32 row_b;
    s32 stride;

    if (func_0020B0B8(id) == 0) {
        *(s32 *)(obj + 0x28) = 0;
        *(f32 *)(obj + 0x1C) = 15.0f;
        *(s32 *)(obj + 0x20) = 0;
        *(s32 *)(obj + 0x18) = 0;
        *(s32 *)(obj + 0x24) = 0;
        return 0;
    }

    stride = 0x18580;
    row_a = (s32)id * stride;
    row_b = slot * stride;
    base = *(s32 *)D_00387A40;

    vec_a[0] = (f32)(s32)*(f32 *)(base + row_a + 0x9C0);
    vec_a[1] = 0.0f;
    vec_a[2] = (f32)(s32)*(f32 *)(base + row_a + 0x9C8);
    vec_a[3] = 1.0f;

    vec_b[0] = (f32)(s32)*(f32 *)(base + row_b + 0x9C0);
    vec_b[1] = 0.0f;
    vec_b[2] = (f32)(s32)*(f32 *)(base + row_b + 0x9C8);
    vec_b[3] = 1.0f;

    func_00312650(cross, vec_b, vec_a);
    ip = sceVu0InnerProduct(cross, cross);
    len = __builtin_sqrtf(ip);

    cur = *(f32 *)obj;
    if (cur < len) {
        vec_b[2] = vec_a[2] + cross[2] * (cur - 170.0f) / len;
        vec_b[0] = vec_a[0] + cross[0] * (cur - 170.0f) / len;
    }

    sceVu0ApplyMatrix((s32)xform, (s32)(obj + 0x70), (s32)vec_b);

    cur_after = *(f32 *)(obj + 0x18);
    *(s32 *)(obj + 0x24) = (s32)xform[0];
    *(s32 *)(obj + 0x2C) = 0x00C8C8C8;
    *(s32 *)(obj + 0x20) = 1;
    *(s32 *)(obj + 0x28) = (s32)xform[1];
    *(f32 *)(obj + 0x1C) = 15.0f;

    blend = cur_after + (16.0f - cur_after) * D_00383F1C;
    *(f32 *)(obj + 0x18) = blend;
    if (15.0f < blend) {
        *(s32 *)(obj + 0x20) = 0;
        *(s32 *)(obj + 0x18) = 0;
    }
    return 0x00C8C8C8;
}
