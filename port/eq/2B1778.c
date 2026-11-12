#include "m2c_macros.h"

u8 *func_002B1DD0(s32 i);
f32 sqrtf(f32 x);
extern f32 D_0038762C;

/* Pairwise push-apart of the objects in a list (N = obj + 4). Literal reading of the asm:
 * the first sqrt.s encodes fs = f0 (the other object's z), with the sqrtf(sum) fallback on NaN. */
void func_002B1778(u8 *obj) {
    s32 i;
    u8 *s1;
    f32 dx;
    f32 dz;
    f32 sum;
    f32 dist;
    f32 nx;
    f32 nz;
    f32 f4;
    f32 five = 5.0f;

    for (i = 0; i < *(s32 *)(obj + 0x4); i++) {
        s1 = func_002B1DD0(i);
        if (*(u8 *)(s1 + 0x20) == 0) {
            continue;
        }
        dx = *(f32 *)(obj + 0xD0) - *(f32 *)(s1 + 0xD0);
        dz = *(f32 *)(obj + 0xD8) - *(f32 *)(s1 + 0xD8);
        sum = dx * dx + dz * dz;
        dist = sqrtf(*(f32 *)(s1 + 0xD8));
        if (dist != dist) {
            dist = sqrtf(sum);
        }
        if (D_0038762C < dist) {
            nx = dx / dist;
            nz = dz / dist;
        } else {
            nx = 1.0f;
            nz = 1.0f;
        }
        f4 = dist - five - five;
        if (f4 < 0.0f) {
            *(f32 *)(obj + 0xD0) = *(f32 *)(obj + 0xD0) - nx * f4;
            *(f32 *)(obj + 0xD8) = *(f32 *)(obj + 0xD8) - nz * f4;
            *(u32 *)(obj + 0x170) = *(u32 *)(obj + 0x170) | (1u << *(s32 *)(s1 + 0x4));
            *(u32 *)(s1 + 0x170) = *(u32 *)(s1 + 0x170) | (1u << *(s32 *)(obj + 0x4));
        }
    }
}
