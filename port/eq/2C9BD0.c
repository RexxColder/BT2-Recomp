#include "common.h"

void func_002C0750(void *arg0, s32 arg1, s32 *arg2);
void func_002C0F30(s32 arg0, s32 *arg1, s32 *arg2);
s64 func_002C10E8(s64 arg0, u64 arg1);

void func_002C9BD0(void *arg0) {
    s32 sp[3];

    func_002C0750(arg0, *(s32 *)((u8 *)arg0 + 0x1FC8), sp);
    if (sp[0] != 0) {
        func_002C0F30(sp[0], &sp[1], &sp[2]);
        *(s64 *)((u8 *)arg0 + 0x9A0) = func_002C10E8(*(s64 *)((u8 *)arg0 + 0x9A0), sp[1]);
    }
}
