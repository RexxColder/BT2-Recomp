#include "common.h"

void func_0025BB38(u8 *arg0, s32 arg1);
extern u8 *D_003876A0;
extern u8 *gBtlCam;

void func_0025BCD8(void) {
    s32 temp_a1;
    s32 temp_s0;
    s32 var_s1;
    s32 var_s2;

    var_s1 = 0;
    if (*(s64 *)(D_003876A0 + 0x4D8) & 2) {
        var_s2 = 0;
        do {
            temp_s0 = var_s2 + 0x250;
            temp_a1 = var_s1 == 0;
            *(s32 *)(gBtlCam + temp_s0) = var_s1;
            var_s1 += 1;
            *(s32 *)(gBtlCam + temp_s0 + 8) = 1;
            func_0025BB38(gBtlCam + var_s2, temp_a1);
            var_s2 += 0x300;
            *(s32 *)(gBtlCam + temp_s0 + 0xC) = 0;
        } while (var_s1 < 2);
        return;
    }
    var_s2 = 0;
    do {
        temp_s0 = var_s2 + 0x250;
        *(s32 *)(gBtlCam + temp_s0) = var_s1;
        var_s1 += 1;
        *(s32 *)(gBtlCam + temp_s0 + 8) = 0;
        func_0025BB38(gBtlCam + var_s2, 0);
        var_s2 += 0x300;
        *(s32 *)(gBtlCam + temp_s0 + 0xC) = 0;
    } while (var_s1 < 2);
}
