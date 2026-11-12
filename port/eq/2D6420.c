#include "common.h"

void *memset(void *s, int c, unsigned int n);
void func_002D64D8(u8 *arg0, s32 arg1, void *arg2);
s32 func_002D6FC8(u8 *arg0);
void func_002D5B80(s32 arg0);

void func_002D6420(u8 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 buf[30];
    void *sp;
    void (*temp_v0)(void *, s32, void *);
    s32 var_v1;

    sp = buf;
    memset(sp, 0, 0x64);
    func_002D64D8(arg0, arg1, sp);
    var_v1 = 0;
    if (arg3 == 1) {
        var_v1 = *(s32 *)(arg0 + 0x38);
    }
    buf[28] = var_v1;
    buf[29] = *(s32 *)(arg0 + 0x50);
    if (func_002D6FC8(arg0) == 1) {
        func_002D5B80(arg2);
    }
    temp_v0 = *(void (**)(void *, s32, void *))(arg0 + 0x68);
    if (temp_v0 != NULL) {
        temp_v0(sp, arg2, &buf[28]);
    }
}
