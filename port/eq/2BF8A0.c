#include "common.h"

void func_002BF9D8(u8 *arg0, u8 *arg1, s32 arg2);
s32 func_002BFA18(u8 *arg0, u8 *arg1, u8 *arg2, s32 arg3, s32 arg4);
s32 func_002BFC18(s32 arg0, u8 *arg1, u8 *arg2, u8 *arg3, s32 arg4);
void func_002BFCD0(u8 *arg0, u8 *arg1, u8 *arg2, s32 arg3);
void func_002BFDF8(u8 *arg0, u8 *arg1, u8 *arg2, s32 arg3);

s32 func_002BF8A0(s32 arg0, u8 *arg1, u8 *arg2) {
    u8 sp[0x20];
    u8 *s1;
    s32 v;

    s1 = arg2 + 8;
    func_002BF9D8(sp, s1, *(s32 *)(arg2 + 0x4));
    v = func_002BFA18(arg1, sp, s1, 0, *(s32 *)s1 % *(s32 *)(arg2 + 0x28));
    if (v == 0) {
        v = func_002BFA18(arg1, sp, s1, 1, 0x800);
        if (v == 0) {
            v = func_002BFA18(arg1, sp, s1, 2, 0);
            if (v == 0) {
                func_002BFC18(arg0, arg1, sp, s1, 3);
                func_002BFCD0(arg1, sp, s1, 4);
                func_002BFC18(arg0, arg1, sp, s1, 5);
                func_002BFCD0(arg1, sp, s1, 6);
                func_002BFDF8(arg1, sp, s1, 7);
                v = 0;
            }
        }
    }
    return v;
}
