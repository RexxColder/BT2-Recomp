#include "common.h"

extern u8 D_003B2654[] __attribute__((section(".data")));
extern u8 *D_00387A40;
extern f32 D_00386E98;

void *memset(void *arg0, s32 arg1, s32 arg2);
s32 func_00276B00(s32 arg0, s32 arg1, s32 arg2);
void func_003126C8(s32 arg0, s32 arg1);
void func_0025ACF8(s32 arg0, s32 arg1);
void func_0025FED8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void func_00260A50(s32 arg0);
u8 *func_00261060(s32 arg0);

void func_002616B8(void) {
    u8 sp[0x40];
    u8 *s1;
    u8 *p;
    s32 s2;
    s32 s3;
    s32 cnt;
    s32 t0;
    f32 f8;
    f32 f1;
    f32 f3;
    f32 f5;
    f32 f6;
    f32 f4;
    f32 f0;

    memset(sp, 0, 0x10);
    *(f32 *)(sp + 0x0C) = 1.0f;
    memset(sp + 0x10, 0, 0x10);
    *(f32 *)(sp + 0x1C) = 1.0f;
    memset(sp + 0x20, 0, 0x10);
    *(f32 *)(sp + 0x2C) = 1.0f;
    memset(sp + 0x30, 0, 0x10);
    *(f32 *)(sp + 0x3C) = 1.0f;

    if (*(s32 *)(D_003B2654 + 0x48) >= 0) {
        if (func_00276B00(*(s32 *)(D_003B2654 + 0x48), (s32)sp, (s32)(sp + 0x10)) < 0) {
            return;
        }
    }

    s2 = 0;
    *(f32 *)(sp + 0x04) = -170.0f;
    func_003126C8((s32)(sp + 0x20), (s32)sp);
    func_003126C8((s32)(sp + 0x30), (s32)(sp + 0x10));

    cnt = *(s32 *)(D_00387A40 + 0xC);
    if (cnt > 0) {
        s3 = 0;
        do {
            s1 = (u8 *)*(s32 *)(D_00387A40 + 0x8) + s3;
            t0 = *(s32 *)(s1 + 0xC);
            s3 += 0x1520;
            if (t0 != 0) {
                p = func_00261060((u16)s2);
                *(s32 *)(p + 0xAF0) = *(s32 *)(p + 0xAF0) | 2;
                s1 = func_00261060((u16)s2);
                func_003126C8((s32)(s1 + 0x9A0), (s32)sp);
                func_003126C8((s32)(s1 + 0x9C0), (s32)sp);
                func_003126C8((s32)(s1 + 0x9B0), (s32)(sp + 0x10));
                func_00260A50((s32)s1);
                func_0025FED8((s32)func_00261060((u16)s2), 0x17, 2, 1, 0);
                if (s2 == 0) {
                    *(f32 *)sp = *(f32 *)sp + 15.0f;
                    *(f32 *)(sp + 0x08) = *(f32 *)(sp + 0x08) - 10.0f;
                }
                if (s2 == 1) {
                    *(f32 *)sp = *(f32 *)sp - 30.0f;
                }
            }
            s2 += 1;
        } while (s2 < *(s32 *)(D_00387A40 + 0xC));
    }

    p = func_00261060(0) + 0x9A0;
    f8 = *(f32 *)(sp + 0x20);
    f1 = *(f32 *)(p + 0x80) * 30.0f;
    f5 = *(f32 *)(sp + 0x24) - 20.0f;
    f3 = *(f32 *)(sp + 0x30);
    f6 = *(f32 *)(sp + 0x34);
    f4 = *(f32 *)(sp + 0x38);
    f8 = f8 + f1;
    f1 = *(f32 *)(sp + 0x28);
    f3 = f3 * 180.0f;
    f6 = f6 * 180.0f;
    f4 = f4 * 180.0f;
    *(f32 *)(sp + 0x24) = f5;
    *(f32 *)(sp + 0x20) = f8;
    f3 = f3 / D_00386E98;
    f0 = *(f32 *)(p + 0x88) * 30.0f;
    f4 = f4 / D_00386E98;
    f1 = f1 + f0;
    *(f32 *)(sp + 0x30) = f3;
    *(f32 *)(sp + 0x28) = f1;
    f6 = f6 / D_00386E98;
    *(f32 *)(sp + 0x38) = f4;
    *(f32 *)(sp + 0x34) = f6;
    func_0025ACF8((s32)(sp + 0x20), (s32)(sp + 0x30));
}
