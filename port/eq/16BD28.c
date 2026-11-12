#include "common.h"

s32 EftShot_TestBits(s32 arg0, s32 arg1);
void func_001CE4D0(s32 arg0, s32 arg1, f32 farg0, f32 farg1);
void func_001D2288(s32 arg0, s32 arg1, s32 arg2, f32 farg0, f32 farg1, f32 farg2);
s32 func_00208DE8(s32 arg0, s32 arg1, s32 arg2);
s32 func_0020B3D0(s32 arg0, s32 arg1);
extern s64 D_0036E610 __attribute__((section(".data")));

void func_0016BD28(s32 arg0) {
    s32 sp[4];
    s64 sp10;
    s64 sp18;
    f32 var_f13;
    s32 temp_s1;
    s32 temp_a1;
    s32 temp_s0;

    temp_a1 = *(s32 *)(arg0 + 0x38);
    temp_s0 = *(s32 *)(temp_a1 + 0xB0);
    sp10 = D_0036E610;
    sp18 = *(s64 *)((s32)&D_0036E610 + 8);
    temp_s1 = func_0020B3D0(*(s32 *)temp_s0, temp_a1);
    if ((*(s32 *)(*(s32 *)(temp_s0 + 0x20) + 0x30) & 0x400) && (EftShot_TestBits(temp_s1, 4) != 0)) {
        if (*(s32 *)(*(s32 *)(temp_s0 + 0x20)) == 0x122) {
            func_00208DE8(*(s32 *)temp_s0, (s32)sp, 0x15);
            func_001CE4D0((s32)sp, 0, 5.0f, 2.0f);
            return;
        }
        func_00208DE8(temp_s1, (s32)sp, 3);
        var_f13 = 1.0f;
        if (*(s32 *)(*(s32 *)(temp_s0 + 0x20)) == 0x9A) {
            var_f13 = 2.0f;
        }
        func_001D2288((s32)sp, (s32)&sp10, temp_s1, 1.0f, var_f13, var_f13);
    }
}
