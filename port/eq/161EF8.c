#include "common.h"

void func_0014EAE8(s32 arg0, s32 arg1);
void func_00161780(s32 arg0);
s32 func_001F3758(s32 arg0);
void *memset(void *s, s32 c, u32 n);
extern f32 D_00384750;

void func_00161EF8(s32 arg0, s32 arg1) {
    s32 temp_s1;
    s32 temp_s0;
    s32 temp_v0;

    temp_s0 = *(s32 *) (arg0 + 0x38);
    temp_s1 = *(s32 *) (func_001F3758(arg0) + 0x38);
    memset((void *) temp_s0, 0, 0xB20);
    *(s32 *) (temp_s0 + 0x70) = arg1;
    temp_v0 = *(s32 *) (arg1 + 0x24);
    *(f32 *) (temp_s0 + 0xC) = *(f32 *) (temp_v0 + 8) * D_00384750;
    *(f32 *) (temp_s0 + 0x10) = *(f32 *) (temp_v0 + 4);
    func_0014EAE8(temp_s1, temp_s0 + 0x74);
    func_00161780(arg0);
}
