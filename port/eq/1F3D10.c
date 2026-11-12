#include "common.h"

void EftVram_Upload(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern s32 gEftVram;

void func_001F3D10(void) {
    s32 temp_a0;
    s32 temp_v1;
    s32 var_a1;
    s32 var_a2;
    u32 var_s0;

    var_s0 = 0;
    if (*(u32 *) (gEftVram + 0x800) != 0) {
        do {
            var_s0 += 1;
            temp_v1 = gEftVram + (var_s0 - 1) * 4;
            temp_a0 = *(s32 *) (temp_v1 + 0x600);
            var_a2 = -1;
            var_a1 = -1;
            if (temp_a0 & 1) {
                var_a1 = *(s32 *) (temp_v1 + 0x200);
            }
            if (temp_a0 & 2) {
                var_a2 = *(s32 *) (temp_v1 + 0x400);
            }
            EftVram_Upload(*(s32 *) (gEftVram + (var_s0 - 1) * 4), var_a1, var_a2, temp_v1);
        } while (var_s0 < *(u32 *) (gEftVram + 0x800));
    }
}
