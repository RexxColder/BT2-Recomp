#include "common.h"

s32 func_0025AB48(s32 arg0);
void func_00280480(s32 arg0, s32 arg1, s32 arg2);
extern u8 *D_003876A0;
extern s32 D_00387AF8;
extern u8 *gBtlCam;

void func_00280500(void) {
    s32 var_a2;
    s64 temp_v0;
    u8 *temp_v0_2;

    temp_v0 = *(s64 *)(D_003876A0 + 0x4D8);
    if (temp_v0 & 3) {
        if (temp_v0 & 2) {
            var_a2 = 0;
            if (func_0025AB48(D_00387AF8) == 0) {
                temp_v0_2 = *(u8 **)(gBtlCam + 0x600);
                if (*(s32 *)(temp_v0_2 + 0x258) == 0) {
                    var_a2 = *(s32 *)(temp_v0_2 + 0x250);
                    goto block_5;
                }
                func_00280480(D_00387AF8, 1, 0);
                func_00280480(D_00387AF8 + 0xBC0, 1, 1);
                return;
            }
block_5:
            func_00280480(D_00387AF8, 0, var_a2);
            return;
        }
        func_00280480(D_00387AF8, 0, 0);
    }
}
