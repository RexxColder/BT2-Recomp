#include "common.h"

void func_002B8790(s32 arg0, s32 arg1, s32 arg2);
void func_002BADC8(s32 arg0, s32 arg1, s32 arg2);
void func_002BB038(s32 arg0, s32 arg1, s32 arg2);
void func_002BB180(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

void func_002BB5F8(s32 arg0) {
    s32 sp[1];
    s32 sp4;
    u32 temp_v1;
    u8 *p;

    p = (u8 *)arg0;
    func_002B8790(arg0, (s32)&sp[0], (s32)&sp4);
    temp_v1 = *(u32 *)(p + 0x2E4);
    *(s32 *)(p + 0x2E0) = 1;
    switch (temp_v1) {
    case 1:
        func_002BADC8(arg0, *(s32 *)(p + 0x1A4), 1);
        break;
    case 3:
        func_002BB180(arg0, *(s32 *)(p + 0x1A4), *(s32 *)(p + 0x2F4), *(s32 *)(p + 0x2F8));
        break;
    case 2:
        func_002BB038(arg0, *(s32 *)(p + 0x2EC), *(s32 *)(p + 0x2F0));
        break;
    }
    *(s32 *)(p + 0x2E0) = 0;
    *(s32 *)(p + 0x300) = *(s32 *)(p + 0x300) + 1;
}
