#include "common.h"

void func_002D05E8(s32 arg0, s32 arg1, s32 arg2);
void func_002D2BE8(s32 arg0, s32 arg1);
void func_002D2CD8(s32 arg0, s32 arg1);
void func_002D2D78(s32 arg0, s32 arg1);
void func_002D2E18(s32 arg0, s32 arg1);
void func_002D2E38(s32 arg0, s32 arg1, s32 arg2);

s32 func_002D2AC8(u8 *arg0, u8 *arg1) {
    if (*(s32 *)(arg1 + 4) != 0) {
        func_002D2E38((s32)arg0, 0, 0);
        func_002D2BE8((s32)arg0, (s32)arg1);
        return 0;
    }
    if (*(s32 *)(arg1 + 8) != 0) {
        func_002D2E38((s32)arg0, 0, 1);
        func_002D2CD8((s32)arg0, (s32)arg1);
        func_002D05E8((s32)arg0, 6, 0);
        *(s32 *)(arg0 + 0xBB4) = 0;
        return 0;
    }
    if (*(s32 *)(arg1 + 0xC) != 0) {
        func_002D2E38((s32)arg0, 0, 2);
        func_002D2D78((s32)arg0, (s32)arg1);
        func_002D05E8((s32)arg0, 5, 0);
        *(s32 *)(arg0 + 0xBB0) = 0;
        return 0;
    }
    if (*(s32 *)(arg1 + 0x20) != 0) {
        func_002D2E38((s32)arg0, 0, 7);
        func_002D2E18((s32)arg0, (s32)arg1);
        func_002D05E8((s32)arg0, 6, 0);
        func_002D05E8((s32)arg0, 5, 0);
        *(s32 *)(arg0 + 0xBB4) = 0;
        *(s32 *)(arg0 + 0xBB0) = 0;
        return 0;
    }
    return -1;
}
