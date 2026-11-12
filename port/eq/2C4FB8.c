#include "common.h"

s32 *func_002C5478(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_002DC798(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_002DA3A8(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

void func_002C4FB8(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 sp[8];
    s32 *temp_v0;
    u8 *b;
    s32 temp_a3;

    temp_v0 = func_002C5478(arg0, arg1, arg2, arg3);
    if (temp_v0 == 0 || *temp_v0 != 0) {
        return;
    }
    b = (u8 *)temp_v0;
    func_002DC798(arg1, (s32)sp, arg2, arg3);
    temp_a3 = (arg3 >= 0xB1) ? 0xB0 : arg3;
    if (sp[3] > 0) {
        *(s32 *)(b + 0x30 + 0x160) = temp_a3;
        func_002DA3A8((s32)(b + 0x30), arg2, temp_a3, temp_a3);
    } else if (sp[2] > 0) {
        *(s32 *)(b + 0x30 + 0x164) = temp_a3;
        func_002DA3A8((s32)(b + 0xE0), arg2, temp_a3, temp_a3);
    }
}
