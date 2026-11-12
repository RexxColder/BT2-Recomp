#include "common.h"

void func_001C2C98(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void func_001C3208(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void func_001C3BE8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void func_001C4750(s32 arg0);
s32 func_001EBD90(s32 arg0, s32 arg1);

void func_001C4D00(u8 *arg0, s32 p1, s32 p2, s32 p3, s32 p4) {
    u8 *s1;
    s16 idx;
    u8 *temp;
    u8 type;

    s1 = *(u8 **)(arg0 + 0x38);
    idx = *(s16 *)(s1 + 0xF406);
    for (;;) {
        idx = (s16)(idx - 1);
        temp = (u8 *)func_001EBD90((s32)(s1 + 0xF400), idx);
        if (temp == NULL) {
            break;
        }
        if (*(s16 *)(temp + 6) < 0) {
            continue;
        }
        type = *temp;
        if (type == 1) {
            func_001C3208((s32)temp, idx, p2, p3, p4);
        } else if (type == 0) {
            func_001C2C98((s32)temp, idx, p2, p3, p4);
        } else if (type == 2) {
            func_001C3BE8((s32)temp, idx, p2, p3, p4);
        } else if (type == 3) {
            func_001C4750((s32)temp);
        }
    }
}
