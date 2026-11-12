#include "common.h"

void func_002C1638(s32 arg0, s32 arg1, s32 arg2);
void func_002C32B0(s32 arg0, s32, s32);
void func_002C32C8(s32 arg0, s32 arg1);

void func_002C1598(s32 arg0, s32 arg1, s32 arg2) {
    s32 sp[4];
    s32 temp_a1;
    u8 *p = (u8 *)arg2;

    func_002C32B0((s32)sp, arg1, arg2);
    func_002C1638(arg0, arg1, arg2);
    temp_a1 = *(s32 *)(p + 8);
    if (temp_a1 == 0) {
        if (*(s32 *)(p + 0xC) == 0) {
            if (*(s32 *)(p + 0x10) == -1) {
                p[0] = 1;
            }
        } else {
            p[0] = 1;
        }
    } else {
        p[0] = 1;
    }
    if ((temp_a1 != 0) || (*(s32 *)(p + 0xC) != 0)) {
        p[1] = 1;
    }
    func_002C32C8((s32)sp, temp_a1);
}
