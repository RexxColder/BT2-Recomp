#include "common.h"

void *memset(void *arg0, s32 arg1, u32 arg2);
void func_00208DE8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, f32 farg0, f32 farg1, f32 farg2, f32 farg3);
void func_0027BCC0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, f32 farg0, f32 farg1, f32 farg2, f32 farg3, f32 farg4);
extern f32 D_00385758;

void func_001F4428(s32 arg0, f32 farg0, f32 farg1, f32 farg2, f32 farg3, s32 arg3) {
    s32 sp[4];

    memset((void *)sp, 0, 0x10);
    *(f32 *)&sp[3] = 1.0f;
    func_00208DE8(arg0, (s32)sp, 3, arg3, farg0, farg1, farg2, farg3);
    func_0027BCC0(arg0, (s32)sp, 3, arg3, D_00385758, 10.0f, 50.0f, 10.0f, 0.5f);
}
