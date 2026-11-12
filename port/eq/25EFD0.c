#include "common.h"

s32 func_00269A40(s32 arg0, s32 arg1);
s32 func_003126C8(s32 arg0, s32 arg1);

void func_0025EFD0(s32 arg0) {
    s32 temp_v0;
    s32 var_s1;

    var_s1 = *(s32 *) (arg0 + 0x48);
    for (;;) {
        temp_v0 = func_00269A40(arg0, *(u16 *) (var_s1 + 0xA));
        func_003126C8(temp_v0 + 0x80, var_s1 + 0x30);
        *(s32 *) (temp_v0 + 0x90) = 0;
        *(f32 *) (temp_v0 + 0x9C) = 1.0f;
        *(s32 *) (temp_v0 + 0x94) = 0;
        *(s32 *) (temp_v0 + 0x98) = 0;
        if (*(u16 *) (var_s1 + 6) != 0) {
            break;
        }
        var_s1 += *(s32 *) var_s1;
    }
}
