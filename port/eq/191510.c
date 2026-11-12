#include "common.h"

s32 BtlTask_SetDead(s32 arg0);
void func_00190CA8(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

void func_00191510(s32 arg0) {
    s32 temp_v0;
    s32 temp_v1;

    temp_v1 = *(s32 *)(arg0 + 0x38);
    temp_v0 = *(s32 *)(temp_v1 + 0x30);
    if ((temp_v0 & 0x10) == 0) {
        *(s32 *)(temp_v1 + 0x30) = temp_v0 | 0x10;
        func_00190CA8(*(s32 *)(*(s32 *)temp_v1), arg0, *(s32 *)(temp_v1 + 4), 0);
    }
    BtlTask_SetDead(arg0);
}
