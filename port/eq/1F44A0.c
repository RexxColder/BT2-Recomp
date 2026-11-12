#include "common.h"

void *memset(void *arg0, s32 arg1, u32 arg2);
void func_00208DE8(s32 arg0, void *arg1, s32 arg2);
void func_00312638(void *arg0, void *arg1, void *arg2);
void func_00312FB0(void *arg0, void *arg1, f32 farg2);
void func_001CF938(void *arg0, s32 arg1, f32 farg2, f32 farg3, f32 farg4);

void func_001F44A0(s32 arg0) {
    s32 sp[4];
    s32 sp10[4];
    s32 sp20[4];

    memset(sp, 0, 0x10);
    memset(sp10, 0, 0x10);
    *(f32 *)&sp[3] = 1.0f;
    memset(sp20, 0, 0x10);
    *(f32 *)&sp10[3] = 1.0f;
    *(f32 *)&sp20[3] = 1.0f;
    func_00208DE8(arg0, sp, 0xF);
    func_00208DE8(arg0, sp10, 0xB);
    func_00312638(sp20, sp10, sp);
    func_00312FB0(sp20, sp20, 0.5f);
    func_001CF938(sp20, 0x10, 1.0f, 5.0f, 10.0f);
}
