#include "common.h"

u8 *func_00269A40(s32 arg0, s32 arg1);
void func_00312650(s32 arg0, s32 arg1, s32 arg2);
void func_003126C8(s32 arg0, s32 arg1, s32 arg2);
void sceVu0ApplyMatrix(s32 arg0, s32 arg1, s32 arg2);
extern u8 D_002C3630[] __attribute__((section(".data")));

void func_00260CB8(s32 arg0, u8 *arg1, s32 arg2) {
    s32 sp[4];
    u8 *v0;
    s32 a2;

    v0 = func_00269A40(arg0, arg2);
    a2 = (s32)v0 + 0x30;
    if (v0 == NULL) {
        func_003126C8((s32)arg1, (s32)D_002C3630, a2);
        return;
    }
    sceVu0ApplyMatrix((s32)sp, arg0 + 0xA40, a2);
    func_00312650((s32)arg1, (s32)sp, (s32)v0 + 0xC0);
    *(f32 *)(arg1 + 0xC) = 1.0f;
}
