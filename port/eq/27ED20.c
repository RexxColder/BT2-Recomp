#include "common.h"

void func_0027E968(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

void func_0027ED20(u8 *arg0, u8 *arg1, s32 arg2, s32 arg3) {
    s32 var_a2;
    s32 var_a3;

    var_a2 = arg2;
    var_a3 = arg3;
    if (arg1 == NULL) {
        var_a2 = 0x80;
        var_a3 = 0x50;
        *(u8 *)(arg0 + 0x502) = 1;
        *(s32 *)(arg0 + 0x508) = 0x78;
        *(s32 *)(arg0 + 0x520) = 0x20;
        *(s32 *)(arg0 + 0x514) = 0x80;
        *(s32 *)(arg0 + 0x518) = 0x50;
        *(s32 *)(arg0 + 0x51C) = 4;
        *(s32 *)(arg0 + 0x524) = 0x40;
        *(u8 *)(arg0 + 0x500) = 0;
        *(u8 *)(arg0 + 0x501) = 0;
    } else {
        *(u8 *)(arg0 + 0x500) = arg1[0];
        *(u8 *)(arg0 + 0x501) = arg1[1];
        *(u8 *)(arg0 + 0x502) = arg1[2];
        *(s32 *)(arg0 + 0x508) = arg1[4];
        *(s32 *)(arg0 + 0x520) = arg1[3];
        *(s32 *)(arg0 + 0x514) = arg1[5];
        *(s32 *)(arg0 + 0x518) = arg1[6];
        *(s32 *)(arg0 + 0x51C) = arg1[7];
        *(s32 *)(arg0 + 0x524) = arg1[8];
    }
    func_0027E968((s32)arg0, *(s32 *)(arg0 + 0x4D0), var_a2, var_a3);
}
