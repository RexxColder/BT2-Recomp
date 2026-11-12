#include "common.h"

typedef void (*Fn2)(void *, void *);

void func_00129C28(void *arg0, void *arg1, f32 farg0);
void Vec4_Set(void *arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4);
void *memset(void *arg0, s32 arg1, s32 arg2);
void func_00178308(void *arg0, s32 arg1, s32 arg2, s32 arg3);

/* the 2-argument calls to func_00129C28 are through Fn2: the asm sets only a0 and a1 there (f12 is not its argument) */
void func_00178070(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, f32 farg0, f32 farg1, f32 farg2, f32 farg3) {
    u8 sp[0x280] __attribute__((aligned(8)));
    s32 fp;
    s32 k;
    s32 off;
    u8 *s0;
    u8 *s1;
    u8 *s2;
    u8 *s3;

    fp = arg3 & 0xFF;

    func_00129C28(sp + 0x1B0, arg0, farg0);
    ((Fn2)func_00129C28)(sp + 0x1C0, arg0 + 0x10);
    ((Fn2)func_00129C28)(sp + 0x1D0, arg0 + 0x20);
    ((Fn2)func_00129C28)(sp + 0x1E0, arg0 + 0x30);

    Vec4_Set(sp + 0x1F0, 0.0f, 0.0f, 1.0f, 0.0f);
    Vec4_Set(sp + 0x200, 1.0f, 0.0f, 1.0f, 0.0f);
    Vec4_Set(sp + 0x210, 0.0f, 1.0f, 1.0f, 0.0f);
    Vec4_Set(sp + 0x220, 1.0f, 1.0f, 1.0f, 0.0f);
    Vec4_Set(sp + 0x230, farg0, farg1, farg2, farg3);
    Vec4_Set(sp + 0x240, farg0, farg1, farg2, farg3);
    Vec4_Set(sp + 0x250, farg0, farg1, farg2, farg3);
    Vec4_Set(sp + 0x260, farg0, farg1, farg2, farg3);

    memset(sp, 0, 0x1B0);

    for (k = 0; k < 3; k++) {
        off = k * 16;
        ((Fn2)func_00129C28)(sp + off, sp + 0x1B0 + off);
        ((Fn2)func_00129C28)(sp + off + 0x90, sp + 0x1F0 + off);
        ((Fn2)func_00129C28)(sp + off + 0x120, sp + 0x230 + off);
    }

    func_00178308(sp, arg1, arg2, fp);
    memset(sp, 0, 0x1B0);

    s3 = sp + 0x240;
    s1 = sp + 0x1C0;
    s2 = sp + 0x200;
    s0 = sp;
    for (k = 0; k < 3; k++) {
        ((Fn2)func_00129C28)(s0, s1);
        ((Fn2)func_00129C28)(s0 + 0x90, s2);
        s2 += 0x10;
        ((Fn2)func_00129C28)(s0 + 0x120, s3);
        s3 += 0x10;
        s1 += 0x10;
        s0 += 0x10;
    }

    func_00178308(sp, arg1, arg2, fp);
}
