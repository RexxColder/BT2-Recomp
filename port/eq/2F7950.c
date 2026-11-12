#include "common.h"

s32 func_002F15B8(s32 arg0);
s32 func_002F1328(s32 arg0, s32 arg1, s32 arg2);
void func_002F1480(s32 arg0, s32 arg1);
void func_002F2280(s32 arg0, s32 arg1, s32 arg2);
void func_002F1F10(s32 arg0, s32 arg1, s32 arg2);

void func_002F7950(u8 *arg0) {
    s32 temp_s1;
    s32 temp_a0;
    s32 temp_a2;
    s32 temp_a2_2;

    temp_s1 = *(s32 *)(arg0 + 8);
    temp_a0 = *(s32 *)(arg0 + 4);
    if ((temp_s1 != 0) && (temp_a0 != 0)) {
        temp_a2 = func_002F15B8(temp_a0);
        if (*(s8 *)(arg0 + 2) == 4) {
            func_002F2280(*(s32 *)(arg0 + 8), 0x7FFFFFFF, temp_a2);
            return;
        }
        if (*(s8 *)(arg0 + 0x6C) == 0) {
            if (func_002F1328(*(s32 *)(arg0 + 4), 0x7FFFFFFF, temp_a2) >= *(s32 *)(arg0 + 0xC4)) {
                func_002F1480(*(s32 *)(arg0 + 4), -1);
            }
            ((void (*)(s32, s32))func_002F2280)(*(s32 *)(arg0 + 8), 0x7FFFFFFF);
            return;
        }
        temp_a2_2 = (temp_a2 < 0) ? (temp_a2 + 0x7FF) : temp_a2;
        func_002F1F10(temp_s1, temp_a2_2 >> 11, temp_a2_2);
    }
}
