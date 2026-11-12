#include "common.h"

extern s32 D_00387E9C;

void func_001DBAE0(s32 arg0) {
    s32 temp_v0_2;
    s32 var_a2;
    s32 var_a2_2;
    s32 var_a1;
    s32 var_a1_2;
    s8 temp_v0;

    var_a2 = 0x1D;
    var_a1 = *(s32 *) (D_00387E9C + 0x1410);
    do {
        if ((*(u8 *) (var_a1 + 0x90) != 0) && (*(u8 *) (var_a1 + 0x91) != 0)) {
            temp_v0 = *(s8 *) (var_a1 + 0x8E);
            if (temp_v0 >= 0) {
                *(u8 *) (arg0 + temp_v0) = 1;
            }
        }
        var_a2 -= 1;
        var_a1 += 0xA0;
    } while (var_a2 >= 0);
    var_a1_2 = D_00387E9C;
    var_a2_2 = 0x1F;
    do {
        if (*(u8 *) (var_a1_2 + 0x99) != 0) {
            temp_v0_2 = *(s32 *) (var_a1_2 + 0x94);
            if (temp_v0_2 >= 0) {
                *(u8 *) (arg0 + temp_v0_2) = 1;
            }
        }
        var_a2_2 -= 1;
        var_a1_2 += 0xA0;
    } while (var_a2_2 >= 0);
}
