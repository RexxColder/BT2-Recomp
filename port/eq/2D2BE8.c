#include "common.h"

void func_002D05E8(void *arg0, s32 arg1, s32 arg2);
void func_002D2CD8(void *arg0, void *arg1);
void func_002D2D78(void *arg0, void *arg1);
void func_002D2E18(void *arg0, void *arg1);
void func_002D2E58(void *arg0, s32 arg1, s32 arg2);
void func_002D2E78(void *arg0, s32 arg1, s32 arg2);
void func_002D2E98(void *arg0, s32 arg1, s32 arg2);
void func_002D2EF8(void *arg0, s32 arg1, s32 arg2);

void func_002D2BE8(void *arg0, void *arg1) {
    func_002D2EF8(arg0, 0, 1);
    if (*(s32 *)((u8 *)arg1 + 8) != 0) {
        func_002D2E58(arg0, 1, 1);
        func_002D2CD8(arg0, arg1);
    } else {
        func_002D05E8(arg0, 5, 0);
        *(s32 *)((u8 *)arg0 + 0xBB0) = 0;
    }
    if (*(s32 *)((u8 *)arg1 + 0xC) != 0) {
        func_002D2E78(arg0, 1, 2);
        func_002D2D78(arg0, arg1);
    } else {
        func_002D05E8(arg0, 6, 0);
        *(s32 *)((u8 *)arg0 + 0xBB4) = 0;
    }
    if (*(s32 *)((u8 *)arg1 + 0x20) != 0) {
        func_002D2E98(arg0, 1, 7);
        func_002D2E18(arg0, arg1);
    }
}
