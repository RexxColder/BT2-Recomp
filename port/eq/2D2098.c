#include "common.h"

s32 func_002E0A98(s32 arg0, s32 arg1, s32 arg2);
void func_002C32B0(s32 arg0);
void func_002C32C8(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

void func_002D2098(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 base;
    s32 sp[4];
    s32 temp_s1;

    base = arg0 + 0xD30;
    temp_s1 = func_002E0A98(*(s32 *)(base + 0x2E0), arg1, arg2);
    func_002C32B0((s32)sp);
    *(s32 *)(base + 0x2DC) = *(s32 *)(base + 0x2DC) + temp_s1;
    func_002C32C8((s32)sp, arg1, arg2, arg3);
}
