#include "common.h"

extern s32 gBtlCam;
extern f32 D_003841CC;
extern f32 D_003841D0;
extern f32 D_003841D4;
extern f32 D_003841D8;
extern f32 D_003841DC;
extern f32 D_003841E0;
extern f32 D_003841E4;
extern f32 D_003841E8;
extern u8 D_002C3630[] __attribute__((section(".data")));

void sceVu0InversMatrix(s32 arg0, s32 arg1);
void func_00312680(f32 farg0, s32 arg0, s32 arg1);
void func_00312638(s32 arg0, s32 arg1, s32 arg2);
s32 rand(void);
void func_001301D0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7,
                   f32 farg0, f32 farg1, f32 farg2, f32 farg3, f32 farg4, f32 farg5, f32 farg6,
                   f32 farg7, f32 stk0, f32 stk1, s32 stk2);

void func_0012FC88(s32 arg0) {
    u8 sp[0xC0];
    s32 base;
    s32 s0;
    s32 rv;
    s32 hi;
    f32 f20;
    f32 f21;
    f32 f0;
    f32 f1;
    f32 f2;
    f32 f18;

    base = gBtlCam + arg0 * 0x300;
    sceVu0InversMatrix((s32)(sp + 0x40), base);
    f21 = D_003841CC;
    func_00312680(10.0f, (s32)(sp + 0x20), (s32)(sp + 0x60));
    func_00312638((s32)(sp + 0x20), (s32)(sp + 0x20), base + 0x270);
    *(f32 *)(sp + 0x24) = *(f32 *)(sp + 0x24) + 20.0f;

    rv = rand();
    f20 = (f32)(rv % 2001 - 0x3E8);
    rv = rand();
    f20 = f20 * f21;
    func_00312680(f20, (s32)(sp + 0x30), (s32)(sp + 0x40));
    f20 = (f32)(rv % 2001 - 0x3E8);
    func_00312638((s32)(sp + 0x20), (s32)(sp + 0x20), (s32)(sp + 0x30));
    f20 = f20 * f21;
    func_00312680(f20, (s32)(sp + 0x30), (s32)(sp + 0x50));
    func_00312638((s32)(sp + 0x20), (s32)(sp + 0x20), (s32)(sp + 0x30));

    hi = rand() % 6;
    if (hi != 0) {
        s0 = 0;
        rv = rand();
        f1 = (f32)rv;
        f0 = D_003841D0;
        f2 = D_003841D4;
    } else {
        s0 = 1;
        rv = rand();
        f1 = (f32)rv;
        f0 = D_003841D8;
        f2 = 1.5f;
    }
    f1 = f1 / f0;
    f1 = f1 * f2;
    f20 = f1 + f2;
    rv = rand();
    f18 = (f32)rv;
    f0 = D_003841DC;
    f18 = f18 / f0;
    f2 = 0.25f;
    f1 = -1.0f;
    f18 = f18 * D_003841E0;
    func_001301D0((s32)(sp + 0x20), (s32)D_002C3630, 0x80, 0x80, 0x80, -1, arg0, s0,
                  0.0f, f20, 128.0f, 0.0f, D_003841E4, 0.0f, f18, D_003841E8,
                  f2, f1, 0);
}
