#include "common.h"

void *BtlTaskList_AddTail(s32 arg0, s32 arg1, s32 arg2);
void Vec3_Sub(s32 arg0, s32 arg1, s32 arg2);
void func_001B06D0(f32 farg0, s32 arg0, s32 arg1, s32 arg2);
s32 func_001B0A30(s32 arg0, s32 arg1);
s32 func_00208DE8(s32 arg0, s32 arg1, s32 arg2);
extern u8 D_003427B8[] __attribute__((section(".data")));
extern s32 D_0038785C;
extern f32 D_00384F24;

s32 func_001AE088(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s64 fr[0x1A];          /* the 0xD0-byte frame, addressed by byte offset as in the asm */
    u8 *S = (u8 *)fr;
    s32 s3;
    f32 f20;
    f32 var_f0;
    s32 var_v0;
    u8 *temp_v0;
    u8 *v1;

    s3 = arg3 & 0xFF;
    f20 = 8.0f;
    if (s3 != 0) {
        func_00208DE8(arg0, (s32)(S + 0x60), 0x15);
        func_00208DE8(arg0, (s32)(S + 0x70), 0x23);
        Vec3_Sub((s32)(S + 0x80), (s32)(S + 0x60), (s32)(S + 0x70));
    } else {
        func_00208DE8(arg0, (s32)(S + 0x60), 0x23);
        func_00208DE8(arg0, (s32)(S + 0x70), 0x15);
        Vec3_Sub((s32)(S + 0x80), (s32)(S + 0x60), (s32)(S + 0x70));
    }
    if (0.0f < *(f32 *)(S + 0x84)) {
        f20 = -1.0f;
    }
    func_001B06D0(f20, (s32)S, arg0, arg1);
    if (s3 != 0) {
        var_f0 = 0.5f;
    } else {
        var_f0 = -0.5f;
    }
    *(s32 *)(S + 0x24) = arg2;
    *(f32 *)(S + 0x30) = D_00384F24;
    *(s32 *)(S + 0x28) = arg1;
    *(s32 *)(S + 0x20) = arg0;
    *(u8 *)(S + 0x49) = (u8)s3;
    *(f32 *)(S + 0x34) = var_f0;
    *(f32 *)(S + 0x2C) = f20;
    *(s32 *)(S + 0x4C) = 0;
    temp_v0 = (u8 *)BtlTaskList_AddTail(D_0038785C, (s32)D_003427B8, (s32)S);
    var_v0 = -1;
    if (temp_v0 != NULL) {
        v1 = *(u8 **)(temp_v0 + 0x38);
        *(s32 *)(v1 + 0x60) = *(s32 *)(v1 + 0x60) | 8;
        var_v0 = func_001B0A30((s32)temp_v0, arg0);
    }
    return var_v0;
}
