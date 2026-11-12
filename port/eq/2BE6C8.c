#include "common.h"

void func_002C0750(u8 *arg0, s32 arg1, s32 *arg2);
void func_002C0F30(s32 arg0, s32 *arg1, s32 *arg2);
s64 func_002C10E8(s64 arg0, u64 arg1);

void func_002BE6C8(u8 *arg0) {
    s32 sp[4];
    u8 *temp_v0;
    u8 *temp_s1;

    temp_v0 = arg0 + 0x1FFC;
    temp_s1 = *(u8 **)(temp_v0 + 8);
    func_002C0750(arg0, *(s32 *)(temp_v0 + 0x10), sp);
    if (sp[0] != 0) {
        func_002C0F30(sp[0], &sp[1], &sp[2]);
        *(s64 *)(arg0 + 0x9B8) = func_002C10E8(*(s64 *)(arg0 + 0x9B8), sp[1]);
        *(s64 *)(arg0 + 0x9C0) = func_002C10E8(*(s64 *)(arg0 + 0x9C0), sp[2]);
        func_002C0F30(*(s32 *)(temp_s1 + 4), &sp[1], &sp[2]);
        *(s64 *)(arg0 + 0x9D0) = func_002C10E8(*(s64 *)(arg0 + 0x9D0), sp[1]);
        *(s64 *)(arg0 + 0x9D8) = func_002C10E8(*(s64 *)(arg0 + 0x9D8), sp[2]);
    }
}
