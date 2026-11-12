#include "common.h"

void BtlAnim_SetBlend(void *arg0, f32 farg1);
void func_00203810(void *arg0, s32 arg1);
void func_00203968(void *arg0, s32 arg1);
s32 func_00203C58(void *arg0, s64 arg1);
s32 func_00211310(void *arg0, s32 arg1, s32 arg2);
void func_002113C0(void *arg0, s32 arg1, s32 arg2, s32 arg3);
s32 func_0023C710(void *arg0);
extern f32 D_0038623C;

s32 func_00225F00(void *arg0) {
    s32 temp_v0;

    if (func_00211310(arg0, 2, 1) == 0) {
        return -1;
    }
    BtlAnim_SetBlend(arg0, D_0038623C);
    if (func_00211310(arg0, 1, 1) != 0) {
        func_002113C0(arg0, 3, 0x100000, 1);
        if (func_00203C58(arg0, 0x200000) != 0) {
            func_00203810(arg0, 0x4E20);
        }
        if (func_00203C58(arg0, 0x800000) != 0) {
            temp_v0 = *(s32 *)((u8 *)arg0 + 0x1188) + 0xC350;
            *(s32 *)((u8 *)arg0 + 0x1188) = temp_v0;
            if (temp_v0 > 0x186A0) {
                *(s32 *)((u8 *)arg0 + 0x1188) = 0x186A0;
            }
        }
        if (func_00203C58(arg0, 0x02000000) != 0) {
            func_00203968(arg0, 0x186A0);
        }
    }
    return func_0023C710(arg0);
}
