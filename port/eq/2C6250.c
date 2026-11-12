#include "common.h"

s32 func_002C62E0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s32 func_002C6A90(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void func_002C9BD0(s32 arg0);

s32 func_002C6250(u8 *arg0) {
    s32 sp[4];
    s32 s1;

    s1 = 0;
    for (;;) {
        if (*(s32 *)(arg0 + 0x60) != 0) {
            break;
        }
        s1 = func_002C62E0((s32)arg0, (s32)&sp[0], (s32)&sp[1], (s32)&sp[2]);
        if (s1 != 0) {
            break;
        }
        s1 = func_002C6A90((s32)arg0, sp[0], sp[1], sp[2], (s32)&sp[3]);
        if (s1 != 0) {
            break;
        }
        if (sp[3] == 0) {
            break;
        }
    }
    func_002C9BD0((s32)arg0);
    return s1;
}
