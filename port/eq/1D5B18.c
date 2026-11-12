#include "common.h"

typedef struct { u64 lo, hi; } q128;

extern u8 *D_00387E9C;
void *func_001D5AB8(void);
void func_00129C28(q128 *arg0, q128 *arg1);

/* 0x001D5B18: copies four 16-byte inputs to the stack, asks func_001D5AB8 for a record,
 * fills it from the inputs and the float parameters (inverse spans, scales), and bumps a counter. */
void func_001D5B18(u8 *arg0, u8 *arg1, u8 *arg2, u8 *arg3, u8 *arg4, s32 arg5, s32 arg6, s32 arg7,
                   f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, f32 f17, f32 f18, f32 f19,
                   f32 f20, f32 f21, f32 fScale) {
    u8 tmp[0x50];
    u8 *rec;
    u8 *s2;
    u8 *s3;
    u8 *s4;
    u8 *s1;
    s32 k;
    f32 diff;
    f32 ratio;
    f32 fa;
    f32 fb;
    f32 fc;
    f32 fd;
    f32 fe;
    f32 ff;

    __builtin_memcpy(tmp + 0x00, arg0, 16);
    __builtin_memcpy(tmp + 0x10, arg1, 16);
    __builtin_memcpy(tmp + 0x20, arg2, 16);
    __builtin_memcpy(tmp + 0x30, arg3, 16);
    __builtin_memcpy(tmp + 0x40, arg4, 16);
    s2 = tmp + 0x10;
    s3 = tmp + 0x20;
    s4 = tmp + 0x30;
    s1 = tmp + 0x40;

    fa = f12;
    fb = f13;
    fc = f14;
    fd = f15;
    fe = f16;
    ff = f17;

    rec = (u8 *)func_001D5AB8();
    if (rec == 0) {
        return;
    }

    func_00129C28((q128 *)rec, (q128 *)tmp);
    func_00129C28((q128 *)(rec + 0x10), (q128 *)s2);
    func_00129C28((q128 *)(rec + 0x20), (q128 *)s3);
    *(f32 *)(rec + 0x30) = *(f32 *)s4;
    *(f32 *)(rec + 0x34) = *(f32 *)(tmp + 0x34);
    *(f32 *)(rec + 0x38) = *(f32 *)(tmp + 0x38);
    if (f20 == 0.0f) {
        *(f32 *)(rec + 0x3C) = *(f32 *)(tmp + 0x4C);
    } else {
        *(f32 *)(rec + 0x3C) = *(f32 *)(tmp + 0x3C);
    }
    func_00129C28((q128 *)(rec + 0x40), (q128 *)s1);

    for (k = 0; k < 3; k++) {
        diff = *(f32 *)(s1 + (k << 2)) - *(f32 *)(s4 + (k << 2));
        if (diff == 0.0f) {
            *(s32 *)(rec + 0x50 + (k << 2)) = 0;
        } else {
            *(f32 *)(rec + 0x50 + (k << 2)) = diff / (f21 * 30.0f);
        }
    }

    if (f20 == 0.0f) {
        ratio = -*(f32 *)(s1 + 0xC) / (f21 * 30.0f);
    } else {
        ratio = *(f32 *)(s1 + 0xC) / (f20 * 30.0f);
    }
    *(f32 *)(rec + 0x5C) = ratio;

    *(f32 *)(rec + 0x60) = fa;
    if (fb == 0.0f) {
        *(f32 *)(rec + 0x64) = 0.0f;
    } else {
        *(f32 *)(rec + 0x64) = 1.0f / fb;
    }
    *(f32 *)(rec + 0x68) = fc;
    *(f32 *)(rec + 0x6C) = fd;
    *(f32 *)(rec + 0x70) = fe;
    *(f32 *)(rec + 0x74) = ff;
    *(f32 *)(rec + 0x78) = f18;
    *(f32 *)(rec + 0x7C) = f19;
    if (f20 == 0.0f) {
        *(f32 *)(rec + 0x80) = f21 * 30.0f;
    } else {
        *(f32 *)(rec + 0x80) = (f21 - f20) * 30.0f;
    }

    *(u8 *)(rec + 0x8D) = (u8)arg5;
    *(s8 *)(rec + 0x8E) = (s8)arg6;
    *(u8 *)(rec + 0x8F) = (u8)arg7;
    *(u8 *)(rec + 0x90) = 1;
    *(u8 *)(rec + 0x91) = 0;
    *(u8 *)(rec + 0x8C) = 0;
    *(f32 *)(rec + 0x84) = fScale * 30.0f;

    *(s32 *)(D_00387E9C + 0x1434) = *(s32 *)(D_00387E9C + 0x1434) + 1;
}
