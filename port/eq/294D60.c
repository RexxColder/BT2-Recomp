#include "common.h"

s32 ColSeg_Nearest(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_003126C8(s32 arg0, s32 arg1);

s32 ColSeg_ClosestToSeg(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 sp[16];
    s32 var_v0;

    func_003126C8((s32)&sp[0], arg0);
    func_003126C8((s32)&sp[4], arg0 + 0x10);
    func_003126C8((s32)&sp[8], arg1);
    func_003126C8((s32)&sp[12], arg1 + 0x10);
    var_v0 = ColSeg_Nearest((s32)&sp[0], (s32)&sp[8], arg2, arg3);
    if (var_v0 != 0) {
        *(f32 *)(arg2 + 0xC) = 1.0f;
        var_v0 = 1;
        *(f32 *)(arg3 + 0xC) = 1.0f;
    }
    return var_v0;
}
