#include "common.h"

s32 func_0029E6D0(s32 arg0, s32 arg1, s64 arg2, s64 arg3);
s32 func_00269A40(s32 arg0, s32 arg1);
void sceVu0InversMatrix(s32 arg0, s32 arg1);
void sceVu0MulMatrix(s32 arg0, s32 arg1, s32 arg2);
void sceVu0CopyMatrix(s32 arg0, s32 arg1);
void func_002628A8(f32 farg0, s32 arg1, s32 arg2, s32 arg3);
void func_00264540(s32 arg0, s32 arg1, s32 arg2, s64 arg3, s32 arg4, s32 arg5);
extern u8 D_003767A0[] __attribute__((section(".data")));
extern u8 D_003767B0[] __attribute__((section(".data")));
extern f32 D_00386ED8;
extern u8 *D_00387A40;
extern u8 *D_00387A44;

void func_00268F60(s32 arg0, s32 arg1) {
    s32 sp[16];
    s64 sp40[4];
    f32 sp60[16];
    s32 s2;
    s32 s3;
    s32 s4;

    s3 = arg1 + 0x80;
    sp40[0] = *(s64 *)(D_003767A0 + 0);
    sp40[1] = *(s64 *)(D_003767A0 + 8);
    sp40[2] = *(s64 *)(D_003767B0 + 0);
    sp40[3] = *(s64 *)(D_003767B0 + 8);
    s4 = func_0029E6D0(1, arg1, sp40[0], sp40[1]);
    s2 = s4 + 0xC0;
    sceVu0InversMatrix((s32)sp60, func_00269A40(arg0, 0));
    sceVu0MulMatrix(s2, (s32)sp60, s3);
    *(f32 *)((u8 *)&sp40[1] + 4) = *(f32 *)(D_00387A44 + 0xE544);
    if (*(u8 *)(arg1 + 0xD) != 0) {
        func_002628A8(D_00386ED8, (s32)sp, (s32)sp40, (s32)&sp40[2]);
    } else {
        func_002628A8(D_00386ED8, (s32)sp, (s32)sp40, (s32)(D_00387A40 + 0x38030));
    }
    sceVu0CopyMatrix(s2, s3);
    sceVu0MulMatrix(s2, s2, (s32)sp);
    sceVu0CopyMatrix(s4 + 0x100, s2);
    func_00264540(arg0, arg0 + 0xB00, 2, 0, 0, 0xA0);
}
