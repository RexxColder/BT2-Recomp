#include "common.h"

f32 cosf(f32 farg0);
f32 sinf(f32 farg0);
u8 *func_0028BAA8(s32 arg0);
void *memset(void *arg0, s32 arg1, u32 arg2);
extern f32 D_0038709C;
extern f32 D_003870A0;
extern f32 D_003870A4;
extern f32 D_003870A8;
extern u8 *D_00387AEC;

void func_0027B890(void) {
    s32 var_s2;
    s32 temp_s1;
    f32 var_f20;
    f32 temp_f12;
    f32 temp_f21;
    f32 temp_f22;
    f32 temp_f23;
    u8 *temp_v0;

    var_s2 = 0;
    temp_v0 = func_0028BAA8(0xB0);
    D_00387AEC = temp_v0;
    memset(temp_v0, 0, 0xB0);
    *(u8 **)D_00387AEC = func_0028BAA8(0x2BC0);
    var_f20 = D_0038709C;
    temp_f23 = D_003870A0;
    temp_f22 = D_003870A4;
    temp_f21 = D_003870A8;
    memset(*(u8 **)D_00387AEC, 0, 0x2BC0);
    do {
        temp_s1 = var_s2 * 8;
        var_s2 += 1;
        temp_f12 = var_f20;
        *(f32 *)(D_00387AEC + 4 + temp_s1) = sinf(var_f20);
        var_f20 += temp_f23;
        *(f32 *)(D_00387AEC + temp_s1 + 8) = cosf(temp_f12);
        if (temp_f22 <= var_f20) {
            var_f20 -= temp_f21;
        }
    } while (var_s2 < 0x14);
}
