#include "common.h"

s32 func_002C3718(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
s32 func_002C3840(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5);
s32 func_002C37D8(u8 *arg0, s32 arg1, s64 arg2, s32 arg3);
void func_002C5070(u8 *arg0);

s32 func_002C3640(u8 *arg0) {
    s32 sp[5];
    s32 s1;
    s32 s2;
    s64 temp;

    s1 = 0;
    s2 = *(s32 *)(arg0 + 0x28);
    while (*(s32 *)(arg0 + 0x60) == 0) {
        s1 = func_002C3718(arg0, (s32)&sp[0], (s32)&sp[1], s2, (s32)&sp[2]);
        if (s1 != 0) {
            break;
        }
        s1 = func_002C3840(arg0, sp[0], sp[1], (s32)&sp[3], (s32)&sp[4], sp[2]);
        if (s1 != 0) {
            break;
        }
        temp = (s64)sp[3] + *(s64 *)(arg0 + 0x990);
        *(s64 *)(arg0 + 0x990) = temp;
        *(s64 *)(arg0 + 0x998) = *(s64 *)(arg0 + 0x998) + (s64)sp[4];
        if (sp[3] == 0) {
            break;
        }
        s1 = func_002C37D8(arg0, sp[3], temp, sp[3]);
        if (s1 != 0) {
            break;
        }
    }
    func_002C5070(arg0);
    return s1;
}
