#include "common.h"

void func_002F3378(s32 arg0, s32, s32, s32);
void func_002F3390(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

void func_002F3080(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 temp_s1;
    s32 temp_v0;

    *(s32 *) (arg0 + 4) = arg1;
    func_002F3378(arg0, arg1, arg2, arg3);
    temp_s1 = ((s32 (*)(s32, s32)) *(s32 *) (*(s32 *) arg1 + 0x24))(arg1, 0);
    *(s32 *) (arg0 + 0x40) = temp_s1 + ((s32 (*)(s32, s32)) *(s32 *) (*(s32 *) arg1 + 0x24))(arg1, 1);
    func_002F3390(arg1, 1, arg2, arg3);
    temp_v0 = *(s32 *) (arg0 + 0x40);
    *(s32 *) (arg0 + 0x1C) = temp_v0;
    *(s32 *) (arg0 + 0x18) = temp_v0;
}
